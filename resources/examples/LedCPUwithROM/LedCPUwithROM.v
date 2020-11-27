`timescale 1ns / 1ps

module LedCPUwithROM(clk, rst, outPattern);
input clk, rst;
output [7:0] outPattern;

parameter FREQ = 50_000_000/16;

wire [ 7:0]addrRd;
wire [15:0]dataRd;

LedCPUcore #(FREQ) LedCPUcore(.clk(clk), .rst(rst), .addrRd(addrRd), .dataRd(dataRd), .outPattern(outPattern));
ROM ROM(.addrRd(addrRd), .dataRd(dataRd));

endmodule
