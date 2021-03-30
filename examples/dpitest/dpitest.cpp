#include <verilated.h>          // Defines common routines
#include <iostream>             // Need std::cout
#include "Vdpitest.h"               // From Verilating "top.v"
#include "svdpi.h"
#include "Vdpitest__Dpi.h"

int testvalVal; 
void testValRead1(){
    testvalVal = 1; 
}
void testValRead0(){
    testvalVal = 0; 
} 

vluint64_t main_time = 0; 

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
        cout << "clk: " << clk << "testval(sv): " << testvalVal << endl;
        setTestval1(); 
        getTestval(); 
        cout << "clk: " << clk << "testval(sv): " << testvalVal << endl;
    
        sc_start(1, SC_NS); 
    }

    top->final(); // Done simulating
    return 0; 
}