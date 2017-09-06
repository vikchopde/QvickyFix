


cmake_minimum_required(VERSION 3.2.2)
project(QvickyFix)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

include_directories("/home/vikram/vikram/tools/pugixml-1.8/src"
                    "/home/vikram/vikram/gitrepo/study/cpp/QvickyFix/include")

find_package(Boost REQUIRED COMPONENTS program_options regex)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    set(SOURCE_FILES main.cpp include/FIXField.h include/FIXFieldStore.h include/FIXParser.h include/FIXSpecManager.h include/FIXWriter.h)

    add_executable(QvickyFix ${SOURCE_FILES})

    target_link_libraries(QvickyFix /home/vikram/vikram/tools/pugixml-1.8/libpugixml.a
                                ${boost_PROGRAM_OPTIONS_LIBRARY} ${boost_REGEX_LIBRARY})
endif()
