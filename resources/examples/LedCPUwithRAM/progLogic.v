module progLogic(clk, rst, switch, enter, addrWr, dataWr, wrEn);
input clk, rst;
input [7:0] switch;
input enter;

output reg[7:0] addrWr;
output reg[15:0] dataWr;
output reg wrEn;

reg[7:0] addrWrNext;
reg[15:0] dataWrNext;
reg wrEnNext;

reg[1:0] state, stateNext;
reg enterDly;
wire enterPos;

assign enterPos = !enterDly && enter;

always@(posedge clk)begin
	addrWr <= #1 addrWrNext;
	dataWr <= #1 dataWrNext;
	wrEn <= #1 wrEnNext;
	state <= #1 stateNext;
	enterDly <= #1 enter;
end

always@(*)begin
	stateNext = state;
	wrEnNext = 0;
	dataWrNext = dataWr;
	addrWrNext = addrWr;
	if (rst) begin
		addrWrNext = 0;
		dataWrNext = 0;
		wrEnNext = 0;
		stateNext = 0;
	end
	else begin
		case(state)
			0: 
			begin
				if (enterPos) begin
					dataWrNext[15:8] = switch; 
					stateNext = 1;
				end
			end
			1: 
			begin
				if (enterPos) begin
					dataWrNext[7:0] = switch; 
					stateNext = 2;
				end
			end
			2:
			begin
				wrEnNext = 1;
				stateNext = 3;
			end
			3: 
			begin
				addrWrNext = addrWr + 1;
				stateNext = 0;
			end
		endcase
	end
end

endmodule 