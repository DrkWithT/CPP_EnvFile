#ifndef FILEREAD_HPP
#define FILEREAD_HPP

#include <algorithm>
#include <fstream>

/**
 * @brief Attempts to read the entire contents of an envfile into a string in memory.
 * @note Maximum file size supported by default is `4096`.
 * 
 * @param file_pathname 
 * @return char* 
 */
[[nodiscard]] char* read_whole_file(const char* file_pathname);

#endif