module fiappvpi
(
    input logic clk, 
    input logic reset, 
    input logic a, 
    input logic enable,
    
    output logic o1, 
    output logic o2,
    output logic o3
);

    //Global switch (--public-flat-rw can be used to turn everything in sim accessible by VPI, but will reduce performance and possibly cause clock  mis-simulation)
    logic q1 /*verilator public_flat_rd*/; //q1 is read only
    logic q2 /*verilator public_flat_rw @(posedge clk) */; //q2 is writae only
    logic q3 /*verilator public_flat*/; //read or write by using c code

    assign o1 = q1; 
    assign o2 = q2; 
    assign o3 = q3; 
    
    always_ff @(posedge clk, posedge reset)
        if(reset) begin
            q1 <= 1'b0;
            q2 <= 1'b0;
            q3 <= 1'b0;
        end
        else begin
            if (enable) begin
                q1 <= a; 
            end
            q2 <= q1; 
            q3 <= !q1; 
    end
endmodule

