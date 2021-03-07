#include <systemc.h>
// Include common routines
#include <verilated.h>

#include "svdpi.h"
// Verilator will create the following file: 
#include "Vfiappdpi_Dpi.h"

// Generated by verilating fiappdpi.sv
#include "Vfiappdpi.h"

#define SIMULATE_UNTIL_TIME 50
// call verilator using: 

int getSoiValue(sc_signal<bool> soi){

    return int(soi); 
}

void setSoiValue(sc_signal<bool> soi, int i){

}

int sc_main(int argc, char** argv) {
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

        // Define Clock: period = 2 ns, duty cycle 50%, posedge sensitive
        sc_clock clk("clk", 2, SC_NS, 0.5, true);

        // Define interconnects
        sc_signal<bool> reset;
        sc_signal<bool> a;
        sc_signal<bool> enable;

        sc_signal<bool> o1;
        sc_signal<bool> o2;
        sc_signal<bool> o3;

        Vfiapp* top;
        top = new Vfiapp("top");

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
        a = 0;
        enable = 1; //active high
        
        // Initialize SC model
        sc_start(1, SC_NS);

        while (!Verilated::gotFinish()) { 

            // Apply control inputs on negedge, as reset and enable are sampled on posedge
            if (!clk){
                if (sc_time_stamp() > sc_time(1, SC_NS) && sc_time_stamp() < sc_time(10, SC_NS)) {
                    reset = 1;  // Assert reset
                } else if (sc_time_stamp() >= sc_time(10, SC_NS) && sc_time_stamp() < sc_time(20, SC_NS)){
                    reset = 0;  // Deassert reset
                    a = !a; 
                } else if (sc_time_stamp() >= sc_time(20, SC_NS) && sc_time_stamp() < sc_time(30, SC_NS)){
                    reset = 0;  // Deassert reset
                    a = !a; 
                    enable = 0; // Deassert enable
                } else if (sc_time_stamp() >= sc_time(30, SC_NS) && sc_time_stamp() < sc_time(40, SC_NS)){
                    reset = 0;  // Deassert reset
                    a = !a; 
                    enable = 1;  // Reassert enable
                }
            }
            // Evaluates model & progresses clock by 1 ns
            sc_start(1, SC_NS); 
            //tprint: time, clk, reset, enable, a, o1, o2, o3
            cout << "[" << sc_time_stamp().value() << "] " << " clk=" << clk << " reset=" << reset << " enable=" << enable << " a=" << a << " o1=" << o1 
                << " o2=" << o2 << " o3=" << o3 << endl; 

            if(sc_time_stamp() > sc_time(SIMULATE_UNTIL_TIME, SC_NS) ){
                break;
            }
        }

        top->final();    
        //delete top;
        return 0;
}