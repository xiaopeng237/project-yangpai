# Install script for directory: /home/admin/repo/project-yangpai/project_pioneers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/lib/libservice_pioneers_proxy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/lib/libservice_pioneers_proxy.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/lib/libservice_pioneers_proxy.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/admin/repo/project-yangpai/project_pioneers/../depend/lib/libservice_pioneers_proxy.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/admin/repo/project-yangpai/project_pioneers/../depend/lib" TYPE SHARED_LIBRARY FILES "/home/admin/repo/project-yangpai/project_pioneers/libservice_pioneers_proxy.so")
  if(EXISTS "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/lib/libservice_pioneers_proxy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/lib/libservice_pioneers_proxy.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/lib/libservice_pioneers_proxy.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/admin/repo/project-yangpai/project_pioneers/../depend/bin" TYPE EXECUTABLE FILES "/home/admin/repo/project-yangpai/project_pioneers/yangpi_service_pioneers")
  if(EXISTS "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers"
         OLD_RPATH "/home/admin/repo/project-yangpai/depend/mysql/lib/mysql:/home/admin/repo/project-yangpai/depend/dlt/lib:/home/admin/repo/project-yangpai/depend/dbus/lib:/home/admin/repo/project-yangpai/project_frame:/home/admin/repo/project-yangpai/project_mysql:/home/admin/repo/project-yangpai/project_adjust:/home/admin/repo/project-yangpai/project_i2cbus:/home/admin/repo/project-yangpai/project_ota:/home/admin/repo/project-yangpai/project_freemodbus:/home/admin/repo/project-yangpai/depend/lib:/home/admin/repo/project-yangpai/cmake-build-debug/project_frame:/home/admin/repo/project-yangpai/cmake-build-debug/project_mysql:/home/admin/repo/project-yangpai/cmake-build-debug/project_i2cbus:/home/admin/repo/project-yangpai/cmake-build-debug/project_adjust:/home/admin/repo/project-yangpai/cmake-build-debug/project_pioneers:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/admin/repo/project-yangpai/project_pioneers/../depend/bin/yangpi_service_pioneers")
    endif()
  endif()
endif()

