module ram_ctrl (
    input  wire        clk_50m,
    input  wire        clk_25m,
    input  wire        rst_n,
    input  wire [15:0] ram1_rd_data,
    input  wire [15:0] ram2_rd_data,
    input  wire        data_en,
    input  wire [7:0]  data_in,

    output reg         ram1_wr_en,
    output reg         ram1_rd_en,
    output reg  [6:0]  ram1_wr_addr,
    output reg  [5:0]  ram1_rd_addr,
    output wire [7:0]  ram1_wr_data,

    output reg         ram2_wr_en,
    output reg         ram2_rd_en,
    output reg  [6:0]  ram2_wr_addr,
    output reg  [5:0]  ram2_rd_addr,
    output wire [7:0]  ram2_wr_data,

    output reg  [15:0] data_out
);

parameter IDLE        = 4'b0001,
          WRAM1       = 4'b0010,
          WRAM2_RRAM1 = 4'b0100,
          WRAM1_RRAM2 = 4'b1000;

reg [3:0] state;
reg [7:0] data_in_reg;

assign ram1_wr_data = ( ram1_wr_en == 1'b1 ) ? data_in_reg : 8'd0;
assign ram2_wr_data = ( ram2_wr_en == 1'b1 ) ? data_in_reg : 8'd0;

always @( negedge clk_50m or negedge rst_n) begin
    if( rst_n == 1'b0 )
        data_in_reg <= 8'd0;
    else
        data_in_reg <= data_in; 
end

always @( negedge clk_50m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        state <= IDLE;
    else
        case (state)
            IDLE  :
                if( data_en == 1'b1 )
                    state <= WRAM1;

            WRAM1 :
                if( ram1_wr_addr == 7'd99 )
                    state <= WRAM2_RRAM1;

            WRAM2_RRAM1 :
                if( ram2_wr_addr == 7'd99 )
                    state <= WRAM1_RRAM2;

            WRAM1_RRAM2 :
                if( ram1_wr_addr == 7'd99 )
                    state <= WRAM2_RRAM1;
            default: 
                state <= IDLE;
        endcase
end

always @(*) begin
    case (state)
        IDLE :
            begin
                ram1_wr_en = 1'b0;
                ram2_wr_en = 1'b0;
            end
        WRAM1 :
            begin
                ram1_wr_en = 1'b1;
                ram2_wr_en = 1'b0;
            end
        WRAM2_RRAM1 :
            begin
                ram1_wr_en = 1'b0;
                ram2_wr_en = 1'b1;
            end
        WRAM1_RRAM2 :
            begin
                ram1_wr_en = 1'b1;
                ram2_wr_en = 1'b0;
            end
        default: ;
    endcase
end

always @( negedge clk_25m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        ram1_rd_en <= 1'b0;
    else
        if( state == WRAM1_RRAM2 )
            ram1_rd_en <= 1'b1;
        else
            ram1_rd_en <= 1'b0;
end

always @( negedge clk_25m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        ram2_rd_en <= 1'b0;
    else
        if( state == WRAM1_RRAM2 )
            ram2_rd_en <= 1'b1;
        else
            ram2_rd_en <= 1'b0;
end

always @( negedge clk_50m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        ram1_wr_addr <= 7'd0;
    else
        if( ram1_wr_addr == 7'd99 )
            ram1_wr_addr <= 7'd0;
        else
            if( ram1_wr_en == 1'b1 ) 
                ram1_wr_addr <= ram1_wr_addr + 1'b1;
end

always @( negedge clk_50m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        ram2_wr_addr <= 7'd0;
    else
        if( ram2_wr_addr == 7'd99 )
            ram2_wr_addr <= 7'd0;
        else
            if( ram2_wr_en == 1'b1 ) 
                ram2_wr_addr <= ram2_wr_addr + 1'b1;
end

always @( negedge clk_25m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        ram1_rd_addr <= 6'd0;
    else
        if( ram1_rd_addr == 6'd49 )
            ram1_rd_addr <= 6'b0;
        else
            if( ram1_rd_en == 1'b1 ) 
                ram1_rd_addr <= ram1_rd_addr + 1'b1;
end

always @( negedge clk_25m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        ram2_rd_addr <= 6'd0;
    else
        if( ram2_rd_addr == 6'd49 )
            ram2_rd_addr <= 6'b0;
        else
            if( ram2_rd_en == 1'b1 ) 
                ram2_rd_addr <= ram2_rd_addr + 1'b1;
end

always @( negedge clk_25m or negedge rst_n ) begin
    if( rst_n == 1'b0 )
        data_out <= 16'd0;
    else
        if( ram1_rd_en == 1'b1 )
            data_out <= ram1_rd_data;
        else
            if( ram2_rd_en == 1'b1 )
                data_out <= ram2_rd_data;
            else
                data_out <= 16'd0;
end

endmodule