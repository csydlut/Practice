
module waterled 
#(
    parameter COUNTER_MAX = 25'd24_999_999
)
(
    input  wire      sys_clk,
    input  wire      sys_rst_n,

    output wire[3:0] led_out
);

    reg [24:0] CounterVal;
    reg        CounterFlag;
    reg [3:0]  LedOutReg;

    //count for 500ms.
    always @( posedge sys_clk or negedge sys_rst_n ) begin
        if( sys_rst_n == 1'b0 )
            CounterVal <= 25'b0;
        else
            if( CounterVal == COUNTER_MAX )
                CounterVal <= 25'b0;
            else
                CounterVal <= CounterVal + 1'b1;
    end

    //flag for 500ms reached.
    always @( posedge sys_clk or negedge sys_rst_n ) begin
        if( sys_rst_n == 1'b0 )
            CounterFlag <= 1'b0;
        else
            if( CounterVal == ( COUNTER_MAX - 1 ) )
                CounterFlag <= 1'b1;
            else
                CounterFlag <= 1'b0;
    end

    //water led ctrl.
    always @( posedge sys_clk or negedge sys_rst_n ) begin
        if( sys_rst_n == 1'b0 )
            LedOutReg <= 4'b0001;
        else
            if( ( LedOutReg == 4'b1000 )&&( CounterFlag == 1'b1 ) )
                LedOutReg <= 4'b0001;
            else
                if( CounterFlag == 1'b1 )
                    LedOutReg <= LedOutReg << 1'b1;
                else
                    LedOutReg <= 4'b0001;
    end

    assign led_out = ~LedOutReg;
    
endmodule