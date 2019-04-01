#include "truck.h"

#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"

Truck::Truck( Printer&       prt,
              NameServer&    nameServer,
              BottlingPlant& plant,
              unsigned int   numVendingMachines,
              unsigned int   maxStockPerFlavour ) {}

void
Truck::main() {}