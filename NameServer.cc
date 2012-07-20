#include "NameServer.h"

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
	counter += 1;
 }
 

VendingMachine* NameServer::getMachine(unsigned int id){
	printerptr->print(Printer::NameServer, 'N', id, arrayOfMachines.at(id % numVM)->getId());
	return arrayOfMachines.at(id % numVM); // returns the vending machine according to what the student should be assigned to.
}


// Return a pointer to the vending machine array
VendingMachine** NameServer::getMachineList(){
  VendingMachine** temp = new VendingMachine*[numVM]; // create an arrray of 'numVM' pointers
  for (unsigned int i = 0 ; i < numVM ; i += 1)
  {
     temp[i] = arrayOfMachines.at(i); // convert vector into a pointer to array
  }
  return temp; // Return pointer to Vending Machine array, defined in driver.cc

}




 
