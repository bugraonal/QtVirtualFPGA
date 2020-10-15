module UDC(upDown, rst, clk, seg, an, led);

    input upDown;
    input rst;
    input clk;
    output reg [7:0] seg;
    output reg [3:0] an;
    output [7:0] led;
    

    reg [3:0] cnt, cntNext;
    reg [5:0] timer, timerNext;
    
    assign led = {{4{1'b0}}, cnt};
    
    always @(posedge clk) begin
        cnt <= #1 cntNext;
        timer <= #1 timerNext;
    end

    always @(*) begin
        cntNext = cnt;
        timerNext = timer + 1;
        if(rst) begin
            cntNext = 0; 
            timerNext = 0;
        end
        else begin
        if (timer == 0) begin
            if(upDown)
                cntNext = (cnt == 9) ? 0 : cnt + 1;
            else 
                cntNext = (cnt == 0) ? 9 : cnt - 1;
            end
        end
    end
    
    always @(*) begin
        an  = 4'b0111;
        seg = 8'b1111_1111;
        if(rst) begin 
            an  = 4'b0111;
            seg = 8'b1111_1111;
        end else begin
            case(cnt)
            0: seg = 8'b11000000; 
            1: seg = 8'b11111001;
            2: seg = 8'b10100100;
            3: seg = 8'b10110000;
            4: seg = 8'b10011001;
            5: seg = 8'b10010010;
            6: seg = 8'b10000010;
            7: seg = 8'b11111000;
            8: seg = 8'b10000000;
            9: seg = 8'b10010000;
            default: seg = 8'b11000000;
            endcase
        end
    end
endmodule
