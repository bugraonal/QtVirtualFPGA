`timescale 1ns / 1ps

module pixelGeneration(switch, pixel_x, pixel_y, video_on, rgb);

input [2:0] switch;
input [9:0] pixel_x, pixel_y;
input video_on;
output reg [2:0] rgb;

wire square_on;

always @(*) begin
	rgb = 3'b000;
	if(video_on) begin
		if(square_on)
			rgb = switch;
		else
			rgb = 3'b110;
	end
end

assign square_on = ((pixel_x > 320 && pixel_x < 360) && (pixel_y > 220 && pixel_y < 260));

endmodule
