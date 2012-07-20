class VendingMachine {
// general vending machine
	private:
    	unsigned int printerpt;
    	unsigned int VMId;
    	unsigned int sodaPrice;
    	unsigned int maxStockEachFlav;
    	bool restocking;

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
	private:
		int printerptr;
    	unsigned int VMId;
    	unsigned int sodaPrice;
    	unsigned int maxStockEachFlav;
    	bool restocking;
    	
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
	private:
		int printerptr;
    	unsigned int VMId;
    	unsigned sodaPrice;
    	unsigned int maxStockEachFlav;
    	bool restocking;
    	
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
