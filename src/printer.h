#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <vector>

_Monitor Printer {
   private:
    struct Info {
        bool dirty = false;
        char state;
        int  val1;
        int  val2;
    };

    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;

    // Info buffer
    Info              parent;
    Info              groupoff;
    Info              watoff;
    Info              names;
    Info              truck;
    Info              plant;
    std::vector<Info> students;
    std::vector<Info> machines;
    std::vector<Info> couriers;

   public:
    enum Kind {
        Parent,
        Groupoff,
        WATCardOffice,
        NameServer,
        Truck,
        BottlingPlant,
        Student,
        Vending,
        Courier
    };
    /**
     * @brief Construct for Printer. Will initialize vector<Info>
     *        buffers for students, vending machines and couriers.
     *        It will also print out output header.
     */
    Printer( unsigned int numStudents,
             unsigned int numVendingMachines,
             unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print(
        Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif
