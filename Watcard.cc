#include "Watcard.h"

/*
  purpose: constructor that initializes WATCard with a balance of 0
  precondition: NONE
  postcondition: WATCard
*/
WATCard::WATCard()
{
    balanced = 0; // set balance to 0
}

/*
  purpose: add money to current watcard balance
  precondition: unsigned int
  postcondition: none
*/
void WATCard::add_fund(unsigned int amount)
{
     balance += amount;
}

/*
  purpose: display current balance in watcard
  precondition: none
  postcondition: unsigned int
*/
unsigned int WATCard::curr_balance()
{
    return balance;        
}

/*
  purpose: subtract money to current watcard balance
  precondition: unsigned int
  postcondition: none
*/
void WATCard::sub_fund(unsigned int amount)
{
    balance -= amount; 
}
