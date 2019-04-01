#include "watcardoffice.h"

#include "bank.h"
#include "printer.h"
#include "watcard.h"

WATCardOffice::WATCardOffice( Printer&     prt,
                              Bank&        bank,
                              unsigned int numCouriers )
    : prt( prt ), bank( bank ), numCouriers( numCouriers ) {}

WATCard::FWATCard
WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    return WATCard::FWATCard();
}

WATCard::FWATCard
WATCardOffice::transfer( unsigned int sid,
                         unsigned int amount,
                         WATCard*     card ) {
    return WATCard::FWATCard();
}

WATCardOffice::Job*
WATCardOffice::requestWork() {
    return nullptr;
}

void
WATCardOffice::main() {}
