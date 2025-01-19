add_library(api "")
target_include_directories(api PUBLIC "${MY_INCLUDES_DIR}")
target_sources(api PRIVATE myenv.cpp)
