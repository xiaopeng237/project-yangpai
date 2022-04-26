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

file(GLOB SOURCES "yangpi_ota_proxy.c" )
add_library(service_ota_proxy SHARED ${SOURCES})

file(GLOB SOURCES "yangpi_ota_stub.c" "yangpi_ota_main.c" )
add_executable(yangpi_service_ota ${SOURCES} ota_data_base.c ota_data_base.h ota_service.c)
set (PROJECT_LINK_LIBS mysqlclient  pthread  m dl dlt dbus-1 pthread yangpai_service curl service_mysql_proxy)
target_link_libraries(yangpi_service_ota ${PROJECT_LINK_LIBS} )


install(TARGETS service_ota_proxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib)
install(TARGETS yangpi_service_ota DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin)
install(FILES  ota_data_base.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)
install(FILES  yangpi_ota_proxy.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)