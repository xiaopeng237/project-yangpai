cmake_minimum_required(VERSION 3.10)


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
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include/dbus-1.0)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/dbus-1.0/include)


file(GLOB SOURCES "yangpi_i2c_proxy.c" )
add_library(service_i2c_proxy SHARED ${SOURCES})

file(GLOB SOURCES "yangpi_i2c_stub.c" "yangpi_i2c_main.c" )
add_executable(yangpi_service_i2cbus ${SOURCES} i2cbus_base.h i2c_bus.c i2c_bus.h i2c_oled.c i2c_oled.h i2cbus_module_base.c i2cbus_module_base.h log_dlt.c log_dlt.h i2c_ad1115.c i2c_ad1115.h i2c_adjust.c i2c_adjust.h)
set (PROJECT_LINK_LIBS   pthread  m dl dlt dbus-1 pthread yangpai_service)
target_link_libraries(yangpi_service_i2cbus ${PROJECT_LINK_LIBS} )

install(TARGETS service_i2c_proxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib)
install(TARGETS yangpi_service_i2cbus DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin)
install(FILES  i2cbus_base.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)
install(FILES  yangpi_i2c_proxy.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)