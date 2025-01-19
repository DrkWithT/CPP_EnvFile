add_library(parsing "")
target_include_directories(parsing PUBLIC "${MY_INCLUDES_DIR}")
target_sources(parsing PRIVATE lexicals.cpp PRIVATE fileread.cpp PRIVATE lexer.cpp PRIVATE envparse.cpp)
