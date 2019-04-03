#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "nameserver.h"
#include "printer.h"
#include "watcard.h"

_Task VendingMachine {
   private:
    // references
    Printer&    prt;
    NameServer& nameServer;
    // attributes
    unsigned int id;
    unsigned int sodaCost;

    void main();

   public:
    enum Flavours {
        Blues_Black_Cherry,
        Classic_Cream_Soda,
        Rock_Root_Beer,
        Jazz_Lime
    };  // flavours of soda (YOU DEFINE)
    _Event Free{};  // free, advertisement
    _Event Funds{};  // insufficient funds
    _Event Stock{};  // out of stock for particular flavour
    VendingMachine( Printer & prt,
                    NameServer & nameServer,
                    unsigned int id,
                    unsigned int sodaCost );
    void                  buy( Flavours flavour, WATCard & card );
    unsigned int*         inventory();
    void                  restocked();
    _Nomutex unsigned int cost() const;
    _Nomutex unsigned int getId() const;
};

#endif