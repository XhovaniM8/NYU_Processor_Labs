#include <iostream>
#include <VExercise2.h>

int main() {
  VExercise2 model;
  bool testPassed = true;

  // Test with different initializations
  
  for(uint16_t init_val : {0x1, 0xA5A5, 0xFFFF}) {
    // Step 1: Apply reset and check initial value
    model.reset = 1;
    model.init = init_val;
    model.eval();
    if(model.out != ~init_val) {
      std::cerr << "Reset failed for init = " << init_val
                << ". Expected: " << ~init_val << ", Got: " << model.out
                << std::endl;
      testPassed = false;
    }

    // Step 2: Release reset and verify LFSR behavior for several cycles
    model.reset = 0;
    for(int i = 0; i < 16; ++i) { // Run for 16 cycles as a basic check
      model.eval();               // Evaluate next state
      // Optionally, add expected values here for known sequence checking
      std::cout << "Cycle " << i << ", Output: " << model.out << std::endl;
    }
  }

  if(testPassed) {
    std::cout << "All tests passed for Exercise2 module." << std::endl;
  } else {
    std::cout << "Some tests failed for Exercise2 module." << std::endl;
  }

  return 0;
}
