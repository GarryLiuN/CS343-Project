#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

#include "printer.h"
#include "watcard.h"

_Task Groupoff {
   private:
    // references
    Printer& prt;
    // fields
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDelay;

    void main();

   public:
    Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost,
              unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};

#endif