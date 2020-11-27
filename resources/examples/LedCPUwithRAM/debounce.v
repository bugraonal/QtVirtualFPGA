module debounce (rst, clk, noisy, clean);
   input rst, clk, noisy;
   output clean;

   parameter NDELAY = 650000;
   parameter NBITS = 20;

   reg [NBITS-1:0] count;
   reg xnew, clean;

   always @(posedge clk)
		if(NDELAY != 0)
			if (rst) begin xnew <= noisy; clean <= noisy; count <= 0; end
			else if (noisy != xnew) begin xnew <= noisy; count <= 0; end
			else if (count == NDELAY) clean <= xnew;
			else count <= count+1;
		else
			clean <= noisy;

endmodule
