find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../doc/doxygen.conf.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Documentation build started")

    if(NOT ULTICON_EXAMPLES)
        set(NO_EXAMPLES_DOCUMENTATION "@CMAKE_CURRENT_SOURCE_DIR@/../examples")
    endif()

    add_custom_target(doc ALL 
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with doxygen"
        VERBATIM)
elseif(NOT DOXYGEN_FOUND)
    message(STATUS "Warning: Doxygen not found; manual will not be created")
endif()