// Include common routines
#include <verilated.h>

// Include model header, generated from Verilating "[modulename].v"
#include "Vfiapp.h"

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
// Called by $time in Verilog
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

int main(int argc, char** argv, char** env) {
    // This is a more complicated example, please also see the simpler examples/make_hello_c.

    // Prevent unused variable warnings
    if (false && argc && argv && env) {}

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs
    Verilated::debug(0);

    // Randomization reset policy
    // May be overridden by commandArgs
    Verilated::randReset(2);

    // Verilator must compute traced signals
    //Verilated::traceEverOn(true);

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    Verilated::commandArgs(argc, argv);

    // Create logs/ directory in case we have traces to put under it
    //Verilated::mkdir("logs");

    // Construct the Verilated model, from Vtop.h generated from Verilating "top.v"
    Vfiapp* top = new Vfiapp;  // Or use a const unique_ptr, or the VL_UNIQUE_PTR wrapper

    // Set some inputs
    top->reset = 0; //reset is active high
    top->clk = 0;
    top->a = 0;
    top->enable = 1; //active high

    // Simulate until $finish
    while (!Verilated::gotFinish()) {
        main_time++;  // Time passes...

        // Toggle a fast (time/2 period) clock
        top->clk = !top->clk;

        // Toggle control signals on an edge that doesn't correspond
        // to where the controls are sampled; in this example we do
        // this only on a negedge of clk, because we know
        // reset is not sampled there.
        if (!top->clk) {
            if (main_time > 1 && main_time < 10) {
                top->reset = !0; // Assert reset 
                }   
            else if (main_time >= 10 && main_time <20{
                top->reset = !1;  // Deassert reset
                top->a = !top->a; 
                }
            else if (main_time >= 20) {
                top->reset = !1;  
                top->a = !top->a;
                top->enable = 0; //deassert enable
            }
        }
    }

        // Evaluate model
        // (If you have multiple models being simulated in the same
        // timestep then instead of eval(), call eval_step() on each, then
        // eval_end_step() on each.)
        top->eval();

        // Read outputs
        /*
        VL_PRINTF("[%" VL_PRI64 "d] clk=%x rstl=%x iquad=%" VL_PRI64 "x"
                  " -> oquad=%" VL_PRI64 "x owide=%x_%08x_%08x\n",
                  main_time, top->clk, top->reset_l, top->in_quad, top->out_quad, top->out_wide[2],
                  top->out_wide[1], top->out_wide[0]);
                  */

        //toprint: time, clk, reset, enable, a, o1, o2, o3
        VL_PRINTF("[%" VL_PRI64 "d] clk=%x reset=%x enable=%x a=%x o1,o2,o3=%x_%08x_%08x\n",
                  main_time, top->clk, top->reset, top->enable, top->a, top->o1,
                  top->o2, top->o3); 
    }

    // Final model cleanup
    top->final();

/*    //  Coverage analysis (since test passed)
#if VM_COVERAGE 
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/coverage.dat");
#endif */

    // Destroy model
    delete top;
    top = nullptr;

    // Fin
    exit(0);
}

