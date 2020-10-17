module top_wrapper
#(
    LED_COUNT=8,
    SWITCH_COUNT=8,
    BUTTON_COUNT=4,
    SEG_COUNT=4
) (
    input clk,
    input rst,
    input [SWITCH_COUNT - 1 : 0] sw,
    input [BUTTON_COUNT - 1 : 0] btn,
    output [LED_COUNT - 1 : 0] led,
    output [7 : 0] seg,
    output [SEG_COUNT - 1 : 0] an
);

    // initialize your top module here

endmodule
