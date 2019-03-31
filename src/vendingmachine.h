#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

_Task VendingMachine {
    void main();

   public:
    enum Flavours {... };  // flavours of soda (YOU DEFINE)
    _Event Free{};  // free, advertisement
    _Event Funds{};  // insufficient funds
    _Event Stock{};  // out of stock for particular flavour
    VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id,
                    unsigned int sodaCost );
    void                  buy( Flavours flavour, WATCard & card );
    unsigned int*         inventory();
    void                  restocked();
    _Nomutex unsigned int cost() const;
    _Nomutex unsigned int getId() const;
};

#endif