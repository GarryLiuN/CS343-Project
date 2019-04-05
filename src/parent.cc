#include "parent.h"

#include "MPRNG.h"

#include "bank.h"
#include "printer.h"

extern MPRNG mprng;

// -----------------------Public Methods-----------------------

Parent::Parent( Printer&     prt,
                Bank&        bank,
                unsigned int numStudents,
                unsigned int parentalDelay )
    : prt( prt ),
      bank( bank ),
      numStudents( numStudents ),
      parentalDelay( parentalDelay ) {}

Parent::~Parent() {
    prt.print( Printer::Kind::Parent, 'F' );
}

// -----------------------Private Methods-----------------------

void
Parent::main() {
    prt.print( Printer::Kind::Parent, 'S' );

    // start feed loop
    for ( ;; ) {
        _Accept( ~Parent ) {  // check for call to terminate
            break;
        }
        _Else {
            yield( parentalDelay );

            unsigned int randomId = mprng( 0, numStudents - 1 );

            unsigned int randomDeposit = mprng( 1, 3 );

            bank.deposit( randomId, randomDeposit );  // make bank deposit

            prt.print( Printer::Kind::Parent, 'D', randomId, randomDeposit );
        };
    }
}
