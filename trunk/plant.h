#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__
#include "printer.h"
#include "nameserver.h"
#include "truck.h"

class BottlingPlant {
      private:
                Printer *plant_printer;
                NameServer *plant_server;
                Truck *truck;
                unsigned int numMac, maxShip, numFla, DeliveryTime, list[4];
                void production_run();
      public:
             BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                            unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                            unsigned int timeBetweenShipments );
             void getShipment( unsigned int cargo[ ] );
             void action();
             ~BottlingPlant();
};

#endif
