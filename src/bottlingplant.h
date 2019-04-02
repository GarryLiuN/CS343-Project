#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "nameserver.h"
#include "printer.h"

_Task BottlingPlant {
   private:
    // references
    static const unsigned int NUMOFFLAVORS = 4;
    Printer&                  prt;
    NameServer&               nameServer;
    // fields
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int currentStock[NUMOFFLAVORS];  // array of stock for each flavor
    bool         shutDownFlag;
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