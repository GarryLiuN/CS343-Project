#include "bottlingplant.h"

#include "MPRNG.h"
#include "nameserver.h"
#include "printer.h"
#include "truck.h"

extern MPRNG mprng;

// -----------------------Public Methods-----------------------

// Constructor
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
      timeBetweenShipments( timeBetweenShipments ) {}

void
BottlingPlant::getShipment( unsigned int cargo[] ) {
    if ( isDestructed ) {
        _Throw Shutdown();
    }
    for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {
        cargo[i]        = currentStock[i];
        currentStock[i] = 0;
    }
}

// -----------------------Private Methods-----------------------
void
BottlingPlant::main() {
    prt.print( Printer::Kind::BottlingPlant, 'S' );

    Truck truck(
        prt, nameServer, *this, numVendingMachines, maxStockPerFlavour );

    // production run
    for ( ;; ) {
        yield( timeBetweenShipments );
        unsigned int totalProduction = 0;
        for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {  // generate soda per
                                                      // flavor
            currentStock[i] += mprng( maxShippedPerFlavour );
            totalProduction += currentStock[i];
        }

        prt.print( Printer::BottlingPlant, 'G', totalProduction );

        // after soda production, either destructor will be call to terminate
        // the o
        _Accept( ~BottlingPlant ) {
            // when destructor is called, update shut down flag and break loop
            isDestructed = true;

            break;
        }
        or _Accept( getShipment ) {
            prt.print( Printer::BottlingPlant, 'P' );
        }
    }
    // one extra accept block used to throw Shutdown event to the truck and
    // terminate the truck
    try {
        _Accept( getShipment ) {}
    } catch ( uMutexFailure::RendezvousFailure ) {
    }

    prt.print( Printer::BottlingPlant, 'F' );
}
