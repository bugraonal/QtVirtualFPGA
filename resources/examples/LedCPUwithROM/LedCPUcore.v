`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:26:21 10/08/2018 
// Design Name: 
// Module Name:    LEDCPUcore 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module LedCPUcore(clk, rst, addrRd, dataRd, outPattern);
	
	input clk, rst;
	input[15:0] dataRd;
	
	output reg[7:0] addrRd;
	output reg[7:0] outPattern;
	
	parameter FREQ = 50_000_000/16;
	parameter COUNT_SIZE = 26;
	
	reg[7:0] addrRdNext, outPatternNext;
	wire timerEn;
	reg[7:0] countTo, countToNext;
	reg timerStart, timerStartNext;
	
	timer #(COUNT_SIZE) timer(.clk(clk), .rst(rst), .startStop(timerStart), .amount(countTo),.en(timerEn));
	
	always@(posedge clk) begin
		addrRd <= #1 addrRdNext;
		outPattern <= #1 outPatternNext;
		countTo <= #1 countToNext;
		timerStart <= timerStartNext;
	end
	
	always@(*)begin
		addrRdNext = addrRd;
		outPatternNext = outPattern;
		countToNext = countTo;
		timerStartNext = timerStart;
		if (rst) begin
			addrRdNext = 0;
			outPatternNext = 0;
			countToNext = 0;
		end
		else if (dataRd[7:0] == 0)
			addrRdNext = dataRd[15:8];
		else if (timerEn) begin
			outPatternNext = dataRd[15:8];
			addrRdNext = addrRd + 1;
			timerStartNext = 0;
		end
		else begin 
			outPatternNext = dataRd[15:8];
			countToNext = dataRd[7:0];
			timerStartNext = 1;
		end
	end
endmodule
