cmake_minimum_required(VERSION 3.10)
project(stack_lib C)

add_library(stack
    src/stack.c
)

target_include_directories(stack
    PUBLIC include
)

add_executable(test_stack
    test/test_stack.c
    test/unity/unity.c
)

target_include_directories(test_stack
    PRIVATE test/unity
)

target_link_libraries(test_stack
    PRIVATE stack
)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_EXTRACT_ALL YES)

    doxygen_add_docs(
        docs
        ${PROJECT_SOURCE_DIR}/include
    )
endif()