add_library(parser "")
target_include_directories(parser PUBLIC "${MY_INCLUDES_DIR}")
target_sources(parser PRIVATE lexicals.cpp fileread.cpp lexer.cpp envparse.cpp)
