
#include<iostream>
#include<string>
#include<vector>
#include"nameserver.h"
#include"vendingmachine.h"

 //extern VendingMachine* machines;

extern int currentStudentId;

using namespace std;
int NameServer::indexer;
 
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ){

	printerptr = &prt;
	numVM = numVendingMachines;
	numStud = numStudents;
	counter = 0;
	arrayOfMachines.resize(numVM);
	printerptr->print(Printer::NameServer, 'S');
}

NameServer::~NameServer(){
	printerptr->print(Printer::NameServer, 'F');
}

void NameServer::VMregister( VendingMachine *vendingmachine ){
 // Add to the array, a pointer to the passed in vendingmachine at its own id
 //machinesArray.at(vendingmachine->getId()) = vendingmachine;
 //cout << "REGISTERED : " << vendingmachine->getId() << endl;
	printerptr->print(Printer::NameServer, 'R', vendingmachine->getId());
	arrayOfMachines.at(counter) = vendingmachine;
	counter = counter + 1;
 }
 

VendingMachine* NameServer::getMachine(unsigned int id){
	
	printerptr->print(Printer::NameServer, 'N', currentStudentId, arrayOfMachines.at((id+1) % numVM)->getId());
	return arrayOfMachines.at((id + 1) % numVM); // returns the vending machine according to what the student should be assigned to.
}


// Return a pointer to the vending machine array
 VendingMachine** NameServer::getMachineList(){
 	VendingMachine** temp = &arrayOfMachines.at(0);
 	return temp; // Return pointer to Vending Machine array, defined in driver.cc

}




 
