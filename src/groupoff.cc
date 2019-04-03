#include "groupoff.h"

#include "printer.h"
#include "watcard.h"

#include "MPRNG.h"

extern MPRNG mprng;

Groupoff::Groupoff( Printer&     prt,
                    unsigned int numStudents,
                    unsigned int sodaCost,
                    unsigned int groupoffDelay )
    : prt( prt ),
      numStudents( numStudents ),
      sodaCost( sodaCost ),
      groupoffDelay( groupoffDelay ),
      giftcards( numStudents ),
      watcards( numStudents ) {}

WATCard::FWATCard
Groupoff::giftCard() {
    static unsigned int i = 0;
    return giftcards.at( i++ );
}

void
Groupoff::main() {
    prt.print( Printer::Groupoff, 'S' );

    for ( auto& watcard : watcards ) {
        watcard = new WATCard();
    }
    // 1. Wait for all student to call giftcard()
    for ( auto i = 0U; i < numStudents; ++i ) {
        _Accept( giftCard ){};
    }

    // 2. Start adding fund to giftcards
    for ( auto i = 0U; i < numStudents; ++i ) {
        _Accept( ~Groupoff ) {
            break;
        }
        _Else {
            // 2.1. yield before activate giftcard
            yield( groupoffDelay );
            // 2.2. get the WATCard and deposit sodaCost
            WATCard* watcard = watcards.at( i );
            watcard->deposit( sodaCost );
            // 2.3. assign WATCard to a random giftcard, then remove the card
            auto index = mprng( numStudents - i - 1 );
            giftcards.at( index ).delivery( watcard );
            giftcards.erase( giftcards.begin() + index );

            prt.print( Printer::Groupoff, 'D', sodaCost );
        }
    }

    // 3. Delete WATCards on heap
    for ( auto watcard : watcards ) {
        delete watcard;
    }

    prt.print( Printer::Groupoff, 'F' );
}
