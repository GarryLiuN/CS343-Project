#ifndef __WATCARD_H__
#define __WATCARD_H__

#include <uFuture.h>

class WATCard {
   private:
    unsigned int balance;
    WATCard( const WATCard& ) = delete;  // prevent copying
    WATCard& operator=( const WATCard& ) = delete;

   public:
    typedef Future_ISM<WATCard*> FWATCard;  // future watcard pointer
    /**
     * @brief : WATCard constructor. balance will be initialized to 0
     */
    WATCard();
    /**
     * @brief : public interface for adding fund to watcard
     * @amount : amount to be added to balance
     */
    void deposit( unsigned int amount );
    /**
     * @brief : public interface for withdrawing fund from watcard
     * @amount : amount to be reduced from balance
     */
    void withdraw( unsigned int amount );
    /**
     * @brief : public interface for retrieve current balance
     * @return : a copy of balance
     */
    unsigned int getBalance();
};

#endif
