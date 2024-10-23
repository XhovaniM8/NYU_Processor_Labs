module Exercise3 (
    input logic clk,
    input logic nReset,
    input logic [3:0] a,          // 4-bit input a
    input logic [15:0] b,         // 16-bit input b
    input logic [15:0] c,         // 16-bit input c
    output logic [15:0] out       // 16-bit output
);

    // Declare intermediate signals for outputs of Alpha & Beta (8 bits)
    logic [7:0] a_in, b_in;

    // Instantiate Alpha (Mystery1)
    Mystery1 alpha_instance (
        .a(a[1:0]),               // Connect a[1:0] to Alpha
        .b(b[7:0]),               // Connect b[7:0] to Alpha
        .c(c[7:0]),               // Connect c[7:0] to Alpha
        .d(a_in)                  // Output a_in (8 bits)
    );

    // Instantiate Beta (Mystery1)
    Mystery1 beta_instance (
        .a(a[3:2]),               // Connect a[3:2] to Beta
        .b(b[15:8]),              // Connect b[15:8] to Beta
        .c(c[15:8]),              // Connect c[15:8] to Beta
        .d(b_in)                  // Output b_in (8 bits)
    );

    // Instantiate Gamma (Mystery2)
    Mystery2 gamma_instance (
        .clk(clk),                // Clock input
        .nReset(nReset),          // Reset input
        .a_in(a_in),              // Connect a_in (8 bits) from Alpha
        .b_in(b_in),              // Connect b_in (8 bits) from Beta
        .out(out)                 // Output from Gamma
    );

endmodule
