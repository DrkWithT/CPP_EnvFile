/**
 * @file test_myenv.cpp
 * @author Derek Tan
 * @brief Contains simple unit test for `parser::Parser` against `sample_04.txt`. Tests if the parsed object from the document has required fields.
 * @date 2023-12-14
 */

#include "interface/myenv.hpp"
#include <iostream>

constexpr const char* sample_04_file_path = "./testfiles/sample_04.txt"
"./testfiles/sample_04.txt";

int main()
{
    std::string test_file_path {sample_04_file_path};
    std::string field_name_1 {"foo"};
    std::string field_name_2 {"bar"};
    std::string field_name_3 {"baz"};
    collections::EnvFileDocument env_sample_4 {sample_04_file_path};

    parser::ParseDump status_info = parse_env(test_file_path, env_sample_4);

    if (status_info.status != parser::env_parse_ok)
    {
        std::cerr << __FILE__ << ": " << myenv_messages[status_info.status];
        return 1;
    }

    if (env_sample_4.get_entry(field_name_1).literal != "123")
    {
        std::cerr << __FILE__ << ": Invalid literal of field 1.\n";
        return 1;
    }

    if (env_sample_4.get_entry(field_name_2).literal != "test")
    {
        std::cerr << __FILE__ << ": Invalid literal of field 2.\n";
        return 1;
    }

    if (env_sample_4.get_entry(field_name_3).lexical_type != collections::env_lexical_type_nil)
    {
        std::cerr << __FILE__ << ": Incorrect type of field 3, expected nil.\n";
        return 1;
    }

    return 0;
}
