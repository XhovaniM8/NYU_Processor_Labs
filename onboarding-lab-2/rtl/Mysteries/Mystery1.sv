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
      0: d = b;
      1: begin
        d[7:4] = b[3:0];
        d[3:0] = c[7:4];
      end
      2: d = c;
      3: begin
        d[7:6] = a;
        d[5:3] = c[2:0];
        d[2:0] = b[2:0];
      end
    endcase
endmodule
