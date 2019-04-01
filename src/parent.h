#ifndef __PARENT_H__
#define __PARENT_H__

#include "bank.h"
#include "printer.h"

_Task Parent {
   private:
    void         main();
    Printer&     prt;
    Bank&        bank;
    unsigned int numStudents;
    unsigned int parentalDelay;

   public:
    Parent( Printer & prt, Bank & bank, unsigned int numStudents,
            unsigned int parentalDelay );
};

#endif