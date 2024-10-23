/**
  @brief An asynchronous mux/decoder

  @input sel   input select
  @input cs    chip select

  @input alpha alpha input
  @input beta  beta input
  @input gamma gamma input

  @output out output
*/
module Exercise4 (
    input [1:0] sel,
    input cs,

    input [7:0] alpha,
    input [7:0] beta,
    input [7:0] gamma,

    output logic [7:0] out
);

always_comb begin
    if (cs == 0) begin
        // If chip select is 0, output is always 0
        out = 8'b0;
    end else begin
        // If chip select is 1, select output based on the value of sel
        case (sel)
            2'b00: out = alpha;   // When sel is 00, output alpha
            2'b01: out = beta;    // When sel is 01, output beta
            2'b10: out = gamma;   // When sel is 10, output gamma
            2'b11: out = 8'b0;    // When sel is 11, output 0
            default: out = 8'b0;  // Default case for safety
        endcase
    end
end

endmodule
