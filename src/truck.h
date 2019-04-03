#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"

_Task Truck {
   private:
    // references
    Printer&       prt;
    NameServer&    nameServer;
    BottlingPlant& plant;
    // attributes
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    unsigned int cargo[NUMOFFLAVORS] = {0};

    void main();

   public:
    Truck( Printer & prt,
           NameServer & nameServer,
           BottlingPlant & plant,
           unsigned int numVendingMachines,
           unsigned int maxStockPerFlavour );
};

#endif
