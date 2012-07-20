#include "office.h"
#include "PRNG.h"

/*
  purpose: constructor
  precondition: printer
  postcondition: None
*/
WATCardOffice::WATCardOffice( Printer &prt )
{
    office_printer = &prt;
    office_printer->print(Printer::WATCardOffice, 'S');                          
}

/*
  purpose: destructor
  precondition: printer
  postcondition: none
*/
WATCardOffice::~WATCardOffice( Printer &prt )
{
    office_printer = NULL;
    office_printer->print(Printer::WATCardOffice, 'F');                          
}

/*
  purpose: create a new watcard
  precondition: unsigned int, unsigned int
  postcondition: WATcard
*/
WATCard *WATCardOffice::create( unsigned int id, unsigned int amount )
{
        // creat a new watcard
        WATcard *new_card = new WATcard;
        // a new watcard is initialized with 'amount'
        WATcard->balance = amount;
        office_printer->print(Printer::WATCardOffice, 'C', id, amount);
        return new_card;       
}

/*
  purpose: transfer money to another watcard
  precondition: unsigned int, unsigned int, WATcard
  postcondition: NONE
*/
void WATCardOffice::transfer( unsigned int id, unsigned int amount, WATCard &card )
{
     int rand = prng(1,4); // pick a number b/w 1 to 4
     
     if (rand == 1)        // if random number is 1, 
     {                     // There is 1/4 change to pick 1 from 1-4
        amount /= 2;       // then half of transferred money disapears
     }
     card.addfund(amount);
     office_printer->print(Printer::WATCardOffice, 'T', id, amount);
}
