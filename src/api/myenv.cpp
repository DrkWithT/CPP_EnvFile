/**
 * @file myenv.cpp
 * @author Derek Tan
 * @brief Implements the wrapper functions around my dotenv file parser.
 * @version 0.1
 * @date 2023-12-14
 */

#include <iostream>
#include "interface/myenv.hpp"

const char* myenv_messages[] {
    "Parsed OK.",
    "Parse failed: found bad decl.",
    "Parse failed: found empty source.",
    "Parse failed: uncategorized error."
};

[[nodiscard]] parser::ParseDump parse_env(const std::string& file_path, collections::EnvFileDocument& document)
{
    char* loaded_contents = read_whole_file(file_path.c_str());
    parser::ParseDump parse_status = {.line = 0U, .status = parser::env_parse_bad_unknown};

    try
    {
        parser::Parser envparser {file_path.c_str(), loaded_contents}; // Throws on nullptr buffer to fail fast so I can minimize wrong code behavior.

        parse_status = envparser.parse_all(document);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return parse_status;
}
