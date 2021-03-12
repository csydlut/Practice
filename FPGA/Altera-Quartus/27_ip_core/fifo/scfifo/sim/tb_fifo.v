`timescale 1ns/1ns

module tb_fifo();

reg       sys_clk;
reg [7:0] pi_data;
reg       pi_flag;
reg       rdreq;
reg       sys_rst_n;
reg [1:0] cnt_baud;

wire [7:0] po_data;
wire       empty;
wire       full;
wire [7:0] usedw;

initial begin
    sys_clk    = 1'b1;
    sys_rst_n <= 1'b0;
    #100;
    sys_rst_n <= 1'b1;
end

always #10 sys_clk = ~sys_clk;

always @( posedge sys_clk or negedge sys_rst_n ) begin
   if ( sys_rst_n == 1'b0 ) 
       cnt_baud <= 2'b0;
   else
        if ( &cnt_baud == 1'b1 )
            cnt_baud <= 2'b0;
        else
            cnt_baud <= cnt_baud + 1'b1;
end

always@(posedge sys_clk or negedge sys_rst_n) begin
    if(sys_rst_n == 1'b0)
        pi_flag <= 1'b0;
    else
        if((cnt_baud == 2'd0) && (rdreq == 1'b0))
            pi_flag <= 1'b1;
        else
            pi_flag <= 1'b0;
end

always@(posedge sys_clk or negedge sys_rst_n) begin
    if(sys_rst_n == 1'b0)
        pi_data <= 8'b0;
    else
        if((pi_data == 8'd255) && (pi_flag == 1'b1))
            pi_data <= 8'b0;
        else
            if(pi_flag == 1'b1)
                pi_data <= pi_data + 1'b1;
end

always@(posedge sys_clk or negedge sys_rst_n) begin
    if(sys_rst_n == 1'b0)
        rdreq <= 1'b0;
    else
        if(full == 1'b1)
            rdreq <= 1'b1;
        else
            if(empty == 1'b1)
                rdreq <= 1'b0;
end

fifo fifo_inst(
    .sys_clk (sys_clk),
    .pi_data (pi_data),
    .pi_flag (pi_flag),
    .rdreq   (rdreq),

    .po_data (po_data),
    .empty   (empty),
    .full    (full),
    .usedw   (usedw)
);

endmodule