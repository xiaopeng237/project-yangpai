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
CMAKE_SOURCE_DIR = /home/admin/repo/project-yangpai

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/admin/repo/project-yangpai

# Include any dependencies generated for this target.
include project_frame/CMakeFiles/yangpai_service.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include project_frame/CMakeFiles/yangpai_service.dir/compiler_depend.make

# Include the progress variables for this target.
include project_frame/CMakeFiles/yangpai_service.dir/progress.make

# Include the compile flags for this target's objects.
include project_frame/CMakeFiles/yangpai_service.dir/flags.make

project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.o: project_frame/CMakeFiles/yangpai_service.dir/flags.make
project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.o: project_frame/yangpai_service.c
project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.o: project_frame/CMakeFiles/yangpai_service.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admin/repo/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.o"
	cd /home/admin/repo/project-yangpai/project_frame && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.o -MF CMakeFiles/yangpai_service.dir/yangpai_service.c.o.d -o CMakeFiles/yangpai_service.dir/yangpai_service.c.o -c /home/admin/repo/project-yangpai/project_frame/yangpai_service.c

project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpai_service.dir/yangpai_service.c.i"
	cd /home/admin/repo/project-yangpai/project_frame && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/admin/repo/project-yangpai/project_frame/yangpai_service.c > CMakeFiles/yangpai_service.dir/yangpai_service.c.i

project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpai_service.dir/yangpai_service.c.s"
	cd /home/admin/repo/project-yangpai/project_frame && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/admin/repo/project-yangpai/project_frame/yangpai_service.c -o CMakeFiles/yangpai_service.dir/yangpai_service.c.s

# Object files for target yangpai_service
yangpai_service_OBJECTS = \
"CMakeFiles/yangpai_service.dir/yangpai_service.c.o"

# External object files for target yangpai_service
yangpai_service_EXTERNAL_OBJECTS =

project_frame/libyangpai_service.so: project_frame/CMakeFiles/yangpai_service.dir/yangpai_service.c.o
project_frame/libyangpai_service.so: project_frame/CMakeFiles/yangpai_service.dir/build.make
project_frame/libyangpai_service.so: project_frame/CMakeFiles/yangpai_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/admin/repo/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libyangpai_service.so"
	cd /home/admin/repo/project-yangpai/project_frame && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yangpai_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project_frame/CMakeFiles/yangpai_service.dir/build: project_frame/libyangpai_service.so
.PHONY : project_frame/CMakeFiles/yangpai_service.dir/build

project_frame/CMakeFiles/yangpai_service.dir/clean:
	cd /home/admin/repo/project-yangpai/project_frame && $(CMAKE_COMMAND) -P CMakeFiles/yangpai_service.dir/cmake_clean.cmake
.PHONY : project_frame/CMakeFiles/yangpai_service.dir/clean

project_frame/CMakeFiles/yangpai_service.dir/depend:
	cd /home/admin/repo/project-yangpai && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/admin/repo/project-yangpai /home/admin/repo/project-yangpai/project_frame /home/admin/repo/project-yangpai /home/admin/repo/project-yangpai/project_frame /home/admin/repo/project-yangpai/project_frame/CMakeFiles/yangpai_service.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project_frame/CMakeFiles/yangpai_service.dir/depend
