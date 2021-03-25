/* SYNC Reset D Flip Flop. */
/*
module myflipflop (
    input  wire sys_clk,
    input  wire sys_rst_n,

    input  wire key_input,

    output reg  led_out
);
    
    always @( posedge sys_clk ) begin
        if ( sys_rst_n == 1'b0 )
            led_out <= 1'b0;
        else
            led_out <= key_input;
    end

endmodule
*/

module myflipflop (
    input  wire sys_clk,
    input  wire sys_rst_n,
    
    input  wire key_input,

    output reg  led_out
);
    always @( posedge sys_clk or negedge sys_rst_n ) begin
        if( sys_rst_n == 1'b0 )
            led_out <= 1'b0;
        else
            led_out <= key_input;
    end
endmodule