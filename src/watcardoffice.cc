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
    if ( isDestructed ) {  // system shutdown
        return nullptr;
    }

    if ( jobs.empty() ) {
        cond_jobs.wait();  // when there's no job, block here
        // could be waken up due to system shutdown
        if ( isDestructed ) {
            return nullptr;
        }
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
        couriers[i] = new Courier( bank, *this, prt, i );
    }

    for ( ;; ) {
        _Accept( ~WATCardOffice ) {
            isDestructed = true;
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

    // signal all couriers and wait to delete them
    while ( !cond_jobs.empty() ) {
        cond_jobs.signal();
    }
    for ( auto i = 0U; i < numCouriers; ++i ) {
        delete couriers[i];
    }

    prt.print( Printer::Kind::WATCardOffice, 'F' );
}  // WATCardOffice::main()

// ***********************Courier***********************

WATCardOffice::Courier::Courier( Bank&          bank,
                                 WATCardOffice& office,
                                 Printer&       prt,
                                 unsigned int   id )
    : bank( bank ), office( office ), prt( prt ), id( id ) {}

void
WATCardOffice::Courier::main() {
    prt.print( Printer::Courier, 'S' );

    for ( ;; ) {
    }

}  // WATCardOffice::Courier::create()
