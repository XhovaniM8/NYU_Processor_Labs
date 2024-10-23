/**
  @brief A fibonacci linear feedback shift register module

  @input clk    clock
  @input nReset active-low reset
  @input init   initial value following a reset
  @output out   current output
*/
module Exercise2 (
    input clk,
    input nReset,
    input [15:0] init,
    output logic [15:0] out
);

always_ff @(posedge clk or negedge nReset) begin
    if (!nReset) begin
        // Active-low reset: initialize LFSR with the value of 'init'
        out <= init;
    end else begin
        // XOR feedback from bits 15, 13, 12, and 10
        logic feedback;
        feedback = out[15] ^ out[13] ^ out[12] ^ out[10];

        // Shift left and insert feedback into the LSB
        out <= {out[14:0], feedback};
    end
end

endmodule
