#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include <vector>
#include "printer.h"
#include "vendingmachine.h"

_Task NameServer {
   private:
    // reference
    Printer& prt;
    // attributes
    unsigned int                 numVendingMachines;
    unsigned int                 numStudents;
    std::vector<int>             studentIndex;
    std::vector<VendingMachine*> machineList;
    unsigned int                 lastMachineIndex = -1;

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
