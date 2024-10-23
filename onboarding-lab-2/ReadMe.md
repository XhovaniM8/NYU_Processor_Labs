# Week 2 Lab: System Verilog

## Question 1
Why do you think the reason for these different testing approaches are? What are their advantages and disadvantages?

### Exhaustive Testing (Exercise 1)
- **Advantages**
    - Guarantees that all possible input combinations are tested
    - Can be used to verify the correctness of the design
    - Good for small designs
  
- **Disadvantages**
    - Not feasible for large designs
    - Time consuming & Resource Intensive
  
- **When to use**
    - When the design has a small amount of input variables
    - For critical modules


### Sampling Initial Values for Multiple Cycles (Exercise 2)
- **Advantages**
    - Covers multi-cycle behavior
    - Efficient for stateful designs
    - It's more practical than exhaustive testing
  
- **Disadvantages**
    - Limited input coverage
    - Resource intensive

- **When to use**
    - When the design is medium sized
    - When the design is critical
    - When the design is simple
  
### Random Testing (Exercise 3)
- **Advantages**
    - Faster than exhaustive testing
    - Can be used to verify the correctness of the design
    - Efficient in large designs

- **Disadvantages**
    - Not guarantee of full coverage
    - Non-deterministic 

- **When to use**
    - When the design is large
    - When looking for bugs!