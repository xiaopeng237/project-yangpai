cmake_minimum_required(VERSION 3.10)
project(buildroot_project C)

set(CMAKE_C_STANDARD 99)


set(TOOLCHAIN_DIR "/opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/arm-fsl-linux-gnueabi-g++)
set(CMAKE_C_COMPILER   ${TOOLCHAIN_DIR}/bin/arm-fsl-linux-gnueabi-gcc)
set(GNU_FLAGS "-O2 -g")
set(CMAKE_CXX_FLAGS "${GNU_FLAGS} ")
set(CMAKE_C_FLAGS "${GNU_FLAGS}  ")
set(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_DIR}
        ${TOOLCHAIN_DIR}/include
        ${TOOLCHAIN_DIR}/lib )

#mysql
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/mysql/include/mysql)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/mysql/lib/mysql)
#dlt
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/dlt/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/dlt/lib)
#dbus
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/dbus/include/dbus-1.0/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/dbus/lib/dbus-1.0/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/dbus/lib)

#project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/depend/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_frame)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/project_frame)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_frame)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_mysql)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/project_mysql)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_mysql)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_i2cbus)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/project_i2cbus)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_i2cbus)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_adjust)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/project_adjust)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_adjust)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_pioneers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/project_pioneers)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/project_pioneers)

add_subdirectory(project_frame)
add_subdirectory(project_mysql)
add_subdirectory(project_i2cbus)
add_subdirectory(project_adjust)
add_subdirectory(project_pioneers)
add_subdirectory(project_freemodbus)
add_subdirectory(project_ota)
add_subdirectory(project_hv_tools)
add_subdirectory(project_vbbr_tools)
