cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME tables)
project(${PROJECT_NAME})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

# Tables
set(MP2_TABLES_LIBRARY "${PROJECT_NAME}_tables")
set(MP2_TESTS   "tests_${PROJECT_NAME}")

set(MP2_TABLES_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/lib_tables/include")

# Polynoms
set(MP2_LISTS_LIBRARY "${PROJECT_NAME}_lists")
set(MP2_POLYNOMS_LIBRARY "${PROJECT_NAME}_polynoms")
set(MP2_LISTS_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/lib_lists/include")
set(MP2_POLYNOMS_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/lib_polynoms/include")



set(MP2_INTRO_LIBRARY "${PROJECT_NAME}_intro")
set(MP2_INTRO_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/lib_intro/include")

# BUILD
add_subdirectory(samples)
add_subdirectory(gtest)
add_subdirectory(tests)
add_subdirectory(lib_tables/src)
add_subdirectory(lib_lists/src)
add_subdirectory(lib_intro/src)
add_subdirectory(lib_polynoms/src)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "=================================================")
message( STATUS "")
message( STATUS "   Configuration:           ${CMAKE_BUILD_TYPE}")
message( STATUS "   ----------------------------------------------")
message( STATUS "   Library names")
message( STATUS "   MP2_TABLES_LIBRARY:      ${MP2_TABLES_LIBRARY}")
message( STATUS "   MP2_LISTS_LIBRARY:       ${MP2_LISTS_LIBRARY}")
message( STATUS "   MP2_INTRO_LIBRARY:       ${MP2_INTRO_LIBRARY}")
message( STATUS "   MP2_POLYNOMS_LIBRARY:    ${MP2_POLYNOMS_LIBRARY}")
message( STATUS "   ----------------------------------------------")
message( STATUS "   Test project name")
message( STATUS "   MP2_TESTS:               ${MP2_TESTS}")
message( STATUS "   ----------------------------------------------")
message( STATUS "   Include directories")
message( STATUS "   MP2_TABLES_INCLUDE:      ${MP2_TABLES_INCLUDE}")
message( STATUS "   MP2_LISTS_INCLUDE:       ${MP2_LISTS_INCLUDE}")
message( STATUS "   MP2_INTRO_LIBRARY:       ${MP2_INTRO_LIBRARY}")
message( STATUS "   MP2_POLYNOMS_INCLUDE:    ${MP2_POLYNOMS_INCLUDE}")
message( STATUS "=================================================")
message( STATUS "")