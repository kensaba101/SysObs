#include <verilated.h>          // Defines common routines
        #include <iostream>             // Need std::cout
        #include "Vdpitest.h"               // From Verilating "top.v"
        #include "svdpi.h"
    #include "Vdpitest__Dpi.h"
    //publicSetBool(value);

    int add(int a, int b) { return a+b; }

       int dpic_line() {
       // Get a scope:  
       
       svScope scope = svGetScope();

       const char* scopenamep = svGetNameFromScope(scope);
       assert(scopenamep);

       const char* filenamep = "";
       int lineno = 0;
       if (svGetCallerInfo(&filenamep, &lineno)) {
           printf("dpic_line called from scope %s on line %d\n",
              scopenamep, lineno);
           return lineno;
       } else {
           return 0;
       }
   }

        //Vdpitest *dpitest;                      // Instantiation of module

        vluint64_t main_time = 0;       // Current simulation time
        // This is a 64-bit integer to reduce wrap over issues and
        // allow modulus.  This is in units of the timeprecision
        // used in Verilog (or from --timescale-override)

        double sc_time_stamp () {       // Called by $time in Verilog
            return main_time;           // converts to double, to match
                                        // what SystemC does
        }

        int main(int argc, char** argv) {
            Verilated::commandArgs(argc, argv);   // Remember args

            Vdpitest* top;
            top = new Vdpitest("top");
            //top = new Vdpitest;             // Create instance

          

            while (!Verilated::gotFinish()) {
            
            }

            top->final();               // Done simulating
            //    // (Though this example doesn't get here)
            //delete top;
        }