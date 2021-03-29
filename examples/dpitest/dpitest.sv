module dpitest
(    input logic clk
);  

    `include "dpifuncs.sv"

    logic testval; 
    
    initial begin
        testval = 1'b1; 
    end

    
    always_ff @(posedge clk)
        begin
            testval <= !testval;
        end
    
endmodule