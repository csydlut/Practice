module mycounter 
#(
    parameter COUNTER_MAX = 25'd24_999_999
)
(
    input  wire sys_clk,
    input  wire sys_rst_n,

    output reg  led_out
);

    reg [24:0]count_val;

    always @( posedge sys_clk or negedge sys_rst_n ) begin
        if( sys_rst_n == 1'b0 )
            count_val <= 25'b0;
        else
            if( COUNTER_MAX == count_val )
                count_val <= 25'b0;
            else
                count_val <= count_val + 1'b1;
    end

    always @( posedge sys_clk or negedge sys_rst_n ) begin
        if( sys_rst_n == 1'b0 )
            led_out <= 1'b0;
        else
            if( COUNTER_MAX == count_val )
                led_out <= ~led_out;
            else
                led_out <=  led_out;
    end
    
endmodule