#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "nameserver.h"
#include "printer.h"

_Task BottlingPlant {
   private:
    // references
    Printer&    prt;
    NameServer& nameServer;
    // fields
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int currentStock[NUMOFFLAVORS] = {0};  // stock for each flavor
    bool         isDestructed               = false;

    void main();

   public:
    _Event Shutdown{};  // shutdown plant
    BottlingPlant( Printer & prt,
                   NameServer & nameServer,
                   unsigned int numVendingMachines,
                   unsigned int maxShippedPerFlavour,
                   unsigned int maxStockPerFlavour,
                   unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif
