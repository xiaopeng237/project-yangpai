cmake_minimum_required(VERSION 3.10)


#set(CMAKE_C_STANDARD 99)
#set(TOOLCHAIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/")
#set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/arm-fsl-linux-gnueabi-g++)
#set(CMAKE_C_COMPILER   ${TOOLCHAIN_DIR}/bin/arm-fsl-linux-gnueabi-gcc)
#set(GNU_FLAGS "-O2 -g")
#set(CMAKE_CXX_FLAGS "${GNU_FLAGS} ")
#set(CMAKE_C_FLAGS "${GNU_FLAGS}  ")
#set(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_DIR}
#	                ${TOOLCHAIN_DIR}/include
#			${TOOLCHAIN_DIR}/lib )
#
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/mysql)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/mysql)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/dbus-1.0)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/dbus-1.0/include)

file(GLOB SOURCES "yangpi_pioneers_proxy.c" )
add_library(service_pioneers_proxy SHARED ${SOURCES})

file(GLOB SOURCES "yangpi_pioneers_stub.c" "yangpi_pioneers_main.c" )
add_executable(yangpi_service_pioneers ${SOURCES} log_dlt.c log_dlt.h pioneers.c pioneers.h pioneers_spi.c pioneers_spi.h pioneers_service.c pioneers_service.h calculate_flow.c calculate_flow.h)
set (PROJECT_LINK_LIBS   pthread  m dl dlt dbus-1 pthread yangpai_service service_mysql_proxy service_adjust_proxy service_i2c_proxy service_ota_proxy service_rtu_proxy)
target_link_libraries(yangpi_service_pioneers ${PROJECT_LINK_LIBS} )

install(TARGETS service_pioneers_proxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib)
install(TARGETS yangpi_service_pioneers DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin)
#install(TARGETS yangpi_service_pioneers DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)