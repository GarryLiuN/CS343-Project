#include <unistd.h>  // access: getpid
#include <iostream>  // access: cout, cin, cerr, endl
#include <string>  // access: string, stoi
using namespace std;

#include "MPRNG.h"
#include "config.h"

MPRNG              mprng;
const unsigned int NUMOFFLAVORS = 4;
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

    mprng.set_seed( seed );

    ConfigParms configParms;
    processConfigFile( config.c_str(), configParms );

    // TODO: initialize tasks
    // TODO: end tasks

    return 0;
}  // ::main()