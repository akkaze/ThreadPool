cmake_minimum_required(VERSION 3.0)
option(THREADPOOL_BUILD_EXAMPLES "Build threadpool examples" ON)
set (CMAKE_CXX_STANDARD 11)
project(threadpool)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE SRCS "src/*.cc")

file(GLOB_RECURSE EXAMPLE_SRCS "example/*.cc")
add_library(threadpool ${SRCS})
target_link_libraries(threadpool pthread)

if(THREADPOOL_BUILD_EXAMPLES)
  set(examples basic barrier)
  foreach(example ${examples})
    add_executable(${example} example/${example}.cc)
    target_link_libraries(${example} threadpool)
    install(TARGETS ${example} DESTINATION bin)
  endforeach()
endif()

