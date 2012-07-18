#include "truck.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"

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
     
     truck_printer->print(Printer::Truck, 'S');
}

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
     
     truck_printer->print(Printer::Truck, 'F');
               
}

int how_many (unsigned int list[])
{
    int count = 0;
    for (int i = 0 ; i < 4 ; i += 1)
    {
        count += list[i];    
    }
    return count;
}

void Truck::action()
{
     // get stocks from the plant
     truck_Plant->getShipment(list);
     truck_printer->print(truck_printer::Truck, 'P', how_many(list));
     
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
            else
            {
               not_enough += how_many_needed - list[j];
               curr_stock[j] += list[j];
               list[j] = 0;
            }
        }
        if (not_enough > 0)
        {
              truck_printer->print(Printer::Truck, 'U', VendList[i]->getId(), not_enough);          
        }
        
        truck_printer->print(Printer::Truck, 'D', VendList[i]->getId(), how_many(list));
        curr_stock[i]->restocked();
        if (how_many(list) == 0)
        {
             delete[] VendList;
             return;                   
        }
     }
     
     delete[] VendList;   
}
