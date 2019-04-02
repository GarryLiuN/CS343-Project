#include "printer.h"

#include <iostream>  // access: cin, cout, cerr, endl
#include <vector>
using namespace std;

// -----------------------Public Methods-----------------------

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
    for ( auto i = 0U; i < numStudents; ++i ) {
        cout << "Stud" << i << "\t";
    }
    for ( auto i = 0U; i < numVendingMachines; ++i ) {
        cout << "Mach" << i << "\t";
    }
    for ( auto i = 0U; i < numCouriers; ++i ) {
        if ( i != 0 ) {
            cout << '\t';
        }
        cout << "Cour" << i;
    }
    cout << '\n';

    auto total_cols = 6U + numStudents + numVendingMachines + numCouriers;

    for ( auto i = 0U; i < total_cols; ++i ) {
        if ( i != 0 ) {
            cout << '\t';
        }
        cout << "*******";
    }
    cout << '\n';
}

Printer::~Printer() {
    flush();
    cout << "***********************" << endl;
}

void
Printer::print( Kind kind, char state ) {
    Printer::Info* infoptr = get_info( kind );
    if ( infoptr->dirty ) {
        flush();
    }
    infoptr->state = state;
    infoptr->dirty = true;
}

void
Printer::print( Kind kind, char state, int value1 ) {
    Printer::Info* infoptr = get_info( kind );
}

void
Printer::print( Kind kind, char state, int value1, int value2 ) {
    Printer::Info* infoptr = get_info( kind );
}

void
Printer::print( Kind kind, unsigned int lid, char state ) {
    Printer::Info* infoptr = get_info( kind, lid );
}

void
Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    Printer::Info* infoptr = get_info( kind, lid );
}

void
Printer::print( Kind         kind,
                unsigned int lid,
                char         state,
                int          value1,
                int          value2 ) {}

// -----------------------Private Methods-----------------------
void
Printer::flush() {}

Printer::Info*
Printer::get_info( Kind kind, unsigned int id ) {
    switch ( kind ) {
        case Parent:
            return &parent;
        case Groupoff:
            return &groupoff;
        case WATCardOffice:
            return &watoff;
        case NameServer:
            return &watoff;
        case Truck:
            return &truck;
        case BottlingPlant:
            return &plant;
        case Student:
            return &students.at( id );
        case Vending:
            return &machines.at( id );
        case Courier:
            return &couriers.at( id );
        default:
            cerr << "invalid kind" << endl;
            return nullptr;
    }
}
