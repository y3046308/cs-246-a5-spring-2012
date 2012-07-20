#ifndef __TRUCK_H__
#define __TRUCK_H__
#include "printer.h"
#include "NameServer.h"
#include "plant.h"

class Truck {
      private:
             Printer *truck_printer;
             NameServer *truck_server;
             BottlingPlant *truck_Plant;
             // numMac = number of Vending Machine
             // maxStock = maximum number of stock available
             // list[4] = a list of stock for each flavour
             unsigned int numMac, maxStock, list[4];
      public:
             Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
             unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
             void action();
             ~Truck();
};

#endif
