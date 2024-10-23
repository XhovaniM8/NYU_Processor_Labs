/**
  @brief A simple ALU-like module

  @input op   opcode for the operation to perform
  @input a    input to calculation
  @input b    input to calulation
  @output out result of calculation
*/
module Exercise1 (
    input  [1:0] op,
    input  [7:0] a,
    input  [7:0] b,
    output reg [7:0] out
);

always @(*) begin
    case (op)
        2'b00: out = a + b;   // Addition    (op code - 0)
        2'b01: out = a - b;   // Subtraction (op code - 1)
        2'b10: out = a & b;   // Bitwise AND (op code - 2)
        2'b11: out = a | b;   // Bitwise OR  (op code - 3)
        default: out = 8'b0;  // Default case to avoid latches
    endcase
end

endmodule
