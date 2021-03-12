module fifo (
    input  wire       sys_clk,
    input  wire [7:0] pi_data,
    input  wire       pi_flag,

    input  wire       rdreq,
    
    output wire [7:0] po_data,
    output wire       empty,
    output wire       full,
    output wire [7:0] usedw
);

scfifo_256x8 scfifo_256x8_inst(
    .clock (sys_clk),
    .data  (pi_data),
    .rdreq (rdreq),
    .wrreq (pi_flag),

    .empty (empty),
    .full  (full),
    .q     (po_data),
    .usedw (usedw)
);
    
endmodule