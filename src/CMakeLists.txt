add_subdirectory(collections)
add_subdirectory(parser)
add_subdirectory(api)

add_executable(test_envparse)
target_include_directories(test_envparse PUBLIC "${MY_INCLUDES_DIR}")
target_link_directories(test_envparse PUBLIC "${MY_LIBRARIES_DIR}")
target_sources(test_envparse PRIVATE test_envparse.cpp)
# target_link_libraries(test_envparse)
