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
include project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/depend.make

# Include the progress variables for this target.
include project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/progress.make

# Include the compile flags for this target's objects.
include project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o: ../project_pioneers/yangpi_pioneers_stub.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o   -c /home/share/workspace/buildroot_project/project_pioneers/yangpi_pioneers_stub.c

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_pioneers/yangpi_pioneers_stub.c > CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.i

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_pioneers/yangpi_pioneers_stub.c -o CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.s

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.requires:

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.provides: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.requires
	$(MAKE) -f project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.provides.build
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.provides

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.provides.build: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o


project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o: ../project_pioneers/yangpi_pioneers_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o   -c /home/share/workspace/buildroot_project/project_pioneers/yangpi_pioneers_main.c

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_pioneers/yangpi_pioneers_main.c > CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.i

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_pioneers/yangpi_pioneers_main.c -o CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.s

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.requires:

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.provides: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.requires
	$(MAKE) -f project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.provides.build
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.provides

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.provides.build: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o


project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o: ../project_pioneers/log_dlt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o   -c /home/share/workspace/buildroot_project/project_pioneers/log_dlt.c

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_pioneers/log_dlt.c > CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.i

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_pioneers/log_dlt.c -o CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.s

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.requires:

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.provides: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.requires
	$(MAKE) -f project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.provides.build
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.provides

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.provides.build: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o


project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o: ../project_pioneers/pioneers.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o   -c /home/share/workspace/buildroot_project/project_pioneers/pioneers.c

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_pioneers/pioneers.c > CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.i

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_pioneers/pioneers.c -o CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.s

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.requires:

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.provides: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.requires
	$(MAKE) -f project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.provides.build
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.provides

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.provides.build: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o


project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o: ../project_pioneers/pioneers_spi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o   -c /home/share/workspace/buildroot_project/project_pioneers/pioneers_spi.c

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_pioneers/pioneers_spi.c > CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.i

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_pioneers/pioneers_spi.c -o CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.s

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.requires:

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.provides: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.requires
	$(MAKE) -f project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.provides.build
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.provides

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.provides.build: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o


project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o: ../project_pioneers/pioneers_service.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o   -c /home/share/workspace/buildroot_project/project_pioneers/pioneers_service.c

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_pioneers/pioneers_service.c > CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.i

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_pioneers/pioneers_service.c -o CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.s

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.requires:

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.provides: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.requires
	$(MAKE) -f project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.provides.build
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.provides

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.provides.build: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o


project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/flags.make
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o: ../project_pioneers/calculate_flow.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o   -c /home/share/workspace/buildroot_project/project_pioneers/calculate_flow.c

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_pioneers/calculate_flow.c > CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.i

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_pioneers/calculate_flow.c -o CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.s

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.requires:

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.provides: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.requires
	$(MAKE) -f project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.provides.build
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.provides

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.provides.build: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o


# Object files for target yangpi_service_pioneers
yangpi_service_pioneers_OBJECTS = \
"CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o" \
"CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o" \
"CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o" \
"CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o" \
"CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o" \
"CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o" \
"CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o"

# External object files for target yangpi_service_pioneers
yangpi_service_pioneers_EXTERNAL_OBJECTS =

project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build.make
project_pioneers/yangpi_service_pioneers: project_frame/libyangpai_service.so
project_pioneers/yangpi_service_pioneers: project_mysql/libservice_mysql_proxy.so
project_pioneers/yangpi_service_pioneers: project_adjust/libservice_adjust_proxy.so
project_pioneers/yangpi_service_pioneers: project_i2cbus/libservice_i2c_proxy.so
project_pioneers/yangpi_service_pioneers: project_ota/libservice_ota_proxy.so
project_pioneers/yangpi_service_pioneers: project_freemodbus/libservice_rtu_proxy.so
project_pioneers/yangpi_service_pioneers: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable yangpi_service_pioneers"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yangpi_service_pioneers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build: project_pioneers/yangpi_service_pioneers

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/build

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_stub.c.o.requires
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/yangpi_pioneers_main.c.o.requires
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/log_dlt.c.o.requires
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers.c.o.requires
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_spi.c.o.requires
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/pioneers_service.c.o.requires
project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires: project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/calculate_flow.c.o.requires

.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/requires

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/clean:
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers && $(CMAKE_COMMAND) -P CMakeFiles/yangpi_service_pioneers.dir/cmake_clean.cmake
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/clean

project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/depend:
	cd /home/share/workspace/buildroot_project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/share/workspace/buildroot_project /home/share/workspace/buildroot_project/project_pioneers /home/share/workspace/buildroot_project/cmake-build-debug /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers /home/share/workspace/buildroot_project/cmake-build-debug/project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project_pioneers/CMakeFiles/yangpi_service_pioneers.dir/depend

