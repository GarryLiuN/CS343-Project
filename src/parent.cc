#include "parent.h"

#include "bank.h"
#include "printer.h"
extern MPRNG mprng;

Parent::Parent( Printer&     prt,
                Bank&        bank,
                unsigned int numStudents,
                unsigned int parentalDelay )
    : prt( prt ),
      bank( bank ),
      numStudents( numStudents ),
      parentalDelay( parentalDelay ) {}

Parent::~Parent() {
    prt.print( Printer::Kind::Parent, 'F' );  // print terminate message
}
void
Parent::main() {
    prt.print( Printer::Kind::Parent, 'S' );  // print start message for parent
    for ( ;; ) {
        _Accept( ~Parent ) {  // check for call to terminate
            break;
        }
        _Else {
            yield( parentalDelay );  // yields for parentalDelay times
            unsigned int randomId
                = mprng( 0, numStudents - 1 );  // generate random student id
            unsigned int randomDeposit
                = mprng( 1, 3 );  // generate random deposit amount
            bank.deposit( randomId, randomDeposit );  // make bank deposit
            prt.print( Printer::Kind::Parent,
                       'D',
                       randomId,
                       randomDeposit );  // print deposit message
        };
    }
}