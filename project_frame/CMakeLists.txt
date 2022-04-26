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
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/dbus-1.0)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/dbus-1.0/include)

file(GLOB SOURCES "*.c" )
add_library(yangpai_service SHARED ${SOURCES} yangpai_service.c )

set (PROJECT_LINK_LIBS  pthread)
target_link_libraries(yangpai_service ${PROJECT_LINK_LIBS} )

install(TARGETS yangpai_service DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib)
#install(TARGETS yangpi_service_pioneers DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin)
install(FILES  yangpai_service.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)