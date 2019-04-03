#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

#include "vector"

#include "printer.h"
#include "watcard.h"

_Task Groupoff {
   private:
    // references
    Printer& prt;
    // constant fields
    const unsigned int numStudents;
    const unsigned int sodaCost;
    const unsigned int groupoffDelay;
    // fields
    std::vector<WATCard::FWATCard> giftcards;
    std::vector<WATCard>           watcards;

    void main();

   public:
    Groupoff( Printer & prt,
              unsigned int numStudents,
              unsigned int sodaCost,
              unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};

#endif
