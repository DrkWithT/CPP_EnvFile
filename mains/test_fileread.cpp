/**
 * @file test_fileread.cpp
 * @author Derek Tan
 * @brief Implements simple unit test for file reading utilities.
 * @date 2023-12-13
 */

#include "parser/fileread.hpp"
#include <memory>
#include <iostream>

int main ()
{
    char* ghost_content = read_whole_file("./testfiles/ghost.txt");
    char* empty_content = read_whole_file("./testfiles/sample_00.txt");
    char* filled_content = read_whole_file("./testfiles/sample_01.txt");

    std::unique_ptr<char> ghost_uptr {ghost_content};
    std::unique_ptr<char> empty_uptr {empty_content};
    std::unique_ptr<char> filled_uptr {filled_content};

    if (ghost_uptr)
    {
        std::cerr << __FILE__ << ": Expected nullptr from non-existent file, found non-nullptr.\n";
        return 1;
    }

    if (empty_uptr)
    {
        std::cerr << __FILE__ << ": Expected nullptr from empty source, got non-nullptr.\n";
        return 1;
    }

    if (!filled_uptr)
    {
        std::cerr << __FILE__ << ": Expected non-nullptr from filled file, found nullptr.\n";
        return 1;
    }

    return 0;
}
