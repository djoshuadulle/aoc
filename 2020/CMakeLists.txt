cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "AdventOfCode")
project(${PROJECT_NAME} LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Werror -Wall -Wextra -Wpedantic)

set(CMAKE_BUILD_TYPE Debug)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
    "Choose the type of build, options are: Debug Release
    RelWithDebInfo MinSizeRel." FORCE)
endif()

# Setup ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
else()
  message("ccache not found, repeated builds will be faster if this program is installed")
endif()

###############################################################################
## Build ##
###############################################################################

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(
#   ${PROJECT_SOURCE_DIR}/include
# )

# set(${PROJECT_NAME}_LIBS
# )

# # Declare a C library
# add_library(${PROJECT_NAME}
# )

# # Specify libraries to link a library against
# target_link_libraries(${PROJECT_NAME} PRIVATE
#   ${${PROJECT_NAME}_LIBS}
# )

# Declare a C executable
add_executable(${PROJECT_NAME}_MAIN
  src/day01.c)

# Specify libraries to link a library against
# target_link_libraries(${PROJECT_NAME}_MAIN PRIVATE
  # ${PROJECT_NAME}
  # ${${PROJECT_NAME}_LIBS}
# )
