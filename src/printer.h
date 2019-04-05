#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <vector>

/**
 * @brief Prnter class handles output of the Soda simulator
 */
_Monitor Printer {
   private:
    /**
     * @brief Internal data structure for each component
     */
    struct Info {
        bool dirty = false;
        char state;
        int  val1 = -1;
        int  val2 = -1;
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

    /**
     * @brief Flush stored dirty Info buffer to stdout. Then set all
     *        Info.dirty = false.
     */
    void flush();

    /**
     * @brief Called by flush(). Will output info to stdout.
     *        Then set info.val1/val2 = -1 and info.dirty = false.
     *
     * @info : Reference to the info to be output.
     */
    void print_info( Info & info );

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
     * @brief Constructor for Printer. Will initialize vector<Info>
     *        buffers for students, vending machines and couriers.
     *        It will also print out output header.
     */
    Printer( unsigned int numStudents,
             unsigned int numVendingMachines,
             unsigned int numCouriers );
    /**
     * @brief Destructor for Printer. Will flush Info buffers before
     *        deletion.
     */
    ~Printer();
    /**
     * @brief : public interfaces for updating kind's corresponding
     *          Info instance. If the updating Info is dirty, a flush()
     *          will be invoked and stored Info will be output to stdout
     */
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print(
        Kind kind, unsigned int lid, char state, int value1, int value2 );

   private:
    // additional helper method. since it depends on Kind
    /**
     * @brief : Get the pointer to the Info instance based on kind and
     *          optional id
     * @kind : Indicates which Info to retrieve
     * @id   : Only used when kind is Student, VendingMachine or Courier
     */
    Info* get_info( Kind kind, unsigned int id = 0 );
};

#endif
