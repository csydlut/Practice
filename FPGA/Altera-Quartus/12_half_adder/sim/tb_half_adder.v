`timescale 1ns/1ns

module tb_half_adder();

reg  in1;
reg  in2;

wire sum;
wire cout;

initial begin
    in1 <= 1'b0;
    in2 <= 1'b1;
end

always #10 in1 <= {$random} % 2;
always #10 in2 <= {$random} % 2;

half_adder half_adder_inst
(
    .in1  (in1),
    .in2  (in2),

    .sum  (sum),
    .cout (cout)
);

endmodule