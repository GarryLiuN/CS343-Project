#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include <queue>

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
    struct Job {
        unsigned int      id;  // student id
        unsigned int      amount;  // amount of fund
        WATCard*          watcard;  // optional WATCard to transfer fund
        WATCard::FWATCard result;  // return future

        Job( unsigned int id, unsigned int amount, WATCard* watcard = nullptr )
            : id( id ), amount( amount ), watcard( watcard ) {}
    };

    /**
     * @brief : Subtask handles WATCardOffice communication with bank.
     *
     * @bank    : reference to the bank object.
     * @office  : reference to the WATCardOffice who creates this courier
     * @printer : reference to the Printer for output
     * @id      : courier id; assigned by WATCardOffice
     */
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
    /**
     * @brief : Create a new WATCard and return FWATCard watcard future pointer.
     *          New card could be lost during transfering fund
     *
     * @return : a future pointer to the underlying WATCard
     *
     * @sid    : student id of the WATCard owner
     * @amound : amount to be tranfer to watcard after creation
     */
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    /**
     * @brief : Transfer amount to the WATCard card and return a FWATCard
     *          watcard future pointer points to it. New card could be lost
     * during transfering fund
     *
     * @return : a future pointer to the underlying WATCard
     *
     * @sid    : student id of the WATCard owner
     * @amound : amount to be tranfer to watcard after creation
     * @car    : WATCard to transfer fund to
     */
    WATCard::FWATCard transfer(
        unsigned int sid, unsigned int amount, WATCard* card );
    /**
     * @brief : Called by Couriers. Will assign new job to the Courier
     *
     * @return : a pointer to the job. If WATCardOffice is being detructed, a
     *           nullptr is returned
     */
    Job* requestWork();
};

#endif
