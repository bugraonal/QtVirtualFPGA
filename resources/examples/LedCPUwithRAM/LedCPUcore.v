module LedCPUcore(
	clk,
	rst,
	addrRd,
	dataRd,
	outPattern
    );
input clk,rst;
output reg [7:0] addrRd;
input [15:0] dataRd;
output reg [7:0] outPattern; 

parameter FREQ = 50_000_000/16;

reg [7:0] addrRdNext;
reg [1:0] state, stateNext;
reg [7:0] outPatternNext;
reg [22:0] count, countNext;
reg [7:0] processTime, processTimeNext;

always@(posedge clk) begin
	addrRd <= addrRdNext;
	state <= stateNext;
	outPattern <= outPatternNext;
	count <= countNext;
	processTime <= processTimeNext;
end

always@(*)begin
	outPatternNext = outPattern;
	countNext = count;
	processTimeNext = processTime;
	stateNext = state;
	addrRdNext = addrRd;
	if(rst)begin
		addrRdNext = 0;
		stateNext = 0;
		outPatternNext = 0;
		countNext = 0;
		processTimeNext = 0;
	end
	else begin
		case (state)
			0 :begin
				stateNext = 1;
			end
			1 : begin
				if(dataRd[7:0] != 0) begin
					outPatternNext = dataRd[15:8];
					stateNext = 2;
				end
				else begin
					addrRdNext = dataRd[15:8];
					stateNext = 0;
				end
			end
			2 : begin
				countNext = count + 1;
				if(count == FREQ)begin
					processTimeNext = processTime + 1;
					countNext = 0;
				end
				if(processTime == dataRd[7:0])begin
					addrRdNext = addrRd + 1;
					stateNext = 0;
					processTimeNext = 0;
				end
			end
		endcase
	end
end
endmodule
