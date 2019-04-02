#include "printer.h"

#include <iostream>  // access: cin, cout, cerr, endl
using namespace std;

Printer::Printer( unsigned int numStudents,
                  unsigned int numVendingMachines,
                  unsigned int numCouriers )
    : numStudents( numStudents ),
      numVendingMachines( numVendingMachines ),
      numCouriers( numCouriers ),
      students( numStudents ),
      machines( numVendingMachines ),
      couriers( numCouriers ) {
    cout << "Parent\tGropoff\tWATOff\tNames\tTruck\tPlant\t";
    for ( unsigned int i = 0; i < numStudents; ++i ) {
        cout << "Stud" << i << "\t";
    }
    for ( unsigned int i = 0; i < numVendingMachines; ++i ) {
        cout << "Mach" << i << "\t";
    }
    for ( unsigned int i = 0; i < numCouriers; ++i ) {
        if ( i != 0 ) {
            cout << '\t';
        }
        cout << "Cour" << i;
    }
    cout << '\n';

    unsigned int total_cols
        = 6 + numStudents + numVendingMachines + numCouriers;

    for ( unsigned int i = 0; i < total_cols; ++i ) {
        if ( i != 0 ) {
            cout << '\t';
        }
        cout << "*******";
    }
    cout << '\n';
}

void
Printer::print( Kind kind, char state ) {}

void
Printer::print( Kind kind, char state, int value1 ) {}

void
Printer::print( Kind kind, char state, int value1, int value2 ) {}

void
Printer::print( Kind kind, unsigned int lid, char state ) {}
void
Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {}

void
Printer::print( Kind         kind,
                unsigned int lid,
                char         state,
                int          value1,
                int          value2 ) {}
