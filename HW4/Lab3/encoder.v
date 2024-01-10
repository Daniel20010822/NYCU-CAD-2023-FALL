//Verilog HDL for "Lab03", "encoder" "functional"


module encoder (
  out3, out2, out1, out0,
  in15, in14, in13, in12, in11, in10, in9, in8, in7, in6, in5, in4, in3, in2, in1, in0
);

  input         in15, in14, in13, in12, in11, in10, in9, in8, in7, in6, in5, in4, in3, in2, in1, in0;
  output        out3, out2, out1, out0;
  reg     [3:0] out;
  wire   [15:0] in;

  assign out3 = out[3];
  assign out2 = out[2];
  assign out1 = out[1];
  assign out0 = out[0];
  always @(*) begin
    if      (in15) out = 4'd15;
    else if (in14) out = 4'd14;
    else if (in13) out = 4'd13;
    else if (in12) out = 4'd12;
    else if (in11) out = 4'd11;
    else if (in10) out = 4'd10;
    else if (in9)  out = 4'd9;
    else if (in8)  out = 4'd8;
    else if (in7)  out = 4'd7;
    else if (in6)  out = 4'd6;
    else if (in5)  out = 4'd5;
    else if (in4)  out = 4'd4;
    else if (in3)  out = 4'd3;
    else if (in2)  out = 4'd2;
    else if (in1)  out = 4'd1;
    else if (in0)  out = 4'd0;
    else           out = 4'd0;
  end
endmodule
