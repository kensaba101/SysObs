module dpitest
(    input logic clk

);

    //import "DPI-C" function int getSoiValue (output int soi);
    //import "DPI-C" function void setSoiValue (output int soi, input int val); 
    //import "DPI-C" function int add (input int a, input int b);
    //export "DPI-C" function integer \$myRand;
    import "DPI-C" context function int dpic_line();

    //import "DPI-C" context function logic getSoiHandle(input logic soi); //input logic -> svLogic, output logic -> svlogic*
    //export "DPI-C" function sendTvHandle; 
    export "DPI-C" task setTestval; 
    export "DPI-C" function getTestval; 

    //import "DPI-C" context function void setSoi(input logic value, output logic soi);

    //initial $display("This is line %d, again, line %d\n", `__LINE__, dpic_line());


    logic testval; 

    initial begin
        testval = 1'b1; 
        //getSoiHandle(testval);
    end

    always_ff @(posedge clk)
        begin
            testval <= !testval;
        end


    task setTestval;
        input logic inLogic; 
        testval = inLogic; 
    endtask
    
    function logic getTestval;
        return testval;
    endfunction
    
   /* task getTestval;    
        $display ("Testval :", testval);

        //return testval; 
    endtask */
    


    /*
    function sendTvHandle(output logic soi);
       soi = testval;
    endfunction
    */


    //function setSoiSV(input logic value, output logic soi);
       /* veril//ator no_inl//ine_ta//sk */
    //   setSoi(soi);
    //endfunction


endmodule