
module data_gen (
    input  wire      clk_50m,
    input  wire      rst_n,

    output reg       data_en,
    output reg [7:0] data_in
);

always @(posedge clk_50m or negedge rst_n) begin
    if( rst_n == 1'b0 )
        data_en <= 1'b0;
    else
        data_en <= 1'b1;    
end

always @(posedge clk_50m or negedge rst_n) begin
    if( rst_n == 1'b0 )
        data_in <= 8'd0;
    else
        if( data_in == 8'd199 )
            data_in <= 8'd0;
        else
            if( data_en == 1'b1 )
                data_in <= data_in + 1'b1;
            else
                data_in <= data_in;
end
    
endmodule