# Week 3 Lab: Verification

* TESTING IN PROGRESS *
  
Q. Make Note: What testing strategy did you adopt for this Exercise2? What decisions did you have to make and how did you come up with your answers?

A. I checked that out initializes correctly to ~init when reset is set high, using different init values to cover a range of cases. After set reset to low, I ran the module for 16 cycles observing out to ensure it changes after each cycle which is the expected behavior of a LFSR. The testing strategy I used was 'Sampling Initial Values for Multiple Cycles'

Q. How does testing a Don’t Care work? What must be done to ensure the input truly has no effect on output?

A. Testing a Don't Care ensures that the condition doesn't affect the output. You need to ensure that the input is not affecting the output by setting the input to a value that doesn't affect the output. In my testbench, I wrote a function to test the don't care by testing a combination of inputs and making sure it does not affect the output or else the test will fail. 

