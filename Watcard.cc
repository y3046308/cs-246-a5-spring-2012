#include "Watcard.h"

WATCard::WATCard()
{
    balanced = 0;                 
}

void WATCard::add_fund(unsigned int amount)
{
     balance += amount;
}

void WATCard::sub_fund(unsigned int amount)
{
    balance -= amount; 
}
