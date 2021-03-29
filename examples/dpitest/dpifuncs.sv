export "DPI-C" function getTestval; 
import "DPI-C" context function void testValRead1();
import "DPI-C" context function void testValRead0();
export "DPI-C" function setTestval1; 
export "DPI-C" function setTestval0; 

function getTestval();
    if (testval == 1'b1) begin
        testValRead1();
    end else begin
        testValRead0();
    end
endfunction
    
function setTestval1();
    testval = 1;
endfunction
    
function setTestval0(); 
    testval = 0; 
endfunction