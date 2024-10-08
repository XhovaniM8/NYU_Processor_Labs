# Lab 1: CMake and Toolchain

### Q&A

**Q. What version of CMake is running in your environment?**  
A. cmake version 3.30.3  

**Q. What is the purpose of cmake_minimum_required(VERSION [major].[minor]) in the CML file?**  
A. The cmake_minimum_required command sets the minimum version of CMake required to build the project.

**Q. Run make help and figure out what the valid targets (command arguments) are for this project.**  
A. The valid targets are:
- all: Build all projects
- clean: Remove all generated files
- hello_world: Build the hello_world executable
- install: Install the compiled files to the system

**Q. The paths used by target_sources and target_include_directories are relative, not absolute. What file or folder are they relative to?**  
A. The paths are relative to the CMakeLists.txt file.

**Q. What are some differences between cmake and ninja?**  
A. CMake is a build system generator, while Ninja is a build system. Ninja is faster and is recommended for this course.

**Q. Why is it important to run cmake in its own directory?**  
A. Running cmake in its own directory keeps the build files separate from the source files.

