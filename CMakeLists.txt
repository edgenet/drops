#################################################################
#   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
#   Please read the README.txt file in the model directory.     #
#################################################################

cmake_minimum_required (VERSION 2.8)

project (drops)

set (SOURCES_files_Source_Files
    src/drops_agent.c
)
source_group ("Source Files" FILES ${SOURCES_files_Source_Files})

set (SOURCES_Source_Files
  ${SOURCES_files_Source_Files}
)

set (SOURCES_files_Header_Files
    include/drops.h
    include/drops_agent.h
)
source_group ("Header Files" FILES ${SOURCES_files_Header_Files})

set (SOURCES_Header_Files
  ${SOURCES_files_Header_Files}
)

set (SOURCES_
  ${SOURCES_Source_Files}
  ${SOURCES_Header_Files}
)

set (WITH_LIBZMQ .)

include_directories (
  ../libzmq/include
  include
  ${CMAKE_INSTALL_PREFIX}/include
  ${WITH_LIBZMQ}
)

set_source_files_properties (
    ${SOURCES_files_Source_Files} PROPERTIES LANGUAGE CXX
)

add_library (
    drops
    ${SOURCES_}
)

install (
    TARGETS drops
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install (
    FILES ${SOURCES_files_Header_Files} DESTINATION include
)

#################################################################
#   GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY    #
#   Please read the README.txt file in the model directory.     #
#################################################################
