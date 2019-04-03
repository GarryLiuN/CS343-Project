#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "printer.h"
#include "watcard.h"

#define NUMOFFLAVORS 4

_Task NameServer;

_Task VendingMachine {
   private:
    // references
    Printer&    prt;
    NameServer& nameServer;
    // attributes
    unsigned int id;
    unsigned int sodaCost;
    unsigned int stock[NUMOFFLAVORS] = {0};
    unsigned int flagType = 0;  // default: 0, Funds: 1, Stock: 2, Free: 3

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
