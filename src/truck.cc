#include "truck.h"

#include "MPRNG.h"
#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"

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
    prt.print( Printer::Truck, 'S' );
    // fetch all vending machines
    VendingMachine** vendingMachines = nameServer.getMachineList();
    int currentMachineIndex = -1;  // choose the next vending machine to restock

    for ( ;; ) {
        // coffee time
        yield( mprng( 1, 10 ) );

        // 1. Picking up shipment from bottling plant
        try {  // try to get shipment from plant
            plant.getShipment( cargo );
        } catch (
            BottlingPlant::Shutdown ) {  // catch and exit when plant shutdown
            break;
        }

        // 1.1 calculate total cargo number
        int totalCargo = 0;
        for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {
            totalCargo += cargo[i];
        }
        prt.print( Printer::Truck, 'P', totalCargo );  // print shipment info

        // 2. Starting restock vending machine
        for ( auto count = 0U; count < numVendingMachines; count++ ) {
            // calculate the next machine index
            currentMachineIndex
                = ( currentMachineIndex + 1 ) % numVendingMachines;

            if ( totalCargo == 0 ) {  // no more soda in cargo end loop
                break;
            }
            // 2.1 retrieve target machine id and inventory info
            VendingMachine* currentMachine
                = vendingMachines[currentMachineIndex];

            unsigned int machineId = currentMachine->getId();

            prt.print( Printer::Truck, 'd', machineId, totalCargo );

            unsigned int* inventory = currentMachine->inventory();

            // counter for not replenished soda
            unsigned int notReplenished = 0;
            // 2.2 start restock each flavor
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
            // 2.3 recalculate total bottle remaining
            totalCargo = 0;
            for ( auto i = 0U; i < NUMOFFLAVORS; i++ ) {
                totalCargo += cargo[i];
            }
            // 2.4 print not replenished soda if necessary
            if ( notReplenished > 0 ) {
                prt.print( Printer::Truck, 'U', machineId, notReplenished );
            }

            // 2.5 inform target machine restock finished
            currentMachine->restocked();

            prt.print( Printer::Truck, 'D', machineId, totalCargo );
        }
    }
    // 3. print finish message after plant shutdown
    prt.print( Printer::Truck, 'F' );
}
