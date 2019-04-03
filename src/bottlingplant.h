#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "nameserver.h"
#include "printer.h"

extern const unsigned int NUMOFFLAVORS;

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
    unsigned int currentStock[NUMOFFLAVORS];  // array of stock for each flavor
    bool         shutDownFlag = false;
    void         main();

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