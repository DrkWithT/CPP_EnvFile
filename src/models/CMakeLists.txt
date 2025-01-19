add_library(models "")
target_include_directories(models PUBLIC "${MY_INCLUDES_DIR}")
target_sources(models PRIVATE exceptions.cpp envdoc.cpp)
