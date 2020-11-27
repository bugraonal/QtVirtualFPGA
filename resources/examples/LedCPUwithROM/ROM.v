`timescale 1ns / 1ps

module ROM(addrRd, dataRd);
input [7:0] addrRd;
output reg [15:0] dataRd;
always @(*) 
    begin
        case(addrRd)
// synthesis
	       8'h00   : dataRd = 16'hA010;
          8'h01   : dataRd = 16'h5020;
          8'h02   : dataRd = 16'h2810;
          8'h03   : dataRd = 16'h1420;
          8'h04   : dataRd = 16'h0A10;
          8'h05   : dataRd = 16'h0519;
          8'h06   : dataRd = 16'h0A00;
          8'h07   : dataRd = 16'hFFFF;
          8'h08   : dataRd = 16'hFFFF;
          8'h09   : dataRd = 16'hFFFF;
          8'h0A   : dataRd = 16'h0A10;
          8'h0B   : dataRd = 16'h1420;
          8'h0C   : dataRd = 16'h2810;
          8'h0D   : dataRd = 16'h5020;
          8'h0E   : dataRd = 16'h0000;
          8'h0F   : dataRd = 16'h0000;
          default : dataRd = 16'h0100;
// simulation
//            8'h00   : dataRd = 16'b10000000_00001000;
//            8'h01   : dataRd = 16'b01000000_00001000;
//            8'h02   : dataRd = 16'b00100000_00001000;
//            8'h03   : dataRd = 16'b00010000_00001000;
//            8'h04   : dataRd = 16'b00001000_00001000;
//            8'h05   : dataRd = 16'b00000100_00001000;
//            8'h06   : dataRd = 16'b00000010_00001000;
//            8'h07   : dataRd = 16'b00000001_00001000;
//            8'h08   : dataRd = 16'b00000010_00001000;
//            8'h09   : dataRd = 16'b00000100_00001000;
//            8'h0A   : dataRd = 16'b00001000_00001000;
//            8'h0B   : dataRd = 16'b00010000_00001000;
//            8'h0C   : dataRd = 16'b00100000_00001000;
//            8'h0D   : dataRd = 16'b01000000_00001000;
//            8'h0E   : dataRd = 16'b00000000_00000000;
//            8'h0F   : dataRd = 16'b00000000_00000000;
//            default : dataRd = 16'b00000000_00000000;
        endcase
    end
endmodule
		  