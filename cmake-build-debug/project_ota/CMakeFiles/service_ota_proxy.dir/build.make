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
include project_ota/CMakeFiles/service_ota_proxy.dir/depend.make

# Include the progress variables for this target.
include project_ota/CMakeFiles/service_ota_proxy.dir/progress.make

# Include the compile flags for this target's objects.
include project_ota/CMakeFiles/service_ota_proxy.dir/flags.make

project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o: project_ota/CMakeFiles/service_ota_proxy.dir/flags.make
project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o: ../project_ota/yangpi_ota_proxy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_ota && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o   -c /home/share/workspace/buildroot_project/project_ota/yangpi_ota_proxy.c

project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.i"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_ota && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/share/workspace/buildroot_project/project_ota/yangpi_ota_proxy.c > CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.i

project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.s"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_ota && /home/share/workspace/gcc/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/share/workspace/buildroot_project/project_ota/yangpi_ota_proxy.c -o CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.s

project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.requires:

.PHONY : project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.requires

project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.provides: project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.requires
	$(MAKE) -f project_ota/CMakeFiles/service_ota_proxy.dir/build.make project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.provides.build
.PHONY : project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.provides

project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.provides.build: project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o


# Object files for target service_ota_proxy
service_ota_proxy_OBJECTS = \
"CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o"

# External object files for target service_ota_proxy
service_ota_proxy_EXTERNAL_OBJECTS =

project_ota/libservice_ota_proxy.so: project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o
project_ota/libservice_ota_proxy.so: project_ota/CMakeFiles/service_ota_proxy.dir/build.make
project_ota/libservice_ota_proxy.so: project_ota/CMakeFiles/service_ota_proxy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/share/workspace/buildroot_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libservice_ota_proxy.so"
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_ota && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/service_ota_proxy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project_ota/CMakeFiles/service_ota_proxy.dir/build: project_ota/libservice_ota_proxy.so

.PHONY : project_ota/CMakeFiles/service_ota_proxy.dir/build

project_ota/CMakeFiles/service_ota_proxy.dir/requires: project_ota/CMakeFiles/service_ota_proxy.dir/yangpi_ota_proxy.c.o.requires

.PHONY : project_ota/CMakeFiles/service_ota_proxy.dir/requires

project_ota/CMakeFiles/service_ota_proxy.dir/clean:
	cd /home/share/workspace/buildroot_project/cmake-build-debug/project_ota && $(CMAKE_COMMAND) -P CMakeFiles/service_ota_proxy.dir/cmake_clean.cmake
.PHONY : project_ota/CMakeFiles/service_ota_proxy.dir/clean

project_ota/CMakeFiles/service_ota_proxy.dir/depend:
	cd /home/share/workspace/buildroot_project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/share/workspace/buildroot_project /home/share/workspace/buildroot_project/project_ota /home/share/workspace/buildroot_project/cmake-build-debug /home/share/workspace/buildroot_project/cmake-build-debug/project_ota /home/share/workspace/buildroot_project/cmake-build-debug/project_ota/CMakeFiles/service_ota_proxy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project_ota/CMakeFiles/service_ota_proxy.dir/depend

