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
include project_mysql/CMakeFiles/yangpi_service_mysql.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include project_mysql/CMakeFiles/yangpi_service_mysql.dir/compiler_depend.make

# Include the progress variables for this target.
include project_mysql/CMakeFiles/yangpi_service_mysql.dir/progress.make

# Include the compile flags for this target's objects.
include project_mysql/CMakeFiles/yangpi_service_mysql.dir/flags.make

project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/flags.make
project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o: project_mysql/log_dlt.c
project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o -MF CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o.d -o CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_mysql/log_dlt.c

project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_mysql/log_dlt.c > CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.i

project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_mysql/log_dlt.c -o CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.s

project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/flags.make
project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o: project_mysql/mysql_service.c
project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o -MF CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o.d -o CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_mysql/mysql_service.c

project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_mysql/mysql_service.c > CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.i

project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_mysql/mysql_service.c -o CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.s

project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/flags.make
project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o: project_mysql/read_mysql.c
project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o -MF CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o.d -o CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_mysql/read_mysql.c

project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_mysql/read_mysql.c > CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.i

project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_mysql/read_mysql.c -o CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.s

project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/flags.make
project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o: project_mysql/yangpi_mysql_main.c
project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o -MF CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o.d -o CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_mysql/yangpi_mysql_main.c

project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_mysql/yangpi_mysql_main.c > CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.i

project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_mysql/yangpi_mysql_main.c -o CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.s

project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/flags.make
project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o: project_mysql/yangpi_mysql_stub.c
project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o: project_mysql/CMakeFiles/yangpi_service_mysql.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o -MF CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o.d -o CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o -c /var/lib/jenkins/workspace/project-yangpai/project_mysql/yangpi_mysql_stub.c

project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.i"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/lib/jenkins/workspace/project-yangpai/project_mysql/yangpi_mysql_stub.c > CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.i

project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.s"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && /opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain//bin/arm-fsl-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/lib/jenkins/workspace/project-yangpai/project_mysql/yangpi_mysql_stub.c -o CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.s

# Object files for target yangpi_service_mysql
yangpi_service_mysql_OBJECTS = \
"CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o" \
"CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o" \
"CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o" \
"CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o" \
"CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o"

# External object files for target yangpi_service_mysql
yangpi_service_mysql_EXTERNAL_OBJECTS =

project_mysql/yangpi_service_mysql: project_mysql/CMakeFiles/yangpi_service_mysql.dir/log_dlt.c.o
project_mysql/yangpi_service_mysql: project_mysql/CMakeFiles/yangpi_service_mysql.dir/mysql_service.c.o
project_mysql/yangpi_service_mysql: project_mysql/CMakeFiles/yangpi_service_mysql.dir/read_mysql.c.o
project_mysql/yangpi_service_mysql: project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_main.c.o
project_mysql/yangpi_service_mysql: project_mysql/CMakeFiles/yangpi_service_mysql.dir/yangpi_mysql_stub.c.o
project_mysql/yangpi_service_mysql: project_mysql/CMakeFiles/yangpi_service_mysql.dir/build.make
project_mysql/yangpi_service_mysql: project_frame/libyangpai_service.so
project_mysql/yangpi_service_mysql: project_mysql/CMakeFiles/yangpi_service_mysql.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/var/lib/jenkins/workspace/project-yangpai/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable yangpi_service_mysql"
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yangpi_service_mysql.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project_mysql/CMakeFiles/yangpi_service_mysql.dir/build: project_mysql/yangpi_service_mysql
.PHONY : project_mysql/CMakeFiles/yangpi_service_mysql.dir/build

project_mysql/CMakeFiles/yangpi_service_mysql.dir/clean:
	cd /var/lib/jenkins/workspace/project-yangpai/project_mysql && $(CMAKE_COMMAND) -P CMakeFiles/yangpi_service_mysql.dir/cmake_clean.cmake
.PHONY : project_mysql/CMakeFiles/yangpi_service_mysql.dir/clean

project_mysql/CMakeFiles/yangpi_service_mysql.dir/depend:
	cd /var/lib/jenkins/workspace/project-yangpai && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /var/lib/jenkins/workspace/project-yangpai /var/lib/jenkins/workspace/project-yangpai/project_mysql /var/lib/jenkins/workspace/project-yangpai /var/lib/jenkins/workspace/project-yangpai/project_mysql /var/lib/jenkins/workspace/project-yangpai/project_mysql/CMakeFiles/yangpi_service_mysql.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project_mysql/CMakeFiles/yangpi_service_mysql.dir/depend

