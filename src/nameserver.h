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
    unsigned int numVendingMachines;
    unsigned int numStudents;
    /** @brief studentIndex vector is used to store the last VM index each
     * student accessed, which will help to make sure that each student has a
     * chance to
     */
    visit every machine std::vector<int> studentIndex;

    std::vector<VendingMachine*> machineList;

    /** @brief lastMachineIndex is used to store the last vm ID that assigned to
     * student who first time called getMachine
     */
    unsigned int lastMachineIndex = -1;

    // local copy for machine that call VMregister
    VendingMachine* newMachine;

    void main();

   public:
    NameServer( Printer & prt,
                unsigned int numVendingMachines,
                unsigned int numStudents );
    /**
     * @brief VMregister will be called by a VM and the nameserver will save the
     * pointer to that machine into a vector
     */
    void VMregister( VendingMachine * vendingmachine );

    /**
     * @brief GetMachine will be called by a student, the id will be used to
     * select next VM in a round-robin fashion
     */
    VendingMachine* getMachine( unsigned int id );

    /**
     * @brief getMachineList will be called by truck and return the full list of
     * all VMs
     */
    VendingMachine** getMachineList();
};

#endif
