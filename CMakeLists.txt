########################################################
# cmake file for building Marlin example Package
# @author Jan Engels, Desy IT
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################

# project name
project(mymarlinprocessoris)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

### DEPENDENCIES ############################################################

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_PATH})
link_libraries(${ROOT_LIBRARIES})

find_package(ILCUTIL REQUIRED COMPONENTS ILCSOFT_CMAKE_MODULES)

# load default settings from ILCSOFT_CMAKE_MODULES
include(ilcsoft_default_settings)

find_package(EUTelescope REQUIRED)
include_directories(${EUTelescope_INCLUDE_DIR})
link_libraries(${EUTelescope_LIBRARIES})

find_package(Marlin 1.0 REQUIRED) # minimum required Marlin version
include_directories(${Marlin_INCLUDE_DIRS})
link_libraries(${Marlin_LIBRARIES})
add_definitions(${Marlin_DEFINITIONS})

# optional package
find_package(AIDA)
if(AIDA_FOUND)
    include_directories( ${AIDA_INCLUDE_DIRS} )
    LINK_LIBRARIES( ${AIDA_LIBRARIES} )
    ADD_DEFINITIONS( "-DMARLIN_USE_AIDA" )
    MESSAGE( STATUS "AIDA -- found" )
else()
    MESSAGE( STATUS "AIDA -- not found" )
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wno-long-long -std=c++11")

include_directories("include")


add_shared_library(TrackerProcessors src/reftrackalignprocessor.cpp src/reftransformprocessor.cpp)

# display some variables and write them to cache
display_std_variables()

