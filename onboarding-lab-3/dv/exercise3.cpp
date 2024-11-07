#include <iostream
#include <VExercise3.h>

int main() {
  VExercise3 model;

  // Initialize simulation time
  uint64_t sim_time = 0;

  // Initialize signals
  model.clk = 0;
  model.rst = 1; // Start with reset high to clear module
  model.a = 0;
  model.b = 0;
  model.c = 0;

  // Test Mystery1 and Mystery2 with reset
  model.rst = 1;
  model.a_in = 0xAA; // Test Values
  model.b_in = 0xBB; // Test Values

  // Toggle clock during reset
  for(int clock_count = 0; clock_count < 4; clock_count++) {
    model.clk = !model.clk;
    model.eval();
    sim_time++;
  }

  // Reset to active low
  model.rst = 0;

  // Function to toggle clock and evaluate model
  auto clock_cycle =
      [&]() {
        model.clk = 1; // Positive Edge
        model.eval();
        sim_time++;

        model.clk = 0; // Negative Edge
        model.eval();
        sim_time++;
      }

  // Test Mystery1
  // Test case 1: a = 0
  model.a = 0;
  model.b = 0xAA; // 10101010
  model.c = 0x55; // 01010101
  model.eval();
  uint8_t expected =
      (0x0 << 6) | (getBits(model.b, 2, 0) << 3) | getBits(model.c, 2, 0);
  if(model.d != expected) {
    std::cout << "Mystery1 failed when a=0" << std::endl;
    return 1;
  }

  // Test case 2: a = 1
  model.a = 1;
  model.eval();
  expected =
      (0x1 << 6) | (getBits(model.c, 2, 0) << 3) | getBits(model.b, 2, 0);
  if(model.d != expected) {
    std::cout << "Mystery1 failed when a=1" << std::endl;
    return 1;
  }

  // Test case 3: a = 2
  model.a = 2;
  model.eval();
  if(model.d != model.b) {
    std::cout << "Mystery1 failed when a=2" << std::endl;
    return 1;
  }

  // Test case 4: a = 3
  model.a = 3;
  model.eval();
  if(model.d != model.c) {
    std::cout << "Mystery1 failed when a=3" << std::endl;
    return 1;
  }

  // Test Mystery2
  // Reset behavior
  model.rst = 1;
  model.a_in = 0xAA;
  model.b_in = 0xBB;
  clock_cycle(); // Apply reset on negative edge

  uint16_t expected_out = (model.b_in << 8) | model.a_in;
  if(model.out != expected_out) {
    std::cout << "Mystery2 reset state failed" << std::endl;
    return 1;
  }

  // Test state transitions
  model.rst = 0;
  uint16_t prev_out;

  // State 0: {a_in, out[7:0]}
  clock_cycle();
  expected_out = (model.a_in << 8) | (model.out & 0xFF);
  if(model.out != expected_out) {
    std::cout << "Mystery2 state 0 failed" << std::endl;
    return 1;
  }

  // State 1: {out[15:8], b_in}
  clock_cycle();
  expected_out = ((model.out >> 8) << 8) | model.b_in;
  if(model.out != expected_out) {
    std::cout << "Mystery2 state 1 failed" << std::endl;
    return 1;
  }

  // State 2: {out[7:0], out[15:8]}
  prev_out = model.out;
  clock_cycle();
  expected_out = ((prev_out & 0xFF) << 8) | (prev_out >> 8);
  if(model.out != expected_out) {
    std::cout << "Mystery2 state 2 failed" << std::endl;
    return 1;
  }

  // State 3: {out[3:0], out[7:4], out[11:8], out[15:12]}
  prev_out = model.out;
  clock_cycle();
  expected_out = (getBits(prev_out, 3, 0) << 12) |
      (getBits(prev_out, 7, 4) << 8) | (getBits(prev_out, 11, 8) << 4) |
      (getBits(prev_out, 15, 12));
  if(model.out != expected_out) {
    std::cout << "Mystery2 state 3 failed" << std::endl;
    return 1;
  }

  // State 4: {15'b0, ^out}
  prev_out = model.out;
  clock_cycle();
  uint16_t xor_reduction = 0;
  for(int i = 0; i < 16; i++) {
    xor_reduction ^= (prev_out >> i) & 1;
  }
  expected_out = xor_reduction;
  if(model.out != expected_out) {
    std::cout << "Mystery2 state 4 failed" << std::endl;
    return 1;
  }

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
