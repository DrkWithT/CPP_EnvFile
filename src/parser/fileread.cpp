/**
 * @file fileread.cpp
 * @author Derek Tan
 * @brief Implemention of file utilities.
 * @date 2023-12-13
 */

#include "parser/fileread.hpp"

/* Global Constexprs */

constexpr int32_t max_envfile_size = 4096;
// constexpr char* default_file_name_cstr = "./.env";

/* Helpers */

[[nodiscard]] char* read_whole_file(const char* file_pathname)
{
    std::ifstream file_reader {file_pathname};
    char* buffer_handle = nullptr;

    if (!file_reader.is_open())
    {
        return buffer_handle;
    }

    file_reader.seekg(0, file_reader.end);
    int32_t raw_file_size = file_reader.tellg();
    file_reader.seekg(0, file_reader.beg);

    if (raw_file_size < 0 || raw_file_size >= max_envfile_size)
    {
        file_reader.close();
        return buffer_handle;
    }

    buffer_handle = new char[raw_file_size + 1];

    if (buffer_handle != nullptr)
    {
        std::fill(buffer_handle, buffer_handle + raw_file_size, '\0');
        file_reader.readsome(buffer_handle, raw_file_size);
    }

    file_reader.close();

    return buffer_handle;
}
