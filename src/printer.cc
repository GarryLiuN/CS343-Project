#include "printer.h"

#include <iostream>  // access: cin, cout, cerr, endl
#include <vector>
using namespace std;

// -----------------------Forward Declarations-----------------------
void print_tabs( unsigned int& tabs_printed, unsigned int tabs_needed );

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
    if ( infoptr->dirty ) {
        flush();
    }
    infoptr->state = state;
    infoptr->val1  = value1;
    infoptr->dirty = true;
}

void
Printer::print( Kind kind, char state, int value1, int value2 ) {
    Printer::Info* infoptr = get_info( kind );
    if ( infoptr->dirty ) {
        flush();
    }
    infoptr->state = state;
    infoptr->val1  = value1;
    infoptr->val2  = value2;
    infoptr->dirty = true;
}

void
Printer::print( Kind kind, unsigned int lid, char state ) {
    Printer::Info* infoptr = get_info( kind, lid );
    if ( infoptr->dirty ) {
        flush();
    }
    infoptr->state = state;
    infoptr->dirty = true;
}

void
Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    Printer::Info* infoptr = get_info( kind, lid );
    if ( infoptr->dirty ) {
        flush();
    }
    infoptr->state = state;
    infoptr->val1  = value1;
    infoptr->dirty = true;
}

void
Printer::print( Kind         kind,
                unsigned int lid,
                char         state,
                int          value1,
                int          value2 ) {}

// -----------------------Private Methods-----------------------
void
Printer::flush() {
    auto tabs_printed = 0U;
    auto tabs_needed  = 0U;

    // print Parent State
    if ( parent.dirty ) {
        print_tabs( tabs_printed, tabs_needed );
        print_info( parent );
    }
    // print Groupoff State
    tabs_needed++;
    if ( groupoff.dirty ) {
        print_tabs( tabs_printed, tabs_needed );
        print_info( groupoff );
    }
    // print WATCardOffice State
    tabs_needed++;
    if ( watoff.dirty ) {
        print_tabs( tabs_printed, tabs_needed );
        print_info( watoff );
    }
    // print NameServer State
    tabs_needed++;
    if ( names.dirty ) {
        print_tabs( tabs_printed, tabs_needed );
        print_info( names );
    }
    // print Truck State
    tabs_needed++;
    if ( truck.dirty ) {
        print_tabs( tabs_printed, tabs_needed );
        print_info( truck );
    }
    // print BottlingPlant State
    tabs_needed++;
    if ( plant.dirty ) {
        print_tabs( tabs_printed, tabs_needed );
        print_info( plant );
    }
    // print Students State
    for ( auto& student : students ) {
        tabs_needed++;
        if ( student.dirty ) {
            print_tabs( tabs_printed, tabs_needed );
            print_info( student );
        }
    }
    // print VendingMachines State
    for ( auto& machine : machines ) {
        tabs_needed++;
        if ( machine.dirty ) {
            print_tabs( tabs_printed, tabs_needed );
            print_info( machine );
        }
    }
    // print Couriers State
    for ( auto& courier : couriers ) {
        tabs_needed++;
        if ( courier.dirty ) {
            print_tabs( tabs_printed, tabs_needed );
            print_info( courier );
        }
    }
    cout << '\n';
}

void
Printer::print_info( Printer::Info& info ) {
    cout << info.state;
    if ( info.val1 != -1 ) {
        cout << info.val1;
        info.val1 = -1;
    }
    if ( info.val2 != -1 ) {
        cout << ',' << info.val2;
        info.val2 = -1;
    }

    info.dirty = false;
}

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
            cerr << "Invalid kind" << endl;
            return nullptr;
    }
}

// -----------------------Free Helper Functions-----------------------
void
print_tabs( unsigned int& tabs_printed, unsigned int tabs_needed ) {
    for ( ; tabs_printed < tabs_needed; ++tabs_printed ) {
        cout << '\t';
    }
}
