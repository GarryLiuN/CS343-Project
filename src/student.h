#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "groupoff.h"
#include "nameserver.h"
#include "printer.h"
#include "watcardoffice.h"

#define WATCARD_BALANCE 5

_Task Student {
   private:
    // references
    Printer&       prt;
    NameServer&    nameServer;
    WATCardOffice& cardOffice;
    Groupoff&      groupoff;
    // attributes
    unsigned int id;
    unsigned int maxPurchases;

    void main();

   public:
    /**
     * @brief : Constructor for Student. Will assign corresponding fields with
     * parameters. maxPurchases will be generated using mprng(1, maxPurchases)
     */
    Student( Printer & prt,
             NameServer & nameServer,
             WATCardOffice & cardOffice,
             Groupoff & groupoff,
             unsigned int id,
             unsigned int maxPurchases );
};

#endif
