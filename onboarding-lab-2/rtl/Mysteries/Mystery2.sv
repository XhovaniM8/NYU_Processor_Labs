/**
  @brief Spooky Mystery Module

  @input clk    clock
  @input nReset active-low reset
  @input a_in   alpha input
  @input b_in   beta input

  @output out    output
*/
module Mystery2 (
    input clk,
    input nReset,
    input [7:0] a_in,
    input [7:0] b_in,
    output logic [15:0] out
);
  logic [1:0] count;
  always_ff @(posedge clk)
    if (!nReset) begin
      out   <= {a_in, b_in};
      count <= 0;
    end else begin
      case (count)
        0: out <= {out[7:0], out[15:8]};
        1: out <= {out[7:0], a_in};
        2: out <= {b_in, out[15:8]};
        3: out <= {out[3:0], out[7:4], out[11:8], out[15:12]};
      endcase
      count <= count + 1;
    end
endmodule
