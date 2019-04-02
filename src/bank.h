#ifndef __BANK_H__
#define __BANK_H__

_Monitor Bank {
   private:
    unsigned int  numStudents;
    unsigned int* studentAccounts;

   public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
    ~Bank();  // add public destructor since we need to deallocate space of the
              // student accounts
};

#endif