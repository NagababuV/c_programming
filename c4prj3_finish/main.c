#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void actScore(deck_t **hands, size_t n_hands, int * win_arr){
  size_t bt = 0;
  int comp = 0;
  int flag = 0;

  size_t i;
  for(i =1; i<n_hands;i++){
    comp = compare_hands(hands[bt], hands[i]);
    if(comp == -1){
      bt = i;
      flag = 0;
    }
    if(comp == 0)
      flag = 1;
  }
  if(flag)
    win_arr[n_hands]++;
  else
    win_arr[bt]++;
}

void freeFutCards(future_cards_t *fc){

  size_t i;
  for(i = 0; i < fc->n_decks;i++)
    free((fc->decks[i]).cards);

  free(fc->decks);
  free(fc);

}

void freeAll(future_cards_t *fc, deck_t **hands, size_t n_hands,
	     deck_t *rem_deck, int *win_arr){
  freeFutCards(fc);
  size_t i;
  for(i=0;i<n_hands;i++)
    free_deck(hands[i]);

  free(hands);
  free_deck(rem_deck);
  free(win_arr);
}

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if((argc==1) || (argc>3)){
    fprintf(stderr, "Wrong number of arguments");
    return EXIT_FAILURE;
  }

  int n_trails;
  deck_t **hands;
  deck_t *rem_cards;
  size_t n_hands =0;
  FILE *f = NULL;
  int *win_arr =NULL;

  future_cards_t *fc = (future_cards_t *)malloc(sizeof(*fc));
  fc->decks =NULL;
  fc->n_decks = 0;

  if(argc == 2)
    n_trails = 10000;
  else
    n_trails = strToInt(argv[2]);

  f = fopen(argv[1],"r");
  hands = read_input(f,&n_hands,fc);
  rem_cards = build_remaining_deck(hands, n_hands);
  win_arr = (int *)realloc(win_arr,(n_hands+1)*sizeof(*win_arr));
  int k;
  for(k =0;k<n_hands+1;k++)
    win_arr[k] =0;

  for(k=0; k<n_trails;k++){
    shuffle(rem_cards);
    future_cards_from_deck(rem_cards,fc);
    actScore(hands,n_hands,win_arr);
  }

  size_t i;
  for(i =0; i< n_hands;i++)
    printf("Hand %zu won %u / %u times (%.2f%%)\n",i,win_arr[i],n_trails,
	   100*(float)win_arr[i]/(float)n_trails);

  printf("And there were %u ties\n",win_arr[n_hands]);
  freeAll(fc,hands, n_hands, rem_cards, win_arr);
  fclose(f);

  
  return EXIT_SUCCESS;
}
