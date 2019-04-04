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
    // Stage 1. Check fund and Soda
    unsigned int balance = card.getBalance();
    if ( balance < sodaCost ) {
        flagType = 1;
        _Throw Funds();
    }

    if ( stock[flavour] < 1 ) {
        flagType = 2;
        _Throw Stock();
    }

    // Stage 1.2 check free
    if ( mprng( 4 ) == 0 ) {
        flagType = 3;
        _Throw Free();
    }

    // Stage 2. debit on card
    stock[flavour] -= 1;
    card.withdraw( sodaCost );
    prt.print( Printer::Vending, 'B', flavour, stock[flavour] );
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
    prt.print( Printer::Vending, 'S', sodaCost );
    nameServer.VMregister( this );
    for ( ;; ) {
        _Accept( ~VendingMachine ) {
            break;
        }
        // during restocking accept restock call
        or _When(restocking) _Accept(restocked){

        }
        // When not restocking accept inventory call
        or _When(!restocking) _Accept(inventory){

        }
        // When not restocking accept buy call
        or _When(!restocking) _Accept(buy){

        }
    }
    prt.print( Printer::Vending, 'F' );
}
