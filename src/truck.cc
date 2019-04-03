#include "truck.h"

#include "MPRNG.h"
#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"
extern MPRNG mprng;

// -----------------------Public Methods-----------------------
Truck::Truck( Printer&       prt,
              NameServer&    nameServer,
              BottlingPlant& plant,
              unsigned int   numVendingMachines,
              unsigned int   maxStockPerFlavour )
    : prt( prt ),
      nameServer( nameServer ),
      plant( plant ),
      numVendingMachines( numVendingMachines ),
      maxStockPerFlavour( maxStockPerFlavour ) {}

// -----------------------Private Methods-----------------------
void
Truck::main() {
    prt.print( Printer::Truck, 'S' );  // print truck start message
    VendingMachine** vendingMachines
        = nameServer.getMachineList();  // fetch all vending machines
    int currentMachineIndex = -1;  // choose the next vending machine to restock

    for ( ;; ) {
        yield( mprng( 1, 10 ) );  // coffee time

        try {  // try to get shipment from plant
            plant.getShipment( cargo );
        } catch (
            BottlingPlant::Shutdown ) {  // catch and exit when plant shutdown
            break;
        }
        int totalCargo = 0;
        for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {
            totalCargo += cargo[i];
        }
        prt.print( Printer::Truck, 'P', totalCargo );  // print shipment info

        for ( auto count = 0U; count < numVendingMachines; count++ ) {
            // start the cyclic order restock

            // calculate the next machine index
            currentMachineIndex
                = ( currentMachineIndex + 1 ) % numVendingMachines;

            if ( totalCargo == 0 ) {  // no more soda in cargo
                break;
            }
            // get the target machine
            VendingMachine* currentMachine
                = vendingMachines[currentMachineIndex];
            // obtain the id of the target machine
            unsigned int machineId = currentMachine->getId();
            // print begin delivery message
            prt.print( Printer::Truck, 'd', id, totalCargo );

            // get target machine inventory
            unsigned int* inventory = currentMachine->inventory();
            // counter for not replenished soda
            unsigned int notReplenished = 0;
            // restock each flavor
            for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {
                if ( inventory[i] + cargo[i] >= maxStockPerFlavour ) {
                    cargo[i] -= ( maxStockPerFlavour - inventory[i] );
                    inventory[i] = maxStockPerFlavour;
                } else {
                    inventory[i] += cargo[i];
                    cargo[i] = 0;
                    notReplenished += ( maxStockPerFlavour - inventory[i] );
                }
            }
            // recalculate total bottle remaining
            totalCargo = 0;
            for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {
                totalCargo += cargo[i];
            }
            // print not replenished soda if necessary
            if ( notReplenished > 0 ) {
                prt.print( Printer::Truck, 'U', id, notReplenished );
            }
            currentMachine->restocked();

            prt.print( Printer::Truck, 'U', id, totalCargo );
        }
    }
    // print finish message after plant shutdown
    prt.print( Printer::Truck, 'F' );
}
