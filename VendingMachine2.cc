#include <iostream>
#include <string>
//#include <vector>
#include "vendingmachine.h"
#include "PRNG.h"

using namespace std;

extern PRNG prng;

//----------------------------------------------------------------------------------------
//Constructors

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ){
    currentStocks = new unsigned int[4];
    printerpt = &prt;
    VMId = id;
    sodaPrice = sodaCost;
    maxStockEachFlav = maxStockPerFlavour;
    restocking = false;
}

VendingMachineCardEater::VendingMachineCardEater ( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : VendingMachine( prt, nameServer, id, sodaCost, maxStockPerFlavour ) {
    currentStocks = new unsigned int[4];
    
    for (int i = 0; i<4; i++){
		currentStocks[i] = 0;
    }
    
    printerptr = &prt;
    printerpts->print(Printer::Vending, id, 'S', sodaCost);
    VMId = id;
    sodaPrice = sodaCost;
    maxStockEachFlav = maxStockPerFlavour;
    restocking = false;
    nameServer.VMregister( this );
}

VendingMachineOverCharger::VendingMachineOverCharger( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : VendingMachine( prt, nameServer, id, sodaCost, maxStockPerFlavour ) {
    currentStocks = new unsigned int[4];
    
    for (int i = 0; i<4; i++){
		currentStocks[i] = 0;
    }

    printerptr = &prt;
    printerptr->print(Printer::Vending, id, 'S', sodaCost * 2);
    VMId = id;
    sodaPrice = sodaCost * 2;
    maxStockEachFlav = maxStockPerFlavour;
    restocking = false;
    nameServer.VMregister( this );
}

//----------------------------------------------------------------------------------------

//Destructors

VendingMachine::~VendingMachine(){
    printerptr->print(Printer::Vending, VMId, 'F');
    delete []currentStocks;
    delete printerptr;
}

VendingMachineCardEater::~VendingMachineCardEater(){
    printerpts->print(Printer::Vending, VMId, 'F');
}

VendingMachineOverCharger::~VendingMachineOverCharger(){
    printerptr->print(Printer::Vending, VMId, 'F');
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
    return sodaPrice;
}

//----------------------------------------------------------------------------------------
//Buy

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard *&card){
   
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
        card->balance = card->balance - sodaPrice;
    
    	//There is one less of that drink flavour in stock
    	currentStocks[flavour] = currentStocks[flavour] - 1;

    	printerptr->print(Printer::Vending, VMId, 'B', flavour, currentStocks[flavour]);
        return BUY;
    }
}

//----------------------------------------------------------------------------------------

VendingMachine::Status VendingMachineCardEater::buy( Flavours flavour, WATCard *&card){
    
    if (prng(9) == 9){   // 1 in 10 Chance the card should be deleted. If so, set flag to 1.
        bool flag = true; //A flag that is used to determine when a card should be deleted ("eaten")
    }
    
    //Check the WatCard balance of the student, if they don't have enough money, FUNDS is
    //returned
    if (card->balance < sodaPrice){            
        
    	if (flag) {             //Delete the card first if the Vending Machine "eats it"
        	WATCard* temp;
        	temp = card;
        	card = NULL;
        	delete temp;
    	}
        
    	return FUNDS;
    }
    
    //If there are none of the students favourtie drink left in stock, return STOCK
    else if (currentStocks[flavour] == 0){
		
        if (flag) {            //Delete the card first if the Vending Machine "eats it"
        	WATCard* temp;
        	temp = card;
        	card = NULL;
        	delete temp;
    	}
        
    	return STOCK;   
    }

	//If the student can make a successful purchase, then debit the price
	//of the drink from the WatCard and return BUY
    else{ 
		
        card->balance = card->balance - sodaPrice;
        
    	if (flag) {           //Delete the card first if the Vending Machine "eats it"
        	WATCard* temp;
        	temp = card;
        	card = NULL;
        	delete temp;
    	}
        
    //There is one less of that drink flavour in stock
    currentStocks[flavour] = currentStocks[flavour] - 1;

    printerptr->print(Printer::Vending, VMId, 'B', flavour, currentStocks[flavour]);
    return BUY;
    }
}

//----------------------------------------------------------------------------------------

VendingMachine::Status VendingMachineOverCharger::buy( Flavours flavour, WATCard *&card){
   
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
		card->balance = card->balance - sodaPrice;
    
    	//There is one less of that drink flavour in stock
    	currentStocks[flavour] = currentStocks[flavour] - 1;

    	printerptr->print(Printer::Vending, VMId, 'B', flavour, currentStocks[flavour]);
        return BUY;
    }
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
	restocking = false;
	printerptr->print(Printer::Vending, 'R');
}

void VendingMachineCardEater::restocked(){
    restocking = false;
    printerptr->print(Printer::Vending, 'R');       
}

void VendingMachineOverCharger::restocked(){
    restocking = false;
    printerptr->print(Printer::Vending, 'R');
}

//----------------------------------------------------------------------------------------
