module mem1R1W(
		clk,
		//rd Port
		addrRd,
		dataRd,
		//wr port
		addrWr,
		dataWr,
		wrEn
);
input clk;
//rd Port
input [7:0] addrRd;
output reg [15:0] dataRd;
//wr port
input [7:0] addrWr;
input [15:0] dataWr;
input wrEn;

reg [15:0] array [0:255];

always@(posedge clk) begin
	dataRd <= array[addrRd];
	if(wrEn)
		array[addrWr] <= dataWr;
end

endmodule

