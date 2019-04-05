#include "bank.h"

// -----------------------Public Methods-----------------------

Bank::Bank( unsigned int numStudents ) : numStudents( numStudents ) {
    // array initialization
    studentAccounts = new unsigned int[numStudents];
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        studentAccounts[i] = 0;
    }
}

void
Bank::deposit( unsigned int id, unsigned int amount ) {
    studentAccounts[id] += amount;
}

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
