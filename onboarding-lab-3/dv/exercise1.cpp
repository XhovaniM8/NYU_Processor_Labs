#include <iostream>
#include <VExercise1.h>

int main() {
  VExercise1 model;

  // Loop through all possible values of a and b (assuming 8-bit inputs)
  for(int a = 0; a < 256; ++a) {
    for(int b = 0; b < 256; ++b) {

      // Test for each operation defined by 'op'
      for(int op = 0; op < 4; ++op) {
        model.a = a;
        model.b = b;
        model.op = op;
        model.eval();

        // Determine expected result based on operation
        int expected;
        switch(op) {
          case 0:
            expected = a ^ b; // a xor b
            break;
          case 1:
            expected = a << b; // 
            break;
          case 2:
            expected = (b == 0) ? 0 : a % b;
            break;
          case 3:
            expected = ~(a & b);
            break;
          default:
            expected = -1; // Invalid operation
        }

        // Verify the result
        if(model.out != expected) {
          std::cerr << "Test failed for a = " << a << ", b = " << b
                    << ", op = " << op << ". Expected: " << expected
                    << ", Got: " << model.out << std::endl;
        }
      }
    }
  }

  return 0;
}
