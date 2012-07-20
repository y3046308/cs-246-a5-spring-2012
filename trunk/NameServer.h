#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__
#include "VendingMachine.h"

class NameServer {
	private:
		Print printerptr;
		unsigned int numVM;
		unsigned int numStud;
		unsigned int counter;
		vector<unsigned int> arrayOfMachines;
		
	public:
		NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
		void VMregister( VendingMachine*vendingmachine );
		VendingMachine*getMachine( unsigned int id );
		VendingMachine**getMachineList();
};

#endif
