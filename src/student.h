#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "groupoff.h"
#include "nameserver.h"
#include "printer.h"
#include "watcardoffice.h"

_Task Student {
    void main();

   public:
    Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice,
             Groupoff & groupoff, unsigned int id, unsigned int maxPurchases );
};

#endif