module vgaSync(clk, rst, hsync, vsync, video_on, p_tick, pixel_x, pixel_y);
	
input clk, rst;
output hsync, vsync, video_on, p_tick;
output [9:0] pixel_x, pixel_y;
	
// constant declaration
// VGA 640-by-480 sync parameters
parameter HD = 640; // horizontal display area
parameter HF = 48; // h. front (left) border
parameter HB = 16; // h. back (right) border
parameter HR = 96; // h. retrace
parameter VD = 480; // vertical display area
parameter VF = 10; // v. front (top) border
parameter VB = 33; // v. back (bottom) border
parameter VR = 2; // v. retrace

// mod_2 counter
reg mod2;
wire mod2Next;

// sync counters
reg [9:0] h_count, h_countNext;
reg [9:0] v_count, v_countNext;

reg v_sync, h_sync;
wire v_syncNext, h_syncNext;
wire h_end, v_end, pixel_tick;

always @(posedge clk) begin
		mod2 <= #1 mod2Next;
		v_count <= #1 v_countNext;
		h_count <= #1 h_countNext;
		v_sync <= #1 v_syncNext;
		h_sync <= #1 h_syncNext;
end

// mod2 circuit to generate 25 MHz enable tick
assign mod2Next = rst ? 0 : ~mod2;
assign pixel_tick = mod2;

// status signals
// end of horizontal counter (799)
assign h_end = (h_count == (HD+HF+HB+HR-1));

// end of vertical counter (524)
assign v_end = (v_count == (VD+VF+VB+VR-1));

// next-statelogic of mod-800 horizontal sync counter
always @(*) begin
	h_countNext = h_count;
	if(rst)
		h_countNext = 0;
	else if(pixel_tick) // 25 MHz pulse
		if(h_end)
			h_countNext = 0;
		else
			h_countNext = h_count + 1;
end

// next-state logic of mod-525 vertical sync counter
always @(*) begin
	v_countNext = v_count;
	if(rst)
		v_countNext = 0;
	else if(pixel_tick & h_end)
		if(v_end)
			v_countNext = 0;
		else
			v_countNext = v_count + 1;
end

// horizontal and vertical sync , buffered to avoid glitch
// h_svnc_next asserted between 656 and 751
assign h_syncNext = rst ? 0 : (h_count >= (HD+HB) && h_count <= (HD+HB+HR-1));

// v_syncNext asserted between 490 and 491
assign v_syncNext = rst ? 0 : (v_count >= (VD+VB) && v_count <= (VD+VB+VR-1));

// video on/off
assign video_on = (h_count < HD) && (v_count < VD);

// output
assign hsync = h_sync;
assign vsync = v_sync;
assign p_tick = mod2;
assign pixel_x = h_count;
assign pixel_y = v_count;

endmodule
