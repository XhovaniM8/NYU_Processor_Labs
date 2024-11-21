#include <iostream>
#include <VExercise3.h>

// Helper function to extract bits
uint32_t getBits(uint32_t value, int high, int low) {
  return (value >> low) & ((1 << (high - low + 1)) - 1);
}

int main() {
  VExercise3 model;

  // Initialize simulation time
  uint64_t sim_time = 0;

  // Initialize signals
  model.clk = 0;
  model.nReset = 1; // Start with nReset high to clear module
  model.a = 0;
  model.b = 0;
  model.c = 0;

  // Helper function to toggle the clock and evaluate the model
  auto clock_cycle = [&]() {
    model.clk = 1; // Positive edge
    model.eval();
    sim_time++;

    model.clk = 0; // Negative edge
    model.eval();
    sim_time++;
  };

  model.nReset = 0;
  model.eval();

  // Test Mystery1 functionality
  std::cout << "Testing Mystery1..." << std::endl;
  for(uint8_t a = 0; a < 4; a++) {
    model.a = a;
    model.b = 0xAA; // 10101010
    model.c = 0x55; // 01010101
    model.eval();   // Evaluate the model

    // Debug print for inputs
    std::cout << "Debug: a=" << static_cast<int>(a)
              << ", b=" << static_cast<int>(model.b)
              << ", c=" << static_cast<int>(model.c) << std::endl;

    // Calculate expected value based on Mystery1 logic
    uint8_t expected;
    if(a == 0) {
      expected =
          (0b00 << 6) | (getBits(model.b, 2, 0) << 3) | getBits(model.c, 2, 0);
    } else if(a == 1) {
      expected =
          (0b01 << 6) | (getBits(model.c, 2, 0) << 3) | getBits(model.b, 2, 0);
    } else if(a == 2) {
      expected = model.b;
    } else { // a == 3
      expected = model.c;
    }

    if(a == 0) {
      uint8_t b_low = getBits(model.b, 2, 0);
      uint8_t c_low = getBits(model.c, 2, 0);
      expected = (0b00 << 6) | (b_low << 3) | c_low;

      // Debugging intermediate calculations
      std::cout << "Debug: a=" << static_cast<int>(a)
                << ", b_low=" << static_cast<int>(b_low)
                << ", c_low=" << static_cast<int>(c_low)
                << ", Expected=" << static_cast<int>(expected)
                << ", Got=" << static_cast<int>(model.out) << std::endl;
    }

    // Debug print for expected vs actual output
    std::cout << "Debug: Expected=" << static_cast<int>(expected)
              << ", Got=" << static_cast<int>(model.out) << std::endl;

    if(model.out != expected) {
      std::cerr << "Mystery1 failed for a=" << static_cast<int>(a)
                << ". Expected: " << static_cast<int>(expected)
                << ", Got: " << static_cast<int>(model.out) << std::endl;
      return 1;
    }
  }

  std::cout << "Mystery1 passed all tests!" << std::endl;

  // Test Mystery2 functionality
  std::cout << "Testing Mystery2..." << std::endl;

  // nReset behavior
  model.nReset = 1;
  model.a = 0x0F;   // Example value
  model.b = 0xF0F0; // Example value
  model.c = 0x0F0F; // Example value
  clock_cycle();    // Apply nReset (on negative edge)

  uint16_t a_in = (getBits(model.a, 1, 0) << 3) | getBits(model.a, 3, 2);
  uint16_t expected_out = (model.b & 0xFF) << 8 | (model.c & 0xFF);
  if(model.out != expected_out) {
    std::cerr << "Mystery2 nReset behavior failed. Expected: " << expected_out
              << ", Got: " << model.out << std::endl;
    return 1;
  }

  // Release nReset
  model.nReset = 0;

  // State 0: {a_in, out[7:0]}
  clock_cycle();
  expected_out = (a_in << 8) | getBits(model.out, 7, 0);
  if(model.out != expected_out) {
    std::cerr << "Mystery2 state 0 failed. Expected: " << expected_out
              << ", Got: " << model.out << std::endl;
    return 1;
  }

  // State 1: {out[15:8], b_in}
  clock_cycle();
  expected_out = (getBits(model.out, 15, 8) << 8) | getBits(model.b, 15, 8);
  if(model.out != expected_out) {
    std::cerr << "Mystery2 state 1 failed. Expected: " << expected_out
              << ", Got: " << model.out << std::endl;
    return 1;
  }

  // State 2: {out[7:0], out[15:8]}
  uint16_t prev_out = model.out;
  clock_cycle();
  expected_out = (getBits(prev_out, 7, 0) << 8) | getBits(prev_out, 15, 8);
  if(model.out != expected_out) {
    std::cerr << "Mystery2 state 2 failed. Expected: " << expected_out
              << ", Got: " << model.out << std::endl;
    return 1;
  }

  // State 3: {out[3:0], out[7:4], out[11:8], out[15:12]}
  prev_out = model.out;
  clock_cycle();
  expected_out = (getBits(prev_out, 3, 0) << 12) |
      (getBits(prev_out, 7, 4) << 8) | (getBits(prev_out, 11, 8) << 4) |
      getBits(prev_out, 15, 12);
  if(model.out != expected_out) {
    std::cerr << "Mystery2 state 3 failed. Expected: " << expected_out
              << ", Got: " << model.out << std::endl;
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
    std::cerr << "Mystery2 state 4 failed. Expected: " << expected_out
              << ", Got: " << model.out << std::endl;
    return 1;
  }

  std::cout << "Mystery2 passed all tests!" << std::endl;

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
