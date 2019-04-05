#ifndef __BANK_H__
#define __BANK_H__

/**
 * @brief class Bank handles all student account information abnd operations
 * including deposit and withdraw
 */
_Monitor Bank {
   private:
    unsigned int numStudents;

    /**
     *  studentAccounts need to be dynamically allocated
     *  since the student number is unknown at compile time
     */
    unsigned int* studentAccounts;

   public:
    Bank( unsigned int numStudents );
    /**
     * @brief  deposit function will add the amount to the corresponding account
     * inputs are guaranteed to be valid : id exists and amount is non-negative
     */
    void deposit( unsigned int id, unsigned int amount );

    /**
     * @brief withdraw function will withdraw from corresponding account may
     * need to wait for deposit when insufficient fund for withdraw inputs are
     * guaranteed to be valid : id exists and amount is non-negative
     */
    void withdraw( unsigned int id, unsigned int amount );
    // add public destructor since we need to deallocate space of the student
    // accounts
    ~Bank();
};

#endif
