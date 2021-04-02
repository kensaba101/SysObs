#include <systemc.h>
#include <verilated.h>
#include "verilated_vpi.h" 
#include "Vfiappvpi.h" 

#define SIMULATE_UNTIL_TIME 50
// call verilator using: 
// verilator -Wall --sc fiappvpi.sv --exe --build sc_vpi.cpp --vpi --Mdir obj_vpi -Wno-BLKANDNBLK 

int q1val;
int q2val; 
int q3val; 

int getSoiValue(vpiHandle vh) { 
    s_vpi_value v; 
    v.format = vpiIntVal; 
    vpi_get_value(vh, &v);
    return v.value.integer; 
}

void setSoiValue(vpiHandle vh, int i) {
    s_vpi_value v; 
    v.format = vpiIntVal; 
    v.value.integer = i; 
    vpi_put_value(vh, &v, 0, vpiForceFlag);   
}

int sc_main(int argc, char** argv) {
        sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated", sc_core::SC_DO_NOTHING ); // Ignore warnings about IEEE deprecated features.
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

        Vfiappvpi* top; 
        top = new Vfiappvpi("top");

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

        vpiHandle vhq1 = vpi_handle_by_name((PLI_BYTE8*)"top.fiappvpi.q1", NULL); //instanceName.moduleName.signalName
        vpiHandle vhq2 = vpi_handle_by_name((PLI_BYTE8*)"top.fiappvpi.q2", NULL); 
        vpiHandle vhq3 = vpi_handle_by_name((PLI_BYTE8*)"top.fiappvpi.q3", NULL); 
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
                setSoiValue(vhq1, 1); 
                setSoiValue(vhq2, 1);
                setSoiValue(vhq3, 1); 
            }

            q1val = getSoiValue(vhq1);
            q2val = getSoiValue(vhq2); 
            q3val = getSoiValue(vhq3);
        
            cout << "q1, q2, q3 before calling sc_start(): " << endl; 
            cout << q1val << q2val << q3val << endl;
            cout << "o1, o2, o3 before calling sc_start(): " << endl;
            cout << o1 << o2 << o3 << endl; 

            sc_start(1, SC_NS); // Evaluates model & progresses clock by 1 ns
            
            cout << "q1, q2, q3 after calling sc_start(): " << endl; 
            cout << q1val << q2val << q3val << endl;
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
