# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/share/workspace/buildroot_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/share/workspace/buildroot_project/cmake-build-debug

# Include any dependencies generated for this target.
include project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/depend.make

# Include the progress variables for this target.
include project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/progress.make

# Include the compile flags for this target's objects.
include project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/flags.make

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o: project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/flags.make
project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o: ../project_vbbr_tools/i2c_2631vbb.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_vbbr_tools && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o   -c /home/share/workspace/buildroot_project/project_vbbr_tools/i2c_2631vbb.c

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_vbbr_tools && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_vbbr_tools/i2c_2631vbb.c > CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.i

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_vbbr_tools && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_vbbr_tools/i2c_2631vbb.c -o CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.s

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.requires:

.PHONY : project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.requires

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.provides: project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.requires
	$(MAKE) -f project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/build.make project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.provides.build
.PHONY : project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.provides

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.provides.build: project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o


# Object files for target i2c_2631vbb
i2c_2631vbb_OBJECTS = \
"CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o"

# External object files for target i2c_2631vbb
i2c_2631vbb_EXTERNAL_OBJECTS =

project_vbbr_tools/i2c_2631vbb: project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o
project_vbbr_tools/i2c_2631vbb: project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/build.make
project_vbbr_tools/i2c_2631vbb: project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable i2c_2631vbb"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_vbbr_tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/i2c_2631vbb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/build: project_vbbr_tools/i2c_2631vbb

.PHONY : project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/build

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/requires: project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/i2c_2631vbb.c.o.requires

.PHONY : project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/requires

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/clean:
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_vbbr_tools && $(CMAKE_COMMAND) -P CMakeFiles/i2c_2631vbb.dir/cmake_clean.cmake
.PHONY : project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/clean

project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/depend:
	cd /home/share/workspace/buildroot_project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/share/workspace/buildroot_project /home/share/workspace/buildroot_project/project_vbbr_tools /home/share/workspace/buildroot_project/cmake-build-debug /home/share/workspace/buildroot_project/cmake-build-debug/project_vbbr_tools /home/share/workspace/buildroot_project/cmake-build-debug/project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project_vbbr_tools/CMakeFiles/i2c_2631vbb.dir/depend

