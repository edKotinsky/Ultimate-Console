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

if (NOT CMAKE_CXX_EXTENSIONS)
    set (CMAKE_CXX_EXTENSIONS OFF)
endif ()

if (ULTICON_DEBUG)
    message (STATUS "examples: debug")
endif ()

project(userdata_cin)
add_executable(userdata_cin userdata_cin.cpp)
target_link_libraries(userdata_cin ulticon)

project(variables)
add_executable(variables variables.cpp)
target_link_libraries(variables ulticon)

project(args)
add_executable(args console_args.cpp)
target_link_libraries(args ulticon)

project(keys)
add_executable(keys keys.cpp)
target_link_libraries(keys ulticon)