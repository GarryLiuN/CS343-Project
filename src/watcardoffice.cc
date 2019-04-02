#include "watcardoffice.h"

#include "bank.h"
#include "printer.h"
#include "watcard.h"

#include "MPRNG.h"

extern MPRNG mprng;

// ***********************WATCardOffice***********************

WATCardOffice::WATCardOffice( Printer&     prt,
                              Bank&        bank,
                              unsigned int numCouriers )
    : prt( prt ), bank( bank ), numCouriers( numCouriers ) {}

WATCard::FWATCard
WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    newJob = new Job( bank, sid, amount );
    return newJob->result;
}  // WATCardOffice::create()

WATCard::FWATCard
WATCardOffice::transfer( unsigned int sid,
                         unsigned int amount,
                         WATCard*     card ) {
    newJob = new Job( bank, sid, amount, card );
    return newJob->result;
}  // WATCardOffice::transfer()

WATCardOffice::Job*
WATCardOffice::requestWork() {
    if ( jobs.empty() ) {
        cond_jobs.wait();  // when there's no job, block here
    }
    WATCardOffice::Job* job = jobs.front();
    jobs.pop();
    return job;
}  // WATCardOffice::requestWork()

void
WATCardOffice::main() {
    prt.print( Printer::WATCardOffice, 'S' );

    Courier* couriers[numCouriers];
    for ( auto i = 0U; i < numCouriers; ++i ) {
        couriers[i] = new Courier( *this, prt, i );
    }

    for ( ;; ) {
        _Accept( ~WATCardOffice ) {
            break;
        }
        or _Accept( create ) {
            break;
        }
        or _Accept( transfer ) {
            break;
        }
        or _Accept( requestWork ) {
            break;
        }
    }

    for ( auto i = 0U; i < numCouriers; ++i ) {
        delete couriers[i];
    }
}  // WATCardOffice::main()

// ***********************Courier***********************

WATCardOffice::Courier::Courier( WATCardOffice& office,
                                 Printer&       prt,
                                 unsigned int   id )
    : office( office ), prt( prt ), id( id ) {}

void
WATCardOffice::Courier::main() {
    prt.print( Printer::Courier, 'S' );

}  // WATCardOffice::Courier::create()
