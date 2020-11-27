`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:22:35 04/20/2012 
// Design Name: 
// Module Name:    delay 
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
module timer(clk, rst, startStop, amount, en);
input clk, rst;
input startStop;
input [7:0] amount;
output reg en;

parameter COUNT_SIZE = 8;

reg enNext;
reg [COUNT_SIZE-1:0] cnt, cntNext;
reg state, stateNext;

always@(posedge clk)begin
	cnt <= cntNext;
	state <= stateNext;
	en <= enNext;
end

always@(*)begin
	stateNext = startStop;
	enNext = 0;
	cntNext = cnt;
	if(rst) begin
		cntNext = 0;
		stateNext = 0;
	end
	else if (en)
		stateNext = !state;
	else begin
		case (state)
			0: 
			begin
				cntNext = 0;
				enNext = 0;
			end
			1: 
			begin 
				cntNext = cnt + 1; 
				enNext = (cnt=={amount, {(COUNT_SIZE-8){1'b1}}});			
			end
		endcase
	end
		
end

//assign en = (cnt=={amount, {(COUNT_SIZE-8){1'b1}}});

endmodule
