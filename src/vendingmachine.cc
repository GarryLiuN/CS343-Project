#include "vendingmachine.h"

#include "nameserver.h"
#include "printer.h"
#include "watcard.h"

VendingMachine::VendingMachine( Printer&     prt,
                                NameServer&  nameServer,
                                unsigned int id,
                                unsigned int sodaCost ) {}

void
VendingMachine::buy( Flavours flavour, WATCard& card ) {}

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
