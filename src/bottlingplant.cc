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

// getShipment will be called by truck and deliver current stock to the cargo
void
BottlingPlant::getShipment( unsigned int cargo[] ) {
    if ( shutDownFlag ) {
        _Throw Shutdown();
    }
    for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {
        cargo[i]        = currentStock[i];
        currentStock[i] = 0;
    }
}

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
        yield( timeBetweenShipments );
        unsigned int totalProduction = 0;
        for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {  // generate soda per
                                                      // flavor
            currentStock[i] += mprng( maxShippedPerFlavour );
            totalProduction += currentStock[i];
        }
        prt.print( Printer::BottlingPlant,
                   'G',
                   totalProduction );  // print soda generation message

        _Accept( ~BottlingPlant ) {
            shutDownFlag = true;  // update shut down flag and break loop

            break;
        }
        or _Accept( getShipment ) {
            prt.print( Printer::BottlingPlant, 'P' );  // print pickup message
        }
    }
    try {
        _Accept( getShipment ) {}
    } catch ( uMutexFailure::RendezvousFailure ) {
    }

    prt.print( Printer::BottlingPlant,
               'F' );  // print bottling plant finish message
}
