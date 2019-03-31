#include <unistd.h>  // access: getpid
#include <iostream>  // access: cout, cin, cerr, endl
#include <string>  // access: string, stoi
using namespace std;

#include "config.h"

int
main( int argc, char* argv[] ) {
    int    seed   = getpid();
    string config = "soda.config";

    try {
        switch ( argc ) {
            case 3:
                seed = stoi( argv[2] );
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

    ConfigParms configParms;
    processConfigFile( config.c_str(), configParms );
    cout << configParms.groupoffDelay << " " << configParms.maxPurchases << " "
         << configParms.maxShippedPerFlavour << " "
         << configParms.maxStockPerFlavour << " " << configParms.numCouriers
         << " " << configParms.numStudents << " "
         << configParms.numVendingMachines << " " << configParms.parentalDelay
         << " " << configParms.sodaCost << " "
         << configParms.timeBetweenShipments << " ";

    // TODO: initialize tasks
    // TODO: end tasks

    return 0;
}  // ::main()