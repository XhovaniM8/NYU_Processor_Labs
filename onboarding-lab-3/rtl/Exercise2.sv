/**
  @brief A fibonacci linear feedback shift register module

  @input clk    clock
  @input reset  active-high reset
  @input init   inverse of initial value following a reset
  @output out   current output
*/
module Exercise2 (
    input clk,
    input reset,
    input [15:0] init,
    output logic [15:0] out
);
  always_ff @(negedge clk)
    if (reset) out <= ~init;
    else out <= {out[14:0], out[10] ^ out[8] ^ out[3] ^ out[1]};
endmodule
