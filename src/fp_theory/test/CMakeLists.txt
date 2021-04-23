set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples)

# array examples
add_executable(test_symb EXCLUDE_FROM_ALL test.cpp)
target_link_libraries(test_symb boolector ${LIBRARIES})
