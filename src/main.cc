#include <unistd.h>  // access: getpid
#include <iostream>  // access: cout, cin, cerr, endl
#include <string>  // access: string, stoi
using namespace std;

#include "MPRNG.h"

#include "bank.h"
#include "bottlingplant.h"
#include "config.h"
#include "groupoff.h"
#include "nameserver.h"
#include "parent.h"
#include "printer.h"
#include "student.h"
#include "truck.h"
#include "watcardoffice.h"

#include "vendingmachine.h"

MPRNG mprng;

int
main( int argc, char* argv[] ) {
    int    seed   = getpid();
    string config = "soda.config";

    try {
        switch ( argc ) {
            case 3:
                seed = stoi( argv[2] );
                if ( seed <= 0 ) {
                    cerr << "Invalid argument: seed must be a "
                            "positive number."
                         << endl;
                    throw 1;
                }
            case 2:
                config = argv[1];
            case 1:
                break;
            default:
                cerr << "Too many arguments." << endl;
                throw 1;
        }  // switch
    } catch ( ... ) {
        cerr << "Usage: " << argv[0] << " [ config-file [ Seed ] ]" << endl;
        exit( EXIT_FAILURE );
    }  // try{} catch{}
    cout << "seed: " << seed << " (for testing, remove before complete)"
         << endl;
    mprng.set_seed( seed );

    ConfigParms configParms;
    processConfigFile( config.c_str(), configParms );

    // ------------------Initialize and Start Instances------------------

    // initialize Printer
    Printer printer( configParms.numStudents,
                     configParms.numVendingMachines,
                     configParms.numCouriers );
    // initialize Bank
    Bank bank( configParms.numStudents );
    // initialize Parent
    Parent parent(
        printer, bank, configParms.numStudents, configParms.parentalDelay );
    // initialize WatCardOffice
    WATCardOffice watcardoffice( printer, bank, configParms.numCouriers );
    // initialize Groupoff
    Groupoff groupoff( printer,
                       configParms.numStudents,
                       configParms.sodaCost,
                       configParms.groupoffDelay );
    // initialize NameServer
    NameServer nameserver(
        printer, configParms.numCouriers, configParms.numVendingMachines );
    // initialize VendingMachines
    VendingMachine* vendingmachines[configParms.numVendingMachines];
    for ( unsigned int i = 0; i < configParms.numVendingMachines; ++i ) {
        vendingmachines[i] = new VendingMachine(
            printer, nameserver, i, configParms.sodaCost );
    }
    // initialize BottlingPlant
    /** Since BottlingPlant needs to be deleted before VendingMachines,
     *  it needs to be allocated on heap for manual deletion     */
    BottlingPlant* bottlingPlant
        = new BottlingPlant( printer,
                             nameserver,
                             configParms.numVendingMachines,
                             configParms.maxShippedPerFlavour,
                             configParms.maxStockPerFlavour,
                             configParms.timeBetweenShipments );
    // initialize Students
    Student* students[configParms.numStudents];
    for ( unsigned int i = 0; i < configParms.numStudents; ++i ) {
        students[i] = new Student( printer,
                                   nameserver,
                                   watcardoffice,
                                   groupoff,
                                   i,
                                   configParms.maxPurchases );
    }

    // ------------------Wait and Delete Instances------------------

    // wait and delete Students
    for ( unsigned int i = 0; i < configParms.numStudents; ++i ) {
        delete students[i];
    }
    // wait and delete BottlingPlant
    delete bottlingPlant;
    // wait and delete VendingMachines
    for ( unsigned int i = 0; i < configParms.numVendingMachines; ++i ) {
        delete vendingmachines[i];
    }
    // the rest will be deleted when main returns

    return 0;
}  // ::main()
