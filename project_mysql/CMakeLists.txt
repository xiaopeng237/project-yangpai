cmake_minimum_required(VERSION 3.10)

#
#set(CMAKE_C_STANDARD 99)
#set(TOOLCHAIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/")
#set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/arm-fsl-linux-gnueabi-g++)
#set(CMAKE_C_COMPILER   ${TOOLCHAIN_DIR}/bin/arm-fsl-linux-gnueabi-gcc)
#set(GNU_FLAGS "-O2 -g")
#set(CMAKE_CXX_FLAGS "${GNU_FLAGS} ")
#set(CMAKE_C_FLAGS "${GNU_FLAGS}  ")
#set(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_DIR}
#		        ${TOOLCHAIN_DIR}/include
#			${TOOLCHAIN_DIR}/lib )
#
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/mysql)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/mysql)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/dbus-1.0)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/dbus-1.0/include)
#

file(GLOB SOURCES "yangpi_mysql_proxy.c" )
add_library(service_mysql_proxy SHARED ${SOURCES})

file(GLOB SOURCES "yangpi_mysql_stub.c" "yangpi_mysql_main.c" "log_dlt.c" "read_mysql.c" "mysql_service.c")
add_executable(yangpi_service_mysql ${SOURCES})
set (PROJECT_LINK_LIBS mysqlclient  pthread  m dl dlt dbus-1 pthread yangpai_service)
target_link_libraries(yangpi_service_mysql ${PROJECT_LINK_LIBS} )

install(TARGETS service_mysql_proxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib)
install(TARGETS yangpi_service_mysql DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin)
install(FILES  mysql_base.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)
install(FILES  yangpi_mysql_proxy.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)