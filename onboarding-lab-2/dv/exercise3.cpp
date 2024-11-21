#include <cstdint>
#include <iostream>
#include <random>
#include <VExercise3.h>

// Helper function to extract bits
uint32_t getBits(uint32_t value, int high, int low) {
  return (value >> low) & ((1 << (high - low + 1)) - 1);
}

// Simulates Mystery1 behavior
uint8_t simulateMystery1(uint8_t a, uint8_t b, uint8_t c) {
  switch(a) {
    case 0:
      return (0b00 << 6) | ((b & 0x7) << 3) | (c & 0x7);
    case 1:
      return (0b01 << 6) | ((c & 0x7) << 3) | (b & 0x7);
    case 2:
      return b;
    case 3:
      return c;
    default:
      return 0; // Should not happen
  }
}

// Simulates Mystery2 behavior
struct Mystery2 {
  uint8_t count {0};
  uint16_t out {0};

  uint16_t reset(uint8_t a_in, uint8_t b_in) {
    out = (b_in << 8) | a_in;
    count = 0;
    return out;
  }

  uint16_t step(uint8_t a_in, uint8_t b_in) {
    switch(count++ % 5) {
      case 0:
        return out = ((a_in << 8) | (out & 0xFF));
      case 1:
        return out = ((out >> 8) << 8) | b_in;
      case 2:
        return out = ((out & 0xFF) << 8) | (out >> 8);
      case 3:
        return out = ((out & 0x0F) << 12) | ((out & 0xF0) << 4) |
            ((out & 0x0F00) >> 4) | ((out >> 12) & 0x0F);
      case 4:
        return out = __builtin_parity(out); // XOR reduction
      default:
        return 0; // Should not happen
    }
  }
};

// Combines Mystery1 and Mystery2 for Exercise3 simulation
struct Exercise3Sim {
  Mystery2 state;

  uint16_t reset(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in = simulateMystery1(a & 0x3, b & 0xFF, c & 0xFF);
    uint8_t b_in = simulateMystery1(a >> 2, b >> 8, c >> 8);
    return state.reset(a_in, b_in);
  }

  uint16_t step(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in = simulateMystery1(a & 0x3, b & 0xFF, c & 0xFF);
    uint8_t b_in = simulateMystery1(a >> 2, b >> 8, c >> 8);
    return state.step(a_in, b_in);
  }
};

// Clock simulation helper
void stepClock(VExercise3& model) {
  model.clk = 0;
  model.eval();
  model.clk = 1;
  model.eval();
}

int main() {
  VExercise3 model;
  Exercise3Sim sim;

  // Random input generation
  std::default_random_engine re {std::random_device {}()};
  std::uniform_int_distribution<uint8_t> rand4 {0, 15};
  std::uniform_int_distribution<uint16_t> rand16;

  // Apply reset and verify
  model.a = rand4(re);
  model.b = rand16(re);
  model.c = rand16(re);
  model.nReset = 0; // Assert reset
  stepClock(model);

  uint16_t expected = sim.reset(model.a, model.b, model.c);
  if(model.out != expected) {
    std::cerr << "Reset failed. Expected: " << expected
              << ", Got: " << model.out << std::endl;
    return 1;
  }

  // Release reset and verify sequential behavior
  model.nReset = 1;
  for(size_t cycles = 0; cycles < 50; ++cycles) {
    model.a = rand4(re);
    model.b = rand16(re);
    model.c = rand16(re);
    stepClock(model);

    expected = sim.step(model.a, model.b, model.c);
    if(model.out != expected) {
      std::cerr << "Cycle " << cycles << " failed. Expected: " << expected
                << ", Got: " << model.out << std::endl;
      return 1;
    }
  }

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
