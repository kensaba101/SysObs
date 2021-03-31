#include <systemc.h>
#include <verilated.h>
#include "Vfiappdpi__Dpi.h"
#include "Vfiappdpi.h"
#include "svdpi.h"

#define SIMULATE_UNTIL_TIME 50
// call verilator using: 
// verilator -Wall --sc fiappdpi.sv --exe --build sc_dpi.cpp --Mdir obj_dpi -Wno-BLKANDNBLK  


int q1val; 
void q1read1(){
    q1val = 1; 
}
void q1read0(){
    q1val = 0; 
} 

int q2val; 
void q2read1(){
    q2val = 1; 
}
void q2read0(){
    q2val = 0; 
} 

int q3val; 
void q3read1(){
    q3val = 1; 
}
void q3read0(){
    q3val = 0; 
} 

int sc_main(int argc, char** argv) {
        if (false && argc && argv) {}
        Verilated::debug(0);
        Verilated::randReset(2);
        Verilated::commandArgs(argc, argv);

        sc_clock clk("clk", 2, SC_NS, 0.5, true); // Define Clock: period = 2 ns, duty cycle 50%, posedge sensitive
        sc_signal<bool> reset; // Define interconnects
        sc_signal<bool> a;
        sc_signal<bool> enable;
        sc_signal<bool> o1;
        sc_signal<bool> o2;
        sc_signal<bool> o3;

        Vfiappdpi* top;
        top = new Vfiappdpi("top");

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
        svSetScope(svGetScopeFromName("top.fiappdpi"));

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
                    
                } else if (sc_time_stamp() >= sc_time(30, SC_NS) && sc_time_stamp() < sc_time(50, SC_NS)){
                    reset = 0;  // Deassert reset
                    a = !a; 
                    enable = 1;  // Reassert enable
                }
            } 

            if (sc_time_stamp() >= sc_time(33,SC_NS) && sc_time_stamp() < sc_time(43,SC_NS)){
                //setq1Val1(); 
                setq2Val1(); 
                setq3Val1(); 
            }

            getq1Val(); getq2Val(); getq3Val(); 

            cout << "q1, q2, q3 before calling sc_start(): " << endl; 
            cout << q1val << q2val <<  q3val << endl;
            cout << "o1, o2, o3 before calling sc_start(): " << endl;
            cout << o1 << o2 << o3 << endl; 

            sc_start(1, SC_NS); // Evaluates model & progresses clock by 1 ns
            
            cout << "q1, q2, q3 after calling sc_start()" << endl; 
            cout << q1val << q2val <<  q3val << endl;
            cout << "o1, o2, o3 after calling sc_start(): " << endl;
            cout << o1 << o2 << o3 << endl; 
            cout << "[" << sc_time_stamp().value() << "] " << " clk=" << clk << " reset=" << reset << " enable=" << enable << " a=" << a << " o1=" << o1 
                << " o2=" << o2 << " o3=" << o3 << endl << endl;

            if(sc_time_stamp() > sc_time(SIMULATE_UNTIL_TIME, SC_NS) ){
                break;
            }
        }

        top->final();    
        return 0;
}