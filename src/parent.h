#ifndef __PARENT_H__
#define __PARENT_H__

#include "bank.h"
#include "printer.h"

_Task Parent {
   private:
    // references
    Printer& prt;
    Bank&    bank;
    // attributes
    unsigned int numStudents;
    unsigned int parentalDelay;

    void main();

   public:
    ~Parent();
    Parent( Printer & prt,
            Bank & bank,
            unsigned int numStudents,
            unsigned int parentalDelay );
};

#endif
