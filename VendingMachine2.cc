#include "vendingmachine2.h"
#include "printer.h"
#include "nameserver.h"
#include "PRNG.h"

extern PRNG prng;

/*
  purpose: helper function that creates a constructor with exact same values
  precondition: Printer, Nameserver, unsigned int, unsigned int, unsigned int
  postcondition: VendingMachine
*/

//void VendingMachine::set( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour)
{
    vend_printer = &prt;
    vend_server = &nameServer;
    VMId = id;
    sodaPrice = sodaCost;
    maxStockEachFlav = maxStockPerFlavour;
    
    vend_printer->print(Printer::Vending, VMId, 'S', sodaPrice);
    
    for (unsigned int i = 0 ; i < 4 ; i += 1)
    {
      currentStocks[i] = 0; // set all stocks to 0
    }
    
    vend_server->VMregister(this); // register the vending machine into nameserver
}

//----------------------------------------------------------------------------------------
//Constructors

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour )
{
    set(prt, nameServer, id, sodaCost, maxStockPerFlavour);
}

VendingMachineCardEater::VendingMachineCardEater ( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : VendingMachine( prt, nameServer, id, sodaCost, maxStockPerFlavour )
{
    set(prt, nameServer, id, sodaCost, maxStockPerFlavour);
}

VendingMachineOverCharger::VendingMachineOverCharger( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : VendingMachine( prt, nameServer, id, sodaCost, maxStockPerFlavour ) 
{
    set(prt, nameServer, id, sodaCost, maxStockPerFlavour);
}

//----------------------------------------------------------------------------------------

//Destructors

VendingMachine::~VendingMachine(){
    vend_server->print(Printer::Vending, VMId, 'F');
}

VendingMachineCardEater::~VendingMachineCardEater(){
    vend_server->print(Printer::Vending, VMId, 'F');
}

VendingMachineOverCharger::~VendingMachineOverCharger(){
    vend_server->print(Printer::Vending, VMId, 'F');
}

//----------------------------------------------------------------------------------------
//Buy

Vendingmachine::Status buy_help(Flavours flavour, WATCard *&card)
{
   
    //Check the WatCard balance of the student, if they don't have enough money, FUNDS is
    //returned
    if (card->balance < sodaPrice){
        return FUNDS;   
    }
    
    //If there are none of the students favourtie drink left in stock, return STOCK
    else if ( currentStocks[flavour] == 0 ){
        return STOCK;
    }
    
    //If the student can make a successful purchase, then debit the price
	//of the drink from the WatCard and return BUY
    else{
        //Reduce the WatCard balance by the soda's price (it will be 2x the price
        //because of the constructor)
        card->sub_fund(sodaPrice);
    
    	  //There is one less of that drink flavour in stock
    	  currentStocks[flavour] -= currentStocks[flavour];

    	  vend_server->print(Printer::Vending, VMId, 'B', flavour, currentStocks[flavour]);
        return BUY;
    }
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard *&card)
{
    return buy_help(flavour, card);
}

//----------------------------------------------------------------------------------------

VendingMachine::Status VendingMachineCardEater::buy( Flavours flavour, WATCard *&card){
    
    if (prng(9) == 9){   // 1 in 10 Chance the card should be deleted. 
        delete card; //card deleted
        card = NULL; // card set to NULL
    }
    return buy_help(flavour, card);
    
}

//----------------------------------------------------------------------------------------

VendingMachine::Status VendingMachineOverCharger::buy( Flavours flavour, WATCard *&card)
{
  return buy_help(flavour, card);
}

//----------------------------------------------------------------------------------------
//Inventory

//Used by Trucks to find the amount of each kind of sode currently
//in the vending machine

unsigned int* VendingMachine::inventory(){
    return currentStocks;
}

unsigned int* VendingMachineCardEater::inventory(){
    return currentStocks;        
}

unsigned int* VendingMachineOverCharger::inventory(){
    return currentStocks;
}

//----------------------------------------------------------------------------------------
//Restocked

//Used by Trucks after they are done with the restocking of a
//Vending Machine

void VendingMachine::restocked(){
     vend_server->print(Printer::Vending, VMId, 'R');
}

void VendingMachineCardEater::restocked(){
    vend_server->print(Printer::Vending, VMId, 'R');       
}

void VendingMachineOverCharger::restocked(){
    vend_server->print(Printer::Vending, VMId, 'R');
}

//----------------------------------------------------------------------------------------
//GetID
//Returns the ID of the vending machine
unsigned int VendingMachine::getId(){
    return VMId;
}

unsigned int VendingMachineCardEater::getId(){
    return VMId;
}

unsigned int VendingMachineOverCharger::getId(){
    return VMId;
}

//----------------------------------------------------------------------------------------

//Cost
//Returns the cost of the soda
unsigned int VendingMachine::cost(){
    return sodaPrice;
}

unsigned int VendingMachineCardEater::cost(){
    return sodaPrice;
}

unsigned int VendingMachineOverCharger::cost(){
    return sodaPrice * 2;
}

//----------------------------------------------------------------------------------------
