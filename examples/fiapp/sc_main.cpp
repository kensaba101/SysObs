#include <systemc.h>
// For std::unique_ptr
#include <memory>

// Include common routines
#include <verilated.h>

#include "Vfiapp.h"

#define SIMULATE_UNTIL_TIME 40

int sc_main(int argc, char* argv[]) {
    // Prevent unused variable warnings
    if (false && argc && argv) {}

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs
    Verilated::debug(0);

    // Randomization reset policy
    // May be overridden by commandArgs
    Verilated::randReset(2);

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    Verilated::commandArgs(argc, argv);

    // Create logs/ directory in case we have traces to put under it
   // Verilated::mkdir("logs");

    // General logfile
    ios::sync_with_stdio();

    // Define clocks
    sc_clock clk("clk", 10, SC_NS, 0.5, 3, SC_NS, true); //true = posedge
    //sc_clock fastclk("fastclk", 2, SC_NS, 0.5, 2, SC_NS, true);

    // Define interconnect
    sc_signal<sc_uint<1>> reset;
    sc_signal<sc_uint<1>> a;
    sc_signal<sc_uint<1>> enable;

    sc_signal<sc_uint<1>> o1;
    sc_signal<sc_uint<1>> o2;
    sc_signal<sc_uint<1>> o3;

    // Construct the Verilated model, from inside V[modulename].h
    //Vfiapp* top = new Vfiapp("top");

    // Construct the Verilated model, from inside Vtop.h
    // Using unique_ptr is similar to "Vtop* top = new Vtop" then deleting at end
    const std::unique_ptr<Vfiapp> top{new Vfiapp{"top"}}
    // Attach signals to the model
    top->clk(clk);
    top->reset(reset);
    top->a(a);
    top->enable(enable);

    top->o1(o1);
    top->o2(o2);
    top->o3(o3);

    // Set some inputs
    reset = 0; //reset is active high
    clk = 0;
    a = 0;
    enable = 1; //active high

    // You must do one evaluation before enabling waves, in order to allow
    // SystemC to interconnect everything for testing.
    sc_start(1, SC_NS);
    //1 nanosecond

    // Simulate until $finish
    while (!Verilated::gotFinish() && (sc_time_stamp() < sc_time(SIMULATE_UNTIL_TIME, SC_NS))) {   

        //toggle clk

        // Apply inputs on negedge
        if (sc_time_stamp() > sc_time(1, SC_NS) && sc_time_stamp() < sc_time(10, SC_NS)) {
            reset = !0;  // Assert reset
            a = 1;
            enable(1);
        } else if(sc_time_stamp() >= sc_time(10, SC_NS) && sc_time_stamp() < sc_time(20, SC_NS)) {
            reset = !1;  // Deassert reset
            a = !a;
            enable = 0;
        } else if(sc_time_stamp() >= sc_time(20, SC_NS) && sc_time_stamp() < sc_time(30, SC_NS)) {
            reset = !1;  // Deassert reset
            a = !a;
            enable = 1;
        } else (sc_time_stamp() >= sc_time(20, SC_NS) && sc_time_stamp() < sc_time(40, SC_NS)) {
            reset = !1;  // Deassert reset
            a = !a;
            enable = !enable;
        }

        //print out what's relevant
        cout << o1 << o2 << o3 <<endl;
        // Simulate 1ns 
        sc_start(1, SC_NS);
    }

    // Final model cleanup
    top->final();

    // Destroy model
    //delete top;
    //top = nullptr;

    // Fin
    return 0;
}
