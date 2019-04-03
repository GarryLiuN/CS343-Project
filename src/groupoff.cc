#include "groupoff.h"

#include "printer.h"
#include "watcard.h"

Groupoff::Groupoff( Printer&     prt,
                    unsigned int numStudents,
                    unsigned int sodaCost,
                    unsigned int groupoffDelay )
    : prt( prt ),
      numStudents( numStudents ),
      sodaCost( sodaCost ),
      groupoffDelay( groupoffDelay ) {}

WATCard::FWATCard
Groupoff::giftCard() {
    return WATCard::FWATCard();
}

void
Groupoff::main() {
    prt.print( Printer::Groupoff, 'S' );

    for ( ;; ) {
    }
}
