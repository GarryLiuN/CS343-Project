#include "vendingmachine.h"

#include "MPRNG.h"
#include "nameserver.h"
#include "printer.h"
#include "watcard.h"

extern MPRNG mprng;

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
        _Throw Funds();
    }

    if ( stock[flavour] < 1 ) {
        _Throw Stock();
    }

    // check free
}

unsigned int*
VendingMachine::inventory() {}

void
VendingMachine::restocked() {}

_Nomutex unsigned int
VendingMachine::cost() const {}

_Nomutex unsigned int
VendingMachine::getId() const {}

void
VendingMachine::main() {}
