#include <iostream>
#include <VExercise4.h>

int main() {
  VExercise4 model;

  // Test variables
  uint8_t alpha = 0xA5; // 10100101
  uint8_t beta = 0x3C;  // 00111100
  uint8_t gamma = 0x96; // 10010110

  // Test case 1: cs = 0 (Don't Care condition)
  // We need to test multiple sel values to ensure they don't affect output
  model.cs = 0;
  model.alpha = alpha;
  model.beta = beta;
  model.gamma = gamma;

  // Test all possible sel values when cs=0
  for(int sel = 0; sel < 4; sel++) {
    model.sel = sel;
    model.eval();

    if(model.out != 0) {
      std::cout
          << "Test failed: When cs=0, output should be 0 regardless of sel"
          << std::endl;
      std::cout << "sel=" << sel << " out=" << (int) model.out << std::endl;
      return 1;
    }
  }

  // Test case 2: cs = 1, test all selector cases
  model.cs = 1;

  // Test sel = 0 (should output alpha)
  model.sel = 0;
  model.eval();
  if(model.out != alpha) {
    std::cout << "Test failed: When cs=1 and sel=0, output should be alpha"
              << std::endl;
    std::cout << "Expected " << (int) alpha << " but got " << (int) model.out
              << std::endl;
    return 1;
  }

  // Test sel = 1 (should output beta)
  model.sel = 1;
  model.eval();
  if(model.out != beta) {
    std::cout << "Test failed: When cs=1 and sel=1, output should be beta"
              << std::endl;
    std::cout << "Expected " << (int) beta << " but got " << (int) model.out
              << std::endl;
    return 1;
  }

  // Test sel = 2 (should output gamma)
  model.sel = 2;
  model.eval();
  if(model.out != gamma) {
    std::cout << "Test failed: When cs=1 and sel=2, output should be gamma"
              << std::endl;
    std::cout << "Expected " << (int) gamma << " but got " << (int) model.out
              << std::endl;
    return 1;
  }

  // Test sel = 3 (should output alpha & (beta | gamma))
  model.sel = 3;
  model.eval();
  uint8_t expected = alpha & (beta | gamma);
  if(model.out != expected) {
    std::cout << "Test failed: When cs=1 and sel=3, output should be alpha & "
                 "(beta | gamma)"
              << std::endl;
    std::cout << "Expected " << (int) expected << " but got " << (int) model.out
              << std::endl;
    return 1;
  }

  // Additional test: Verify Don't Care behavior with different input values
  model.cs = 0;
  // Try different combinations of inputs and see effect on output
  for(uint8_t test_val = 0; test_val < 255; test_val += 51) {
    model.alpha = test_val;
    model.beta = ~test_val;        // Use complement to test different values
    model.gamma = test_val ^ 0xAA; // Use XOR to get more variations

    for(int sel = 0; sel < 4; sel++) {
      model.sel = sel;
      model.eval();

      if(model.out != 0) {
        std::cout << "Don't Care test failed with test_val=" << (int) test_val
                  << " sel=" << sel << std::endl;
        return 1;
      }
    }
  }

  std::cout << "All tests passed!" << std::endl;
  return 0;
}