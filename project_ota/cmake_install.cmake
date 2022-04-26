# Install script for directory: /var/lib/jenkins/workspace/project-yangpai/project_ota

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
  if(EXISTS "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib/libservice_ota_proxy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib/libservice_ota_proxy.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib/libservice_ota_proxy.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib/libservice_ota_proxy.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib" TYPE SHARED_LIBRARY FILES "/var/lib/jenkins/workspace/project-yangpai/project_ota/libservice_ota_proxy.so")
  if(EXISTS "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib/libservice_ota_proxy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib/libservice_ota_proxy.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/lib/libservice_ota_proxy.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin" TYPE EXECUTABLE FILES "/var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_service_ota")
  if(EXISTS "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota"
         OLD_RPATH "/var/lib/jenkins/workspace/project-yangpai/depend/mysql/lib/mysql:/var/lib/jenkins/workspace/project-yangpai/depend/dlt/lib:/var/lib/jenkins/workspace/project-yangpai/depend/dbus/lib:/var/lib/jenkins/workspace/project-yangpai/project_frame:/var/lib/jenkins/workspace/project-yangpai/project_mysql:/var/lib/jenkins/workspace/project-yangpai/depend/lib:/var/lib/jenkins/workspace/project-yangpai/cmake-build-debug/project_frame:/var/lib/jenkins/workspace/project-yangpai/cmake-build-debug/project_mysql:/var/lib/jenkins/workspace/project-yangpai/cmake-build-debug/project_i2cbus:/var/lib/jenkins/workspace/project-yangpai/cmake-build-debug/project_adjust:/var/lib/jenkins/workspace/project-yangpai/cmake-build-debug/project_pioneers:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/bin/yangpi_service_ota")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/include/ota_data_base.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/include" TYPE FILE FILES "/var/lib/jenkins/workspace/project-yangpai/project_ota/ota_data_base.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/include/yangpi_ota_proxy.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/var/lib/jenkins/workspace/project-yangpai/project_ota/../depend/include" TYPE FILE FILES "/var/lib/jenkins/workspace/project-yangpai/project_ota/yangpi_ota_proxy.h")
endif()

