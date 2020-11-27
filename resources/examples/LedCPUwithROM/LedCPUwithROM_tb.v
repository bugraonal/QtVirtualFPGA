module LedCPUwithROM_tb;

parameter FREQ = 0;
reg tClk, tRst;
wire [ 7:0]tOutPattern;

//tClk Generation
initial
begin
	tClk <= 1;
	forever
		#5 tClk <= ~tClk;
end

//tRst Generation
initial
begin
	tRst <= 1;
	#30 tRst <= 0;
end

//Data&Jump Error Check
integer dataError, jumpError;
reg errorFlag;

initial
begin
	errorFlag <= 0;
	dataError <= 0;
	jumpError <= 0;
	#31;														//31ns
	if(tOutPattern != 8'hAA)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'hAA, tOutPattern);
		dataError <= dataError+1;
		errorFlag <= 1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;															//41ns
	if(tOutPattern!=8'h55)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h55, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																//61ns
	if(tOutPattern!=8'hCC)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'hCC, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																	//91ns
	if(tOutPattern!=8'h33)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h33, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																//101ns
	if(tOutPattern!=8'hFF)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'hFF, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																	//131ns
	if(tOutPattern!=8'h00)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h00, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																//151ns
	if(tOutPattern!=8'h0A)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h0A, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																	//161ns
	if(tOutPattern!=8'h7F)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h7F, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	if(DUT.addrRd!=8'h0A)
	begin
		$display("Jump Error at time %d, expected %h, received %h", $time, 8'h0A, DUT.addrRd);
		jumpError <= jumpError+1;
	end
	@(tOutPattern)
	#1;																	//181ns
	if(tOutPattern!=8'h80)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h80, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																//191ns
	if(tOutPattern!=8'hFF)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'hFF, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																//201ns
	if(tOutPattern!=8'h00)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h00, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																	//221ns
	if(tOutPattern!=8'h11)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h11, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																	//251ns
	if(tOutPattern!=8'h00)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'h00, tOutPattern);
		dataError <= dataError+1;
	end else
		errorFlag <= 0;
	@(tOutPattern)
	#1;																//261ns
	if(tOutPattern!=8'hAA)
	begin
		$display("Data Error at time %d, expected %h, received %h", $time, 8'hAA, tOutPattern);
		dataError <= dataError+1;
	end
	if(DUT.addrRd!=8'h00)
	begin
		$display("Jump Error at time %d, expected %h, received %h", $time, 8'h00, DUT.addrRd);
		jumpError <= jumpError+1;
	end
	if(dataError==0)
		$display("No Data Error.");
	else
		$display("%d Data Errors.", dataError);
	if(jumpError==0)
		$display("No Jump Error.");
	else
		$display("%d Jump Errors.", jumpError);
	$finish;
end

//Module Connection
LedCPUwithROM #(FREQ) DUT(.clk(tClk), .rst(tRst), .outPattern(tOutPattern));

endmodule
