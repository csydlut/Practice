/* Method1 Only divide. */

module divider_six (
    input  wire sys_clk,
    input  wire sys_rst_n,

    output reg clk_out
);

reg [1:0]cnt;

always @( posedge sys_clk or negedge sys_rst_n )
    if( sys_rst_n == 1'b0 )
        cnt <= 2'b0;
    else
        if( cnt == 2'd2 )
            cnt <= 2'b0;
        else 
            cnt <= cnt + 1'b1;

always @( posedge sys_clk or negedge sys_rst_n ) begin
    if( sys_rst_n == 1'b0 )
        clk_out <= 1'b0;
    else
        if( cnt == 2'd2 )
            clk_out <= ~clk_out;
end

endmodule


/* Method2 Divide and decrease Freq. */
/*
module divider_six (
    input  wire sys_clk,
    input  wire sys_rst_n,

    output reg  clk_flag
);

reg [2:0]cnt;

always @( posedge sys_clk or negedge sys_rst_n ) begin
    if( sys_rst_n == 1'b0 )
        cnt <= 3'b0;
    else
        if( cnt == 3'd5 )
            cnt <= 3'b0;
        else
            cnt <= cnt + 1'b1;
end

always @( posedge sys_clk or negedge sys_rst_n ) begin
    if( sys_rst_n == 1'b0 )
        clk_flag <= 1'b0;
    else
        if( cnt == 3'd4 )
            clk_flag <= 1'b1;
        else
            clk_flag <= 1'b0;
end    

endmodule
*/