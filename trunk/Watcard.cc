#include "Watcard.h"

WATCard::WATCard()
{
    balanced = 0;                 
}

unsigned int WATCard::curr_balance()
{
    return balance;        
}

void WATCard::add_fund(unsigned int amount)
{
     balance += amount;
}

void WATCard::sub_fund(unsigned int amount)
{
    balance -= amount; 
}
