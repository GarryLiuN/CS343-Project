#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "printer.h"

_Task VendingMachine;

_Task NameServer {
   private:
    // reference
    Printer& prt;
    // attributes
    unsigned int numVendingMachines;
    unsigned int numStudents;

    void main();

   public:
    NameServer( Printer & prt,
                unsigned int numVendingMachines,
                unsigned int numStudents );
    void             VMregister( VendingMachine * vendingmachine );
    VendingMachine*  getMachine( unsigned int id );
    VendingMachine** getMachineList();
};

#endif
