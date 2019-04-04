#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "printer.h"
#include "watcard.h"

#define NUMOFFLAVORS 4

_Task NameServer;

/**
 * @brief VendingMachine class handles students' soda purchase request
 */

_Task VendingMachine {
   private:
    // references
    Printer&    prt;
    NameServer& nameServer;
    // attributes
    unsigned int id;
    unsigned int sodaCost;
    unsigned int stock[NUMOFFLAVORS] = {0};
    enum { Default, FundFlag, StockFlag, FreeFlag } flag;
    /**
     * @brief boolean restocking set to true when inventory is called and will
     * only accept restocked function call. Then restocking will be set to false
     * and accept inventory and buy function call
     */
    bool       restocking = false;
    uCondition switchBack;

    void main();

   public:
    enum Flavours {
        Blues_Black_Cherry,
        Classic_Cream_Soda,
        Rock_Root_Beer,
        Jazz_Lime
    };  // flavours of soda
    _Event Free{};  // free, advertisement
    _Event Funds{};  // insufficient funds
    _Event Stock{};  // out of stock for particular flavour
    VendingMachine( Printer & prt,
                    NameServer & nameServer,
                    unsigned int id,
                    unsigned int sodaCost );
    void buy( Flavours flavour, WATCard & card );
    /**
     * @brief inventory method is called by truck to acquire vm's stock level
     * and start restocking, so after the function call, restocking boolean will
     * be set to true.
     */
    unsigned int* inventory();
    /**
     * @brief restocked method is called by truck to notify vm that restocking
     * is finished Then restocking boolean is set to true and VM could start to
     * accept buy request or next restock request
     */

    void                  restocked();
    _Nomutex unsigned int cost() const;
    _Nomutex unsigned int getId() const;

   private:
    /**
     * @brief tempCard and tempFlavor are local copy for card and flavor that
     * buy function pass in
     */
    WATCard* tempCard;
    Flavours tempFlavor;
};

#endif
