/**
  @brief Spooky Mystery Module

  @input clk    clock
  @input reset  active high reset
  @input a_in   alpha input
  @input b_in   beta input

  @output out    output
*/
module Mystery2 (
    input clk,
    input reset,
    input [7:0] a_in,
    input [7:0] b_in,
    output logic [15:0] out
);
  logic [2:0] count;
  always_ff @(negedge clk)
    if (reset) begin
      out   <= {b_in, a_in};
      count <= 0;
    end else begin
      case (count)
        0: out <= {a_in, out[7:0]};
        1: out <= {out[15:8], b_in};
        2: out <= {out[7:0], out[15:8]};
        3: out <= {out[3:0], out[7:4], out[11:8], out[15:12]};
        4: out <= {15'b0, ^out};
      endcase
      count <= (count + 1) % 5;
    end
endmodule
