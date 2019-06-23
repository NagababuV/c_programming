#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);

}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH:
    return"STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
  case FULL_HOUSE:
    return "FULL_HOUSE";
  case FLUSH:
    return "FLUSH";
  case STRAIGHT:
    return "STRAIGHT";
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
  case TWO_PAIR:
    return "TWO_PAIR";
  case PAIR:
    return "PAIR";
  default:
  
  return "NOTHING";
  }
}

char value_letter(card_t c) {
  static const char *l = "234567890JQKA";

  if (c.value >= 2 && c.value <= VALUE_ACE)
    return l[c.value -2];
  return '?';
}


char suit_letter(card_t c) {
  static const char *sl = "shdc";

  if (c.suit >= 0 && c.suit <= CLUBS)
   return  sl[c.suit];
  return '?';
  
}

void print_card(card_t c) {
  printf("%c%c",value_letter(c),suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;

  temp.value = 19;
  int i;
  static const char *letter = "234567890JQKA";
  for(i=0; i<14; i++){
    if(letter[i] == value_let)
      temp.value = i+2;
  }

  assert(temp.value != 19);

  temp.suit = 4;
  static const char *suit = "shdc";
  for(i=0;i <4;i++){
    if(suit[i] == suit_let)
      temp.suit = i;
  }
      
  assert(temp.suit != 4);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.suit= c/13;
  temp.value = c%13+2;
  return temp;
}
