#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "nameserver.h"
#include "printer.h"

_Task BottlingPlant {
    void main();
    // reference
    Printer & prt;
    NameServer & nameServer;
    // attribute
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
   public:
    _Event Shutdown{};  // shutdown plant
    BottlingPlant(
        Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
        unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
        unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif