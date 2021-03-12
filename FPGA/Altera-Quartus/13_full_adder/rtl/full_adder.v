
module full_adder (
    input  wire in1,
    input  wire in2,
    input  wire cin,

    output wire sum,
    output wire cout
);
    wire h0_sum;
    wire h0_cout;
    wire h1_cout;

    half_adder half_adder_inst0
    (
        .in1  ( in1 ),
        .in2  ( in2 ),

        .sum  ( h0_sum ),
        .cout ( h0_cout )
    );

    half_adder half_adder_inst1
    (
        .in1  ( in1 ),
        .in2  ( cin ),

        .sum  ( sum ),
        .cout ( h1_cout )
    );
    
    assign cout = h0_cout | h1_cout;

endmodule