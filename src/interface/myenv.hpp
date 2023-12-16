#ifndef MYENV_HPP
#define MYENV_HPP

#include "parser/envparse.hpp"
#include "parser/fileread.hpp"

/// @brief Corresponding status messages for `parser::ParseDump::status`
extern const char* myenv_messages[4U];

/**
 * @brief Attempts to parse a file with simple dotenv syntax. Succeeds only when the file is fully read and all fields are successfully parsed.
 * 
 * @param file_path A string representing an envfile path.
 * @param document
 * @return parser::ParseDump A struct denoting the error code at a certain line.
 */
[[nodiscard]] parser::ParseDump parse_env(const std::string& file_path, collections::EnvFileDocument& document);

#endif