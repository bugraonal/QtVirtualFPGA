`timescale 1ns / 1ps
module LedCPUwithRAM_tb;

// Inputs
reg clk;
reg rst;
reg enter;
reg rwIn;
reg [7:0] switch;

// Outputs
wire [7:0] outPattern;
parameter NDELAY = 0;
parameter FREQ = 0;

integer errorFlag=0;
integer dataError=0;
integer jumpError=0;
integer ii=0, jj=0;

// Instantiate the Unit Under Test (LedCPUwithRAM)
LedCPUwithRAM #(NDELAY, FREQ) LedCPUwithRAM(
	.clk(clk), 
	.rst(rst), 
	.switch(switch),
	.enter(enter), 
	.outPattern(outPattern)
);

initial
begin
	clk = 1;
	forever
	#5	clk =~clk;
end

initial
begin
	rst = 1;
	#40 rst = 0;
end

initial
begin
	for(jj=0;jj<=255;jj=jj+1)
	begin
		LedCPUwithRAM.mem1R1W_1.array[jj]=0;
	end
	enter = 0;
	rwIn = 0;
	switch = 0;
	#32;
		 switch  = 8'hAA;
	#10 enter = 1;		//41
	#20 enter = 0;
		 switch  = 8'h01;
	#10 enter = 1;		//61
	#20 enter = 0;
		 switch  = 8'h88;
	#10 enter = 1;		//81
	#20 enter = 0;
		 switch  = 8'h03;
	#10 enter = 1;		//101
	#20 enter = 0;
		 switch  = 8'hF0;
	#10 enter = 1;		//121
	#20 enter = 0;
		 switch  = 8'h02;
	#10 enter = 1;		//141
	#20 enter = 0;
		 switch  = 8'h00;
	#10 enter = 1;		//161
	#20 enter = 0;
		 switch  = 8'h00;
	#10 enter = 1;		//181
	#20 enter = 0;
	#88

	for(ii=1; ii<4; ii=ii+1)
	begin
		if(outPattern == 8'hAA)
		begin
			$display("True value at %d, expected %h, received %h", $time, 8'hAA, outPattern);
		end	else begin
			dataError = dataError+1;
			$display("False value at %d, expected %h, received %h", $time, 8'hAA, outPattern);
		end
		#50;

		if(outPattern == 8'h88)
		begin
			$display("True value at %d, expected %h, received %h", $time, 8'h88, outPattern);
		end else begin
			dataError = dataError+1;
			$display("False value at %d, expected %h, received %h", $time, 8'h88, outPattern);
		end
		#60;

		if(outPattern == 8'hF0)
		begin
			$display("True value at %d, expected %h, received %h", $time, 8'hF0, outPattern);
		end else begin
			dataError = dataError+1;
			$display("False value at %d, expected %h, received %h", $time, 8'hF0, outPattern);
		end
		#60;
			
	end
	$finish;
end
      
endmodule

