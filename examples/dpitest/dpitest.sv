module dpitest
(    input logic clk

);

    //import "DPI-C" function int getSoiValue (output int soi);
    //import "DPI-C" function void setSoiValue (output int soi, input int val); 
    //import "DPI-C" function int add (input int a, input int b);
    //export "DPI-C" function integer \$myRand;
    import "DPI-C" context function int dpic_line();
    import "DPI-C" context function void testValRead1();
    import "DPI-C" context function void testValRead0();

    //import "DPI-C" context function logic getSoiHandle(input logic soi); //input logic -> svLogic, output logic -> svlogic*
    //export "DPI-C" function sendTvHandle; 
    //export "DPI-C" function setTestval; 
    export "DPI-C" function getTestval; 
    export "DPI-C" function setTestval1; 
    export "DPI-C" function setTestval0; 

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

    /*
    function setTestval;
        input logic inLogic; 
        testval <= inLogic; 
    endfunction 
    */
    
    function getTestval();
        //$display (" Clk: %d, Testval : %d", clk, testval); //works
        //call import here to send value over to c-side (read) 
        if (testval == 1'b1) begin
            $display ("sv function getTestval called, calling c import testvalread1: ";
            testValRead1();
        end else begin
            $display ("sv function getTestval called, calling c import testvalread0: ";
            testValRead0();
        end
    endfunction

    function setTestval1();
        $display (" Clk: %d, Testval : %d", clk, testval);
        testval = 1;
        $display (" Clk: %d, Testval : %d", clk, testval);
    endfunction

    
    function setTestval0(); 
        $display (" Clk: %d, Testval : %d", clk, testval);
        testval = 0; 
        $display (" Clk: %d, Testval : %d", clk, testval);
    endfunction
    

    /*
    function logic getTestval;
        return testval;
    endfunction 
    */
    
   /* task getTestval;    
        $display ("Testval : %d", testval);

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