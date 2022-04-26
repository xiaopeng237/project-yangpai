# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /var/lib/jenkins/workspace/project-yangpai

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /var/lib/jenkins/workspace/project-yangpai

# Include any dependencies generated for this target.
include project_pioneers/CMakeFiles/service_pioneers_proxy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include project_pioneers/CMakeFiles/service_pioneers_proxy.dir/compiler_depend.make

# Include the progress variables for this target.
include project_pioneers/CMakeFiles/service_pioneers_proxy.dir/progress.make

# Include the compile flags for this target's objects.
include project_pioneers/CMakeFiles/service_pioneers_proxy.dir/flags.make

project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o: project_pioneers/CMakeFiles/service_pioneers_proxy.dir/flags.make
project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o: project_pioneers/yangpi_pioneers_proxy.c
project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o: project_pioneers/CMakeFiles/service_pioneers_proxy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_pioneers && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o -MF CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o.d -o CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_pioneers/yangpi_pioneers_proxy.c

project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_pioneers && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_pioneers/yangpi_pioneers_proxy.c > CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.i

project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_pioneers && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_pioneers/yangpi_pioneers_proxy.c -o CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.s

# Object files for target service_pioneers_proxy
service_pioneers_proxy_OBJECTS = \
"CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o"

# External object files for target service_pioneers_proxy
service_pioneers_proxy_EXTERNAL_OBJECTS =

project_pioneers/libservice_pioneers_proxy.so: project_pioneers/CMakeFiles/service_pioneers_proxy.dir/yangpi_pioneers_proxy.c.o
project_pioneers/libservice_pioneers_proxy.so: project_pioneers/CMakeFiles/service_pioneers_proxy.dir/build.make
project_pioneers/libservice_pioneers_proxy.so: project_pioneers/CMakeFiles/service_pioneers_proxy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libservice_pioneers_proxy.so"
	cd /var/lib/jenkins/workspace/project-yangpai/project_pioneers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/service_pioneers_proxy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project_pioneers/CMakeFiles/service_pioneers_proxy.dir/build: project_pioneers/libservice_pioneers_proxy.so
.PHONY : project_pioneers/CMakeFiles/service_pioneers_proxy.dir/build

project_pioneers/CMakeFiles/service_pioneers_proxy.dir/clean:
	cd /var/lib/jenkins/workspace/project-yangpai/project_pioneers && $(CMAKE_COMMAND) -P CMakeFiles/service_pioneers_proxy.dir/cmake_clean.cmake
.PHONY : project_pioneers/CMakeFiles/service_pioneers_proxy.dir/clean

project_pioneers/CMakeFiles/service_pioneers_proxy.dir/depend:
	cd /var/lib/jenkins/workspace/project-yangpai && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /var/lib/jenkins/workspace/project-yangpai /var/lib/jenkins/workspace/project-yangpai/project_pioneers /var/lib/jenkins/workspace/project-yangpai /var/lib/jenkins/workspace/project-yangpai/project_pioneers /var/lib/jenkins/workspace/project-yangpai/project_pioneers/CMakeFiles/service_pioneers_proxy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project_pioneers/CMakeFiles/service_pioneers_proxy.dir/depend

