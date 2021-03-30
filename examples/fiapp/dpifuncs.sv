export "DPI-C" function getq1Val; 
import "DPI-C" context function void q1read1();
import "DPI-C" context function void q1read0();
export "DPI-C" function setq1Val1; 
export "DPI-C" function setq1Val0; 
function getq1Val();
    if (q1 == 1'b1) begin
        q1read1();
    end else begin
        q1read0();
    end
endfunction
function setq1Val1();
    q1 = 1;
endfunction
function setq1Val0(); 
    q1 = 0; 
endfunction

export "DPI-C" function getq2Val; 
import "DPI-C" context function void q2read1();
import "DPI-C" context function void q2read0();
export "DPI-C" function setq2Val1; 
export "DPI-C" function setq2Val0; 
function getq2Val();
    if (q2 == 1'b1) begin
        q2read1();
    end else begin
        q2read0();
    end
endfunction
function setq2Val1();
    q2 = 1;
endfunction
function setq2Val0(); 
    q2 = 0; 
endfunction

export "DPI-C" function getq3Val; 
import "DPI-C" context function void q3read1();
import "DPI-C" context function void q3read0();
export "DPI-C" function setq3Val1; 
export "DPI-C" function setq3Val0; 
function getq3Val();
    if (q3 == 1'b1) begin
        q3read1();
    end else begin
        q3read0();
    end
endfunction
function setq3Val1();
    q3 = 1;
endfunction
function setq3Val0(); 
    q3 = 0; 
endfunction

