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
include project_ota/CMakeFiles/yangpi_service_ota.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include project_ota/CMakeFiles/yangpi_service_ota.dir/compiler_depend.make

# Include the progress variables for this target.
include project_ota/CMakeFiles/yangpi_service_ota.dir/progress.make

# Include the compile flags for this target's objects.
include project_ota/CMakeFiles/yangpi_service_ota.dir/flags.make

project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/flags.make
project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o: project_ota/yangpi_ota_main.c
project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o -MF CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o.d -o CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_ota_main.c

project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_ota_main.c > CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.i

project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_ota_main.c -o CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.s

project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/flags.make
project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o: project_ota/yangpi_ota_stub.c
project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o -MF CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o.d -o CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_ota_stub.c

project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_ota_stub.c > CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.i

project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_ota_stub.c -o CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.s

project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/flags.make
project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o: project_ota/ota_data_base.c
project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o -MF CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o.d -o CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_ota/ota_data_base.c

project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_ota/ota_data_base.c > CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.i

project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_ota/ota_data_base.c -o CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.s

project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/flags.make
project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.o: project_ota/ota_service.c
project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.o: project_ota/CMakeFiles/yangpi_service_ota.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.o -MF CMakeFiles/yangpi_service_ota.dir/ota_service.c.o.d -o CMakeFiles/yangpi_service_ota.dir/ota_service.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_ota/ota_service.c

project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_ota.dir/ota_service.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_ota/ota_service.c > CMakeFiles/yangpi_service_ota.dir/ota_service.c.i

project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_ota.dir/ota_service.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_ota/ota_service.c -o CMakeFiles/yangpi_service_ota.dir/ota_service.c.s

# Object files for target yangpi_service_ota
yangpi_service_ota_OBJECTS = \
"CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o" \
"CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o" \
"CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o" \
"CMakeFiles/yangpi_service_ota.dir/ota_service.c.o"

# External object files for target yangpi_service_ota
yangpi_service_ota_EXTERNAL_OBJECTS =

project_ota/yangpi_service_ota: project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_main.c.o
project_ota/yangpi_service_ota: project_ota/CMakeFiles/yangpi_service_ota.dir/yangpi_ota_stub.c.o
project_ota/yangpi_service_ota: project_ota/CMakeFiles/yangpi_service_ota.dir/ota_data_base.c.o
project_ota/yangpi_service_ota: project_ota/CMakeFiles/yangpi_service_ota.dir/ota_service.c.o
project_ota/yangpi_service_ota: project_ota/CMakeFiles/yangpi_service_ota.dir/build.make
project_ota/yangpi_service_ota: project_frame/libyangpai_service.so
project_ota/yangpi_service_ota: project_mysql/libservice_mysql_proxy.so
project_ota/yangpi_service_ota: project_ota/CMakeFiles/yangpi_service_ota.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable yangpi_service_ota"
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yangpi_service_ota.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project_ota/CMakeFiles/yangpi_service_ota.dir/build: project_ota/yangpi_service_ota
.PHONY : project_ota/CMakeFiles/yangpi_service_ota.dir/build

project_ota/CMakeFiles/yangpi_service_ota.dir/clean:
	cd /var/lib/jenkins/workspace/project-yangpai/project_ota && $(CMAKE_COMMAND) -P CMakeFiles/yangpi_service_ota.dir/cmake_clean.cmake
.PHONY : project_ota/CMakeFiles/yangpi_service_ota.dir/clean

project_ota/CMakeFiles/yangpi_service_ota.dir/depend:
	cd /var/lib/jenkins/workspace/project-yangpai && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /var/lib/jenkins/workspace/project-yangpai /var/lib/jenkins/workspace/project-yangpai/project_ota /var/lib/jenkins/workspace/project-yangpai /var/lib/jenkins/workspace/project-yangpai/project_ota /var/lib/jenkins/workspace/project-yangpai/project_ota/CMakeFiles/yangpi_service_ota.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project_ota/CMakeFiles/yangpi_service_ota.dir/depend

