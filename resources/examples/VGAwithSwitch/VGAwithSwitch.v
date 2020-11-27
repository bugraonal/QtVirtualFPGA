module VGAwithSwitch(clk, rst, switch,	hsync, vsync, rgb);

input clk, rst;
input [2:0] switch;
output hsync, vsync;
output [2:0] rgb;

wire video_on;
wire [9:0] pixel_x, pixel_y;

// instantiate vgaSync and pixelGeneration circuit
vgaSync vgaSync(.clk(clk), .rst(rst), .hsync(hsync), .vsync(vsync), .video_on(video_on), .p_tick(), .pixel_x(pixel_x), .pixel_y(pixel_y));

pixelGeneration pixelGeneration(.switch(switch), .pixel_x(pixel_x), .pixel_y(pixel_y), .video_on(video_on), .rgb(rgb));

endmodule
