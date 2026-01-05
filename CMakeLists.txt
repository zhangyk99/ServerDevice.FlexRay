cmake_minimum_required(VERSION 3.11)

project(MTestServer.Device.FlexRay)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    if(CMAKE_CL_64)
        link_directories(tools/serverlogger/win64 tools/watchdog/win64 tools/Common/win64)
    else()
        link_directories(tools/serverlogger/win32 tools/watchdog/win32 tools/Common/win32 tools/flexraywrapper/win32)
    endif()
elseif(UNIX AND NOT APPLE)
    link_directories(tools/serverlogger/linux tools/watchdog/linux tools/Common/linux tools/flexraywrapper/linux)
endif()

include_directories(src tools)

file(GLOB SRC_FILES "./src/*cpp")

if (WIN32)
    add_library(MTestServer.Device.FlexRay SHARED mtestserver_device_flexray.cpp ${SRC_FILES})
    set_target_properties(MTestServer.Device.FlexRay PROPERTIES
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR})
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fPIC")
    add_library(MTestServer.Device.FlexRay SHARED mtestserver_device_flexray.cpp ${SRC_FILES})
endif ()

target_include_directories(MTestServer.Device.FlexRay PRIVATE "./src")

target_link_libraries(MTestServer.Device.FlexRay PRIVATE
        serverlogger MTestServer.Watchdog MTestServer.Common
)

#add_subdirectory(test)
