#include "bank.h"

// constructor for Bank
// student accounts need to be dynamically allocated since the student number is
// unknown at compile time
Bank::Bank( unsigned int numStudents ) {
    // array initialization
    studentAccounts = new unsigned int[numStudents];
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        studentAccounts[i] = 0;
    }
}

// deposit function will add the amount to the corresponding account
// inputs are guaranteed to be valid : id exists and amount is non-negative
void
Bank::deposit( unsigned int id, unsigned int amount ) {
    studentAccounts[id] += amount;
}

// withdraw function will withdraw from corresponding account
// may need to wait for deposit when insufficient fund for withdraw
// inputs are guaranteed to be valid : id exists and amount is non-negative
void
Bank::withdraw( unsigned int id, unsigned int amount ) {
    // wait until account has enough fund
    for ( ;; ) {
        _When( amount > studentAccounts[id] ) _Accept( deposit );
        if ( amount <= studentAccounts[id] ) {
            break;
        }
    }
    studentAccounts[id] -= amount;
}

// destructor for Bank, will deallocate space of student accounts
Bank::~Bank() {
    delete studentAccounts;
}
