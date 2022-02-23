`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Target Device:  
// Tool versions:  
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb;

    
    wire wen = 1;
    reg clk;
    reg  [4 :0] raddr1;
    reg  [4 :0] raddr2;
    reg  [4 :0] waddr;
    reg  [31:0] wdata;
    wire  [31:0] rdata1;
    wire  [31:0] rdata2;
    wire  [31:0] test_data;  
    reg  [4 :0] test_addr;
    regfile rf_module(
        .clk   (clk   ),
        .wen   (wen   ),
        .raddr1(raddr1),
        .raddr2(raddr2),
        .waddr (waddr ),
        .wdata (wdata ),
        .rdata1(rdata1),
        .rdata2(rdata2),
        .test_addr(test_addr),
        .test_data(test_data)
    );

    initial begin
        // Initialize Inputs
        clk = 0;
        raddr1 = 5'd1;
        raddr2 = 5'd2;
        test_addr = 5'd3;

        #10;
        clk = 1;
        waddr = 5'd1;
        wdata = 32'HFFFFFFFF;
        
        #10;
        clk = 0;

        #10;
        clk = 1;
        waddr = 5'd2;
        wdata = 32'H0000FFFF;
        
        #10;
        clk = 0;

        #10;
        clk = 1;
        waddr = 5'd3;
        wdata = 32'HFFFF0000;
    end
endmodule
