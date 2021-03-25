module dpitest
(
);

    //import "DPI-C" function int getSoiValue (output int soi);
    //import "DPI-C" function void setSoiValue (output int soi, input int val); 
    import "DPI-C" function int add (input int a, input int b);
    //export "DPI-C" function integer \$myRand;
    import "DPI-C" context function int dpic_line();
   initial $display("This is line %d, again, line %d\n", `__LINE__, dpic_line());

   //initial $display("myRand=%d", $myRand());
/*
    export "DPI-C" task publicSetBool;
    logic testval; 
    bit var_bool; 

   task publicSetBool;
      input bit in_bool;
      var_bool = in_bool;
   endtask



    
    initial begin
        testval = 1; 
        $display("%x + %x = %x", 1, 2, add(1,2));
    end

    
*/

endmodule