module fiapp
(
    input logic clk, 
    input logic reset, 
    input logic a, 
    input logic enable,
    
    output logic o1, 
    output logic o2,
    output logic o3
);
    logic q1, q2, q3; 

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

