cmake_minimum_required (VERSION 3.0.0)

add_compile_options(
    -Wall
    -Wpedantic
    -Wextra

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

project (UltimateConsole VERSION 0.3 LANGUAGES CXX)

get_directory_property (IS_SUBPROJECT PARENT_DIRECTORY)

option(ULTICON_EXAMPLES "Build Ultimate Console examples" OFF)
option(ULTICON_DOC "Enable documentation generating" OFF)
option(ULTICON_WARNS_INTO_ERRS "Turn all warnings into errors" OFF)
option(ULTICON_TRACE "Enable trace messages into file" OFF)

if (ULTICON_TRACE)
    message (STATUS "Ultimate Console: Trace")
    
    set (TRACE trace/trace.cpp)
    
    set(TRACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/trace)
endif ()

configure_file (trace/UC_trace.hpp.in uctrace.hpp)

if (NOT CMAKE_CXX_EXTENSIONS)
    set (CMAKE_CXX_EXTENSIONS OFF)
endif ()

set (SOURCES
    source/cmd.cpp
    source/indata.cpp
    source/interface.cpp
    source/lexer.cpp
    source/printerr.cpp
    source/semalyzer.cpp
    source/synalyzer.cpp
    source/dictionary.cpp
    ${TRACE})

add_library (UltimateConsole STATIC ${SOURCES})
add_library (ulticon ALIAS UltimateConsole)

target_include_directories(UltimateConsole PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${TRACE_DIR}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ulticon
)

target_compile_features (UltimateConsole PUBLIC cxx_std_17)

if (ULTICON_WARNS_INTO_ERRS)
    add_compile_options ( -Werror )
    message (VERBOSE "Ultimate Console: All warnings turned into errors")
endif ()

if (NOT ULTICON_EXAMPLES)
    message (STATUS "Ultimate Console: Examples disabled")
elseif (IS_SUBPROJECT)
    message (STATUS "Ultimate Console: Examples disabled in submodule mode")
else ()
    message (STATUS "Ultimate Console: Examples build enabled")
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/examples 
                      ${CMAKE_CURRENT_SOURCE_DIR}/examples/build)
endif ()

if (NOT ULTICON_DOC)
    message (STATUS "Ultimate Console: Documentation disabled")
elseif (IS_SUBPROJECT)
    message (STATUS "Ultimate Console: Documentation disabled in submodule mode")
else ()
    message (STATUS "Ultimate Console: Documentation enabled")
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/doc
                      ${CMAKE_CURRENT_SOURCE_DIR}/doc/build)
endif ()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

