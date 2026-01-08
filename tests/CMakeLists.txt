cmake_minimum_required(VERSION 3.10)
project(MTestServer.Device.FlexRayTest)

find_package(GTest)

add_executable(tests tests.cpp)

if(WIN32)
    target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main flexraywrapper)
else()
    target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main flexraywrapper dl)
endif()


