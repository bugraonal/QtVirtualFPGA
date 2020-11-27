module LedCPUwithRAM(
	clk,
	rst,
	switch,
	enter,
	outPattern
);
input clk, rst;
input [7:0] switch;
input enter;
output [7:0] outPattern;

parameter NDELAY = 1000; // 650000;
parameter FREQ = 1000; // 50_000_000/16;

wire enterDB, wrEn;
wire [7:0] addrWr,  addrRd;
wire [15:0] dataWr, dataRd;


debounce #(NDELAY)debounce_1(.rst(rst), .clk(clk), .noisy(enter), .clean(enterDB));

progLogic progLogic_1(.clk(clk), .rst(rst), .switch(switch), .enter(enterDB), .addrWr(addrWr), .dataWr(dataWr), .wrEn(wrEn));

mem1R1W mem1R1W_1(.clk(clk), .addrRd(addrRd), .dataRd(dataRd), .addrWr(addrWr), .dataWr(dataWr), .wrEn(wrEn));

LedCPUcore #(FREQ)LedCPUcore_1(.clk(clk), .rst(rst), .addrRd(addrRd), .dataRd(dataRd), .outPattern(outPattern));

endmodule
