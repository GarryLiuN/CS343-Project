#include "student.h"

#include "groupoff.h"
#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"
#include "watcard.h"
#include "watcardoffice.h"

#include "MPRNG.h"

extern MPRNG mprng;

Student::Student( Printer&       prt,
                  NameServer&    nameServer,
                  WATCardOffice& cardOffice,
                  Groupoff&      groupoff,
                  unsigned int   id,
                  unsigned int   maxPurchases )
    : prt( prt ),
      nameServer( nameServer ),
      cardOffice( cardOffice ),
      groupoff( groupoff ),
      id( id ),
      maxPurchases( mprng( 1, maxPurchases ) ) {}

void
Student::main() {
    // 1. Setting up
    // 1.1. create favorate flavour
    VendingMachine::Flavours flavour
        = (VendingMachine::Flavours)mprng( NUMOFFLAVORS - 1 );
    prt.print( Printer::Student, id, 'S', (int)flavour, maxPurchases );
    // 1.2 create WATCard
    WATCard::FWATCard watcard = cardOffice.create( id, WATCARD_BALANCE );
    // 1.3 create giftcard
    WATCard::FWATCard giftcard = groupoff.giftCard();
    // 1.4 obtain a vending machine
    VendingMachine* vendingMachine = nameServer.getMachine( id );

    prt.print( Printer::Student, id, 'V', vendingMachine->getId() );

    // 2. Start purchasing sodas
    for ( unsigned int purchased = 0; purchased < maxPurchases; ) {
        yield( mprng( 1, 10 ) );
        for ( ;; ) {  // for skipping yield when failed purchase
            try {
                _Select( watcard ) {
                    try {
                        // 2.a.1 attempt to purchase with watcard
                        vendingMachine->buy( flavour, *watcard() );
                        purchased++;
                        prt.print( Printer::Student,
                                   id,
                                   'B',
                                   flavour,
                                   watcard()->getBalance() );
                        break;
                    } catch ( VendingMachine::Free& ) {
                        // yield 4 times for free soda
                        for ( int i = 0; i < 4; ++i ) {
                            yield();
                        }
                        purchased++;
                        prt.print( Printer::Student,
                                   id,
                                   'A',
                                   flavour,
                                   watcard()->getBalance() );
                        break;
                    } catch ( VendingMachine::Funds& ) {
                        watcard = cardOffice.transfer(
                            id,
                            vendingMachine->cost() + WATCARD_BALANCE,
                            watcard() );
                        break;
                        ;
                    } catch ( WATCardOffice::Lost& ) {
                        prt.print( Printer::Student, id, 'L' );
                        watcard = cardOffice.create( id, WATCARD_BALANCE );
                        continue;
                    }  // try (watcard)
                }  // _Select( watcard )
                or _Select( giftcard ) {
                    try {
                        // 2.b.1 attempt to purchase with giftcard
                        vendingMachine->buy( flavour, *giftcard() );
                        // 2.b.2 success purchased a soda
                        purchased++;
                        prt.print( Printer::Student,
                                   id,
                                   'G',
                                   flavour,
                                   giftcard()->getBalance() );
                        giftcard.reset();  // giftcard should be only used once
                        break;
                    } catch ( VendingMachine::Free& ) {
                        // yield 4 times for free soda
                        for ( int i = 0; i < 4; ++i ) {
                            yield();
                        }
                        purchased++;
                        prt.print( Printer::Student,
                                   id,
                                   'a',
                                   flavour,
                                   giftcard()->getBalance() );
                        break;
                    }  // try (giftcard)
                }  // _Select( giftcard )
            } catch ( VendingMachine::Stock& ) {
                vendingMachine = nameServer.getMachine( id );
                prt.print( Printer::Student, id, 'V', vendingMachine->getId() );
                break;
            }  // try
        }  // for(;;)
    }  // for

    try {
        delete watcard();
    } catch ( ... ) {
    }

    // 3. Finish
    prt.print( Printer::Student, id, 'F' );
}
