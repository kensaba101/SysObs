module dpitest
(    input logic clk

);

    //import "DPI-C" function int getSoiValue (output int soi);
    //import "DPI-C" function void setSoiValue (output int soi, input int val); 
    //import "DPI-C" function int add (input int a, input int b);
    //export "DPI-C" function integer \$myRand;
    import "DPI-C" context function int dpic_line();

    import "DPI-C" context function logic getSoi(input logic soi); //input logic -> svLogic, output logic -> svlogic*
    export "DPI-C" function getSoiSV; 

    //import "DPI-C" context function void setSoi(input logic value, output logic soi);

    //initial $display("This is line %d, again, line %d\n", `__LINE__, dpic_line());


    logic testval; 

    initial begin
        testval = 1'b1; 
    end

    always_ff @(posedge clk)
        begin
            testval <= !testval;
        end
    

    

    function getSoiSV(input logic soi);
       /* verilator no_inline_task */
       return getSoi(soi);
    endfunction


    //function setSoiSV(input logic value, output logic soi);
       /* veril//ator no_inl//ine_ta//sk */
    //   setSoi(soi);
    //endfunction


endmodule