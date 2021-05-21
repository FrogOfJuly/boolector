set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples)

# array examples
add_executable(test_symb EXCLUDE_FROM_ALL test.cpp test_cases.cpp test_cases.h)
target_include_directories(test_symb PRIVATE ${DEPS_INCLUDE_DIR})
target_link_libraries(test_symb boolector ${LIBRARIES})
