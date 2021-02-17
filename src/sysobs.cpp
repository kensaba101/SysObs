#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

void verilation(); //TODO:args, calls verilator with default verilator args, with user given files. flags can be used to overwrite default args. 


int main(int argc, char **argv){

    //while loop for all flags and params to be processed
    //user select DPI or VPI using flag
    

    //pass verilator arguments to verilator, if none specified use default args
    //sc (cpp) wrapper file is passed to verilator, this file is not processed by sysobs, so burden of making sure everything's ready for VPI/DPI usage is on user.
    
    //.v/.sv files are modified, for metacomments necessary for DPI/VPI, as well as commenting in/out only DPI or only VPI as specified by user. 
    //SOI.csv is processed 
    
}

