cmake_minimum_required(VERSION 3.10)


file(GLOB SOURCES "yangpi_rtu_proxy.c" )
add_library(service_rtu_proxy SHARED ${SOURCES})


add_executable(yangpi_service_rtu freemodbus_rtu.c
        mbascii.c
        mb.c
        mbcrc.c
        mbfunccoils.c
        mbfuncdiag.c
        mbfuncdisc.c
        mbfuncholding.c
        mbfuncinput.c
        mbfuncother.c
        mbrtu.c
        mbutils.c
        portevent.c
        portother.c
        portserial.c
        porttimer.c
        rtu_service.c
        yangpi_rtu_main.c
        yangpi_rtu_stub.c)
set (PROJECT_LINK_LIBS pthread  m dl dlt dbus-1 yangpai_service service_mysql_proxy)
target_link_libraries(yangpi_service_rtu ${PROJECT_LINK_LIBS} )

install(TARGETS service_rtu_proxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib)
install(TARGETS yangpi_service_rtu DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin)
install(FILES  rtu_data_base.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)
install(FILES  yangpi_rtu_proxy.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)