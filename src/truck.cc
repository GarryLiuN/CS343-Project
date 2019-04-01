#include "truck.h"

#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"

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

void
Truck::main() {}
