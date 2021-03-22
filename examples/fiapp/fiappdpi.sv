module fiappdpi
(
    input logic clk, 
    input logic reset, 
    input logic a, 
    input logic enable,
    
    output logic o1, 
    output logic o2,
    output logic o3
);

    import "DPI-C" context function void getSoiValue();
    //import "DPI-C" function void setSoiValue(output int soi, input int val); 
    //export "DPI-C" function SetLogic;


    logic q1, q2, q3; 

    assign o1 = q1; 
    assign o2 = q2; 
    assign o3 = q3; 
    
    always_ff @(posedge clk, posedge reset)
        if(reset) begin
            q1 <= 1'b0;
            q2 <= 1'b0;
            q3 <= 1'b0;
            soiGetter(q1);
        end
        else begin
            if (enable) begin
                q1 <= a; 
            end
            q2 <= q1; 
            q3 <= !q1; 
            soiGetter(q1);
        end
endmodule

task soiGetter(input din);
    /* verilator no_inline_task */
    getSoiValue();
endtask


/* //toTry 1: 
function void getSoiValueSV(int soi);
    // Call C function
    getSoiValue(soi); // Arguments passed by copy
    
endfunction

function void setSoiValueSV(output int soi, output int val);
    // Call C function
    getSoiValue(soi, val); // Arguments passed by copy
endfunction


//*/



/* //doesn't work 
function void SetLogic(input logic inLogic, output logic outLogic); //SetLogic(1,q1);   
    outLogic = inLogic; 
endfunction
*/
