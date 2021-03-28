#include <verilated.h>          // Defines common routines
#include <iostream>             // Need std::cout
#include "Vdpitest.h"               // From Verilating "top.v"
#include "svdpi.h"
#include "Vdpitest__Dpi.h"
/*
int add(int a, int b) { return a+b; }

int dpic_line() { //works
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
*/
//imports, called on sv side. 
int testvalVal; 

void testValRead1(){
    cout << "testValRead1 form c called." << endl;
    testvalVal = 1; 
}
void testValRead0(){
    cout << "testValRead0 form c called." << endl;
    testvalVal = 2; 
} 

vluint64_t main_time = 0;       // Current simulation time
// This is a 64-bit integer to reduce wrap over issues and
// allow modulus.  This is in units of the timeprecision
// used in Verilog (or from --timescale-override)



int sc_main(int argc, char** argv) {    


    Verilated::commandArgs(argc, argv);   // Remember args
    
    Vdpitest* top;
    top = new Vdpitest("top");
    sc_clock clk("clk", 2, SC_NS, 0.5, true);
    top->clk(clk); 
    sc_start(1, SC_NS); 
    svSetScope(svGetScopeFromName("top.dpitest"));


    while (!Verilated::gotFinish() && (sc_time_stamp() < sc_time(50, SC_NS)) ) {
        //cout << "value of testval address: " << testvalPtr << endl; 
        getTestval(); 
        setTestval1(); 
            
        sc_start(1, SC_NS); 
    }

    top->final(); // Done simulating
    return 0; 
}