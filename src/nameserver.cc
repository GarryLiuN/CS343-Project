#include <iostream>
using namespace std;

#include "nameserver.h"

#include "printer.h"
#include "vendingmachine.h"

// -----------------------Public Methods-----------------------
NameServer::NameServer( Printer&     prt,
                        unsigned int numVendingMachines,
                        unsigned int numStudents )
    : prt( prt ),
      numVendingMachines( numVendingMachines ),
      numStudents( numStudents ),
      studentIndex( numStudents ) {
    // vector initialization for each student's start position
    for ( auto i = 0U; i < numStudents; i++ ) {
        studentIndex.at( i ) = -1;
    }
}

void
NameServer::VMregister( VendingMachine* vendingmachine ) {
    newMachine = vendingmachine;
}

VendingMachine*
NameServer::getMachine( unsigned int id ) {
    int prevStudentIndex = studentIndex.at( id );
    if ( prevStudentIndex == -1 ) {  // first time assign
        lastMachineIndex      = ( lastMachineIndex + 1 ) % numVendingMachines;
        studentIndex.at( id ) = lastMachineIndex;
    } else {  // not first time assign
        studentIndex.at( id )
            = ( studentIndex.at( id ) + 1 ) % numVendingMachines;
    }
    prt.print( Printer::NameServer, 'N', id, studentIndex.at( id ) );
}

VendingMachine**
NameServer::getMachineList() {
    return &machineList[0];
}

void
NameServer::main() {
    prt.print( Printer::NameServer, 'S' );
    // Stage 1. wait for all vending machine register
    for ( auto i = 0U; i < numVendingMachines; i++ ) {
        _Accept( VMregister ) {
            machineList.push_back( newMachine );
            prt.print( Printer::NameServer, 'R', newMachine->getId() );
        };
    }

    // Stage 2. receive student and truck call
    for ( ;; ) {
        _Accept( ~NameServer ) {
            break;
        }
        or _Accept( getMachine ){

        } or _Accept( getMachineList ) {}
    }

    // Stage 3. exit
    prt.print( Printer::NameServer, 'F' );
    prt.print( Printer::NameServer, 'F' );
}
