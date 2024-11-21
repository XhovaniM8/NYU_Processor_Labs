# NYU ProcDesign Development Template

Q. What is a registry?

A. A registry is a collection of information about packages that are available to the package manager.


Q. What is a package?

A. Packages are the source code files (SystemVerilog, C++, or even cmake files) that we wish to use in our projects. The package manager in this cake is vcpkg. 


Q. What’s the difference between an interface library and a “normal” library or executable? Can you think of any uses for this besides SystemVerilog files? (Think about source code used for generic programming)

A. An interface library is referring to a header-only library that's lightweight and don't need compilation immediately. Some uses for this besides SystemVerilog files are C++ header files, CMake files, and other source code files that are used for generic programming.


Q. What is a top module?

A. A top-level module is one which contains all other modules. A top-level module is not instantiated within any other module. It is also the module that is instantiated in the testbench. 