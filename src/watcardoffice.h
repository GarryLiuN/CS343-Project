#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include <queue>
#include <vector>

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
        unsigned int      id;  // student id
        unsigned int      amount;  // amount of fund
        WATCard*          watcard;  // optional WATCard to transfer fund
        WATCard::FWATCard result;  // return future

        Job( unsigned int id, unsigned int amount, WATCard* watcard = nullptr )
            : id( id ), amount( amount ), watcard( watcard ) {}
    };

    _Task Courier {
       private:
        Bank&          bank;
        WATCardOffice& office;
        Printer&       prt;
        unsigned int   id;

        void main();

       public:
        Courier( Bank & bank,
                 WATCardOffice & office,
                 Printer & prt,
                 unsigned int id );
    };  // communicates with bank

    // private fields
    Job*             newJob = nullptr;
    std::queue<Job*> jobs;
    bool             isDestructed = false;
    // Task main
    void main();

   public:
    _Event Lost{};  // lost WATCard
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer(
        unsigned int sid, unsigned int amount, WATCard* card );
    Job* requestWork();
};

#endif
