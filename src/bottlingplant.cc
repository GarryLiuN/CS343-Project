#include "bottlingplant.h"

#include "nameserver.h"
#include "printer.h"

BottlingPlant::BottlingPlant( Printer&     prt,
                              NameServer&  nameServer,
                              unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour,
                              unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments )
    : prt( prt ),
      nameServer( nameServer ),
      numVendingMachines( numVendingMachines ),
      maxShippedPerFlavour( maxShippedPerFlavour ),
      maxStockPerFlavour( maxStockPerFlavour ),
      timeBetweenShipments( timeBetweenShipments ) {
    currentStock = 0;
}

void
BottlingPlant::getShipment( unsigned int cargo[] ) {}

void
BottlingPlant::main() {
    prt.print( Printer::Kind::BottlingPlant,
               'S' );  // print start message for bottling plant
    Truck truck( prt,
                 nameServer,
                 *this,
                 numVendingMachines,
                 maxStockPerFlavour );  // create truck

    // production run
    for ( ;; ) {
    }
}
