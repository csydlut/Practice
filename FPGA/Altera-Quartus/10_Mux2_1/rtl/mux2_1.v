/* 1st Method */
module mux2_1 (
    input wire in1,
    input wire in2,
    
    input wire sel,

    output reg out
);
    always@(*)
        if ( sel == 1'b1 )
            out = in1;
        else
            out = in2;

endmodule

/* 2nd Method */
/*
module mux2_1 (
    input  wire in1,
    input  wire in2,
    
    input  wire sel,

    output reg  out
);

always@(*)
    case (sel)
        1'b1: out = in1;
        1'b0: out = in2;
        default: out = in1;
    endcase

endmodule
*/
/* 3rd Method */
/*
module mux2_1 (
    input  wire in1,
    input  wire in2,

    input  wire sel,

    output wire out
);
    assign out = ( sel == 1'b1 ) ? in1 : in2;

endmodule
*/