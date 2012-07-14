#include "plant.h"
#include "PRNG.h"
#include "truck.h"
#include "printer.h"
#include "nameserver.h"
PRNG prng;

/*
  purpose: constructor that intializes the plant.
           It creates a truck and then do production run
  precondition: none
  postcondition: none
*/
BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                            unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                            unsigned int timeBetweenShipments )
{
   plant_printer = &prt;
   plant_server = &nameserver;
   numMac = numVendingMachines;
   maxShip = maxShippedPerFlavour;
   numFla = maxStockPerFlavour;
   DeliveryTime = timeBetweenShipments;   
   
   printer->print(Printer::BottlingPlant, 'S'); 
   
    // It begins by creating a truck
    truck = new Truck(*plant_printer, *plant_server, *this, numMac, numFla );
    // performing a production run
    production_run();
    truck->action();                
}

/*
  purpose: destructor that destroys everything.
  precondition: none
  postcondition: none
*/
BottlingPlant::~BottlingPlant()
{
   plant_printer = NULL;
   plant_server = NULL;
   delete(truck);
   numMac = 0;
   maxShip = 0;
   numFla = 0;
   DeliveryTime = 0; 
   
    printer->print(Printer::BottlingPlant, 'F');                               
}

/*
  purpose: tranfer items of plant to truck
  precondition: an array of unsigned int
  postcondition: none
*/
void BottlingPlant::getShipment( unsigned int cargo[ ] )
{
     for (int i = 0 ; i < 4 ; i += 1)
     {
         cargo[i] = list[i];    
     }
     printer->print(Printer::BottlingPlant, 'P')
}

/*
  purpose: perform action based on probability.
          - there is 1/5 chance that the plant is on strike
          - there is 1/TimeBetweenShipments chance that truck has returned
  precondition: none
  postcondition: none
*/
void BottlingPlant::action()
{
     int on_strike = prng(1,5)
     if (on_strike == 1) // plant on strike
     {
        printer->print(Printer::BottlingPlant, 'X')
        return;         
     }
     else
     {
         int truck_return = prng(1, DeliveryTime);
         if (truck_return == 1)
         {
            truck-->action();  
            production_run();               
         }
         else
         {
             return;    
         }
     }
}

/*
  purpose: do production run. That is, it creates a random number of items for each flavour
  precondition: none
  postcondition: none
*/
void production_run()
{ 
    unsigned int total = 0; 
    for(int i=0; i<4; i += 1)
    {
        int rand_stock = prng(1,maxShip);
        list[i] = rand_stock;
        production_size += rand_stock;
    }
    printer->print(Printer::BottlingPlant, 'G', production_size); 
}
