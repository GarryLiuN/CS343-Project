#include "parent.h"

#include "bank.h"
#include "printer.h"

Parent::Parent( Printer&     prt,
                Bank&        bank,
                unsigned int numStudents,
                unsigned int parentalDelay )
    : prt( prt ),
      bank( bank ),
      numStudents( numStudents ),
      parentalDelay( parentalDelay ) {}

void
Parent::main() {}
