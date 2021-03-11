
module touch_ctrl_led (
    input wire sys_clk,
    input wire sys_rst_n,
    input wire touch_key,

    output reg led
);
    reg touch_key_dly1;
    reg touch_key_dly2;

    wire touch_en;

    assign touch_en = touch_key_dly2 & (~touch_key_dly1);

    always @( posedge sys_clk or negedge sys_rst_n ) 
    begin
        if ( sys_rst_n == 1'b0 ) 
            begin
                touch_key_dly1 <= 1'b0;
                touch_key_dly2 <= 1'b0;
            end
        else
            begin
               touch_key_dly1 <= touch_key;
               touch_key_dly2 <= touch_key_dly1; 
            end
    end

    always @( posedge sys_clk or negedge sys_rst_n ) 
    begin
        if ( sys_rst_n == 1'b0 ) 
            led <= 1'b1;
        else
            if( touch_en == 1'b1 )
                led <= ~led;
    end

endmodule