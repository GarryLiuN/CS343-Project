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
    newJob = new Job( sid, amount );
    prt.print( Printer::WATCardOffice, 'C', sid, amount );
    return newJob->result;
}  // WATCardOffice::create()

WATCard::FWATCard
WATCardOffice::transfer( unsigned int sid,
                         unsigned int amount,
                         WATCard*     card ) {
    newJob = new Job( sid, amount, card );
    prt.print( Printer::WATCardOffice, 'T', sid, amount );
    return newJob->result;
}  // WATCardOffice::transfer()

WATCardOffice::Job*
WATCardOffice::requestWork() {
    if ( isDestructed ) {  // system shutdown
        return nullptr;
    }

    Job* job = jobs.front();
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
        or _When( !jobs.empty() ) _Accept( requestWork ) {
            // only accept requestWork when there are jobs
            jobs.pop();  // for greater concurrency
            prt.print( Printer::WATCardOffice, 'W' );
        }
        or _Accept( create, transfer ) {
            // always accepts new jobs
            jobs.push( newJob );  // for greater concurrency
        }
    }  // for

    for ( auto i = 0U; i < numCouriers; ++i ) {
        _Accept( requestWork ) {}
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
        // 1. requestWork from WATCardOffice
        Job* job = office.requestWork();
        if ( !job ) {
            // no job returned, terminates
            break;
        }

        if ( !job->watcard ) {
            // create WATCard if no card provided
            job->watcard = new WATCard();
        }
        prt.print( Printer::Courier, id, 't', job->id, job->amount );

        // 2. Withdraw amount from the bank
        bank.withdraw( job->id, job->amount );
        // 3. Deposit amount to the WATCard
        job->watcard->deposit( job->amount );

        // 4. Lose card or complete transfer
        if ( mprng( 5 ) == 0 ) {  // 1 in 6 chance courier loses the card
            // Lost the card
            prt.print( Printer::Courier, id, 'L' );
            delete job->watcard;
            job->result.exception( new Lost() );
        } else {
            prt.print( Printer::Courier, id, 'T', job->id, job->amount );
            job->result.delivery( job->watcard );
        }

        // 5. delete completed job
        delete job;
    }  // for

    prt.print( Printer::Courier, id, 'F' );
}  // WATCardOffice::Courier::main()
