#include "truck.h"
#include "printer.h"
#include "NameServer.h"
#include "plant.h"

/*
  purpose: constructor that initializes truck
  precondition: Printer NameServer BottlingPlant unsigned int unsigned int
  postcondition: Truck
*/
Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
             unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
{
     truck_printer = &prt;
     truck_server = &nameserver;
     truck_plant = &plant;      
     numMac = numVendingMachines;
     maxStock = maxStockPerFlavour;
            
     for(int i=0; i < 4; i += 1){
         list[i] = 0;
     }
     
     // printer prints that truck has started its job
     truck_printer->print(Printer::Truck, 'S');
}

/*
  purpose: destructor that indicates the end of truck's work
  precondition: NONE
  postcondition: Truck
*/
Truck::~Truck()
{
     truck_printer = NULL;
     truck_server = NULL;
     truck_plant = NULL;   
     numMac = 0;
     maxStock = 0;
            
     for(int i=0; i < 4; i += 1){
         list[i] = 0;
     }
     // printer prints that truck has finished its job
     truck_printer->print(Printer::Truck, 'F');
               
}

/*
  purpose: output how many sodas are there
  precondition: an array of unsigned int
  postcondition: int
*/
int how_many (unsigned int list[])
{
    int count = 0;
    for (int i = 0 ; i < 4 ; i += 1)
    {
        count += list[i]; 
    }
    return count;
}

/*
  purpose: truck deliever sodas to vending machines
  precondition: none
  postcondition: void
*/
void Truck::action()
{
     // get stocks from the plant
     truck_Plant->getShipment(list);
     truck_printer->print(truck_printer::Truck, 'P', how_many(list));
     
     // bring a list of vending machine from server
     VendingMachine** VendList = truck_server->getMachineList();
     for (unsigned int i = 0 ; i < numMac ; i += 1)
     {
        truck_printer->print(Printer::Truck, 'd', VendList[i]->getId(), how_many(list)); 
        
        unsigned int *curr_stock = VendList[i]->inventory();
        unsigned int not_enough = 0;
        for (unsigned int j = 0 ; j < 4 ; j += 1)
        {
            unsigned int how_many_needed = maxStock - curr_stock[j];
            if (list[j] > how_many_needed) // if we have enough sodas to fill the vendingmachine
            {
               list[j] -= how_many_needed;
               curr_stock[j] += how_many_needed;
            }
            else // if there is not enough soda, give as much as possible to the machine
            {
               not_enough += how_many_needed - list[j];
               curr_stock[j] += list[j];
               list[j] = 0;
            }
        }
        // printer prints that truck gave vending machine not enough supplies
        if (not_enough > 0)
        {
              truck_printer->print(Printer::Truck, 'U', VendList[i]->getId(), not_enough);          
        }
        
        // printer prints that truck finished delivering to current vending machine
        truck_printer->print(Printer::Truck, 'D', VendList[i]->getId(), how_many(list));
        // printer prints that vending machine has been restocked by truck
        curr_stock[i]->restocked();
        if (how_many(list) == 0) // if truck is out its supply, then finish its job.
        {
             delete[] VendList;
             return;                   
        }
     }
     
     delete[] VendList;   
}
