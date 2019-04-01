#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "bank.h"
#include "printer.h"
#include "watcard.h"

_Task WATCardOffice {
   private:
    // references
    Printer& prt;
    Bank&    bank;
    // attributes
    unsigned int numCouriers;
    // classes and structures
    struct Job {  // marshalled arguments and return future
        // TODO Define args, give it a proper type
        int               args;  // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;  // return future
        Job( int args ) : args( args ) {}
    };

    _Task Courier{
        // TODO
    };  // communicates with bank

    void main();

   public:
    _Event Lost{};  // lost WATCard
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount,
                                WATCard* card );
    Job*              requestWork();
};

#endif