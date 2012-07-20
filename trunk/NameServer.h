#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__
#include "VendingMachine2.h"
#include "printer.h"
#include <vector>
using namespace std;

class NameServer {
	private:
		Print *printerptr;
		unsigned int numVM, numStud, counter;
		vector<VendingMachine*> arrayOfMachines;
		
	public:
		NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
		void VMregister( VendingMachine*vendingmachine );
		VendingMachine*getMachine( unsigned int id );
		VendingMachine**getMachineList();
};

#endif
