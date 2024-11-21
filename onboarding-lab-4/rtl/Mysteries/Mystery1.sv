/**
  @brief Spooky Mystery Module

  @input a input
  @input b input
  @input c input

  @output d output
*/
module Mystery1 (
    input [1:0] a,
    input [7:0] b,
    input [7:0] c,
    output logic [7:0] d
);
  always_comb
    case (a)
      0: begin
        d[7:6] = a;
        d[5:3] = b[2:0];
        d[2:0] = c[2:0];
      end
      1: begin
        d[7:6] = a;
        d[5:3] = c[2:0];
        d[2:0] = b[2:0];
      end
      2: d = b;
      3: d = c;
    endcase
endmodule
