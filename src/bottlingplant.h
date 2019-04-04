#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "nameserver.h"
#include "printer.h"

/**
 *@brief class BottlingPlant will manage soda production and load soda to the
 *truck
 */
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
    // isDestructed will be set to true after BP's destructor is called and next
    // getShipment will throw event ShutDown
    bool isDestructed = false;

    void main();

   public:
    // shutdown event will be thrown at truck to start its termination
    _Event Shutdown{};
    BottlingPlant( Printer & prt,
                   NameServer & nameServer,
                   unsigned int numVendingMachines,
                   unsigned int maxShippedPerFlavour,
                   unsigned int maxStockPerFlavour,
                   unsigned int timeBetweenShipments );
    /**
     * @brief getShipment will be called by truck and cargo is printer of the
     * truck's cargo bottling plant will fill the truck's cargo in the function
     * call.
     */
    void getShipment( unsigned int cargo[] );
};

#endif
