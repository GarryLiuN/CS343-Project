#include "vendingmachine.h"

#include "MPRNG.h"
#include "nameserver.h"
#include "printer.h"
#include "watcard.h"

extern MPRNG mprng;

// -----------------------Public Methods-----------------------
VendingMachine::VendingMachine( Printer&     prt,
                                NameServer&  nameServer,
                                unsigned int id,
                                unsigned int sodaCost )
    : prt( prt ), nameServer( nameServer ), id( id ), sodaCost( sodaCost ) {}

void
VendingMachine::buy( Flavours flavour, WATCard& card ) {
    // copy parameter to local copy
    tempFlavor = flavour;
    tempCard   = &card;

    // move process logic back to main
    switchBack.wait();

    // throw exception is necessary
    switch ( flag ) {
        case ( Fundf ): {
            flag = Default;
            _Throw VendingMachine::Funds();
        }
        case ( Stockf ): {
            flag = Default;
            _Throw VendingMachine::Stock();
        }
        case ( Freef ): {
            flag = Default;
            _Throw VendingMachine::Free();
        }

        default:
            break;
    }
}

unsigned int*
VendingMachine::inventory() {
    restocking = true;
    return stock;
}

void
VendingMachine::restocked() {
    restocking = false;
}

_Nomutex unsigned int
VendingMachine::cost() const {
    return sodaCost;
}

_Nomutex unsigned int
VendingMachine::getId() const {
    return id;
}

void
VendingMachine::main() {
    prt.print( Printer::Vending, id, 'S', sodaCost );
    nameServer.VMregister( this );
    for ( ;; ) {
        _Accept( ~VendingMachine ) {
            break;
        }
        // during restocking accept restock call
        or _When( restocking ) _Accept( restocked ) {
            prt.print( Printer::Vending, id, 'R' );
        }
        // When not restocking accept inventory call
        or _When( !restocking ) _Accept( inventory ) {
            prt.print( Printer::Vending, id, 'r' );
        }
        // When not restocking accept buy call
        or _When( !restocking ) _Accept( buy ) {
            // Stage 1. Check fund and Soda
            unsigned int balance = tempCard->getBalance();
            if ( balance < sodaCost ) {
                flag = Fundf;
            } else if ( stock[tempFlavor] < 1 ) {
                flag = Stockf;
            } else {
                // Stage 1.2 check free
                if ( mprng( 4 ) == 0 ) {
                    flag = Freef;
                } else {
                    // Stage 2. debit on card when not free
                    flag = Default;
                    stock[tempFlavor] -= 1;
                    tempCard->withdraw( sodaCost );
                    prt.print( Printer::Vending,
                               id,
                               'B',
                               tempFlavor,
                               stock[tempFlavor] );
                }
            }

            // Stage 3. switch back to buy function
            switchBack.signalBlock();
        }
    }
    prt.print( Printer::Vending, id, 'F' );
}
