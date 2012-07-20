#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__
#include "printer.h"
#include "Watcard.h"
#include "flavour.h"

class VendingMachine {
// general vending machine
	protected:
    	Printer *vend_printer;
      NameServer *vend_server;
    	unsigned int VMId, sodaPrice, maxStockEachFlav, currentStocks[4] ;
      void set(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour);

	public:
		enum Status { BUY, STOCK, FUNDS }; // purchase status: successful buy, out of stock, insufficient funds
		VendingMachine( Printer &prt, NameServer &nameServer,
			unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
		virtual ~VendingMachine();
		// necessary to trigger destructors in inherited classes
		virtual Status buy( Flavours flavour, WATCard*&card ); // YOU DEFINE FLAVOURS
		virtual unsigned int*inventory();
		virtual void restocked();
		virtual unsigned int cost();
		virtual unsigned int getId();
};


class VendingMachineCardEater : public VendingMachine { // specific vending machine
	public:
		VendingMachineCardEater( Printer &prt, NameServer &nameServer,
			unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
// member routines from VendingMachine

		Status buy( Flavours flavour, WATCard*&card ); // YOU DEFINE FLAVOURS
		unsigned int*inventory();
		unsigned int cost();
		unsigned int getId();
		void restocked();


};


class VendingMachineOverCharger : public VendingMachine { // specific vending machine
   public:
		VendingMachineOverCharger( Printer &prt, NameServer &nameServer,
			unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
// member routines from VendingMachine

		Status buy( Flavours flavour, WATCard*&card ); // YOU DEFINE FLAVOURS
		unsigned int*inventory();
		unsigned int cost();
		unsigned int getId();
		void restocked();
};

#endif
