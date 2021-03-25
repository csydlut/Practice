
module mydecoder (
    input  wire     in_val1,
    input  wire     in_val2,
    input  wire     in_val3,

    output reg[7:0] out_val
);
    always @(*) begin
        case ({in_val1, in_val2, in_val3})
            3'b000 : 
                out_val = 8'b0000_0001;
            3'b001 :
                out_val = 8'b0000_0010;
            3'b010 :
                out_val = 8'b0000_0100;
            3'b011 :
                out_val = 8'b0000_1000;
            3'b100 :
                out_val = 8'b0001_0000;
            3'b101 :
                out_val = 8'b0010_0000;
            3'b110 :
                out_val = 8'b0100_0000;
            3'b111 :
                out_val = 8'b1000_0000;
            default: 
                out_val = 8'b0000_0000;
        endcase
    end
endmodule