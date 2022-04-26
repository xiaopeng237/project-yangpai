cmake_minimum_required(VERSION 3.10)


file(GLOB SOURCES "i2c_2631hv.c"  )
add_executable(i2c_2631hv ${SOURCES} )
set (PROJECT_LINK_LIBS   pthread  m )
target_link_libraries(i2c_2631hv ${PROJECT_LINK_LIBS} )

#install(TARGETS service_i2c_proxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib)
#install(TARGETS yangpi_service_i2cbus DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin)
#install(FILES  i2cbus_base.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)
#install(FILES  yangpi_i2c_proxy.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../depend/include)