/**
 * @file test_envdoc.cpp
 * @author Derek Tan
 * @brief Implements simple unit test program for `EnvFileDocument`.
 * @date 2023-12-12
 */

#include <iostream>

#include "collections/envdoc.hpp"

constexpr const char* demo_env_name = "example";

int main()
{
    collections::EnvFileDocument example_env {demo_env_name};
    collections::EnvFileEntry demo_entry_1 {"foo", "123", collections::EnvLexicalType::env_lexical_type_number};
    std::string demo_name_1 {"foo"};
    std::string demo_literal_1 {"123"};

    if (example_env.view_name() != demo_env_name)
    {
        std::cerr << __FILE__ << ": Invalid name on initialization!\n";
        return 1;
    }

    try
    {
        // This also tests has_entry(...) internally, so this case is fine.
        example_env.get_entry(demo_name_1);
        return 1; // This is here to check if the call above unexpectedly did not throw.
    }
    catch (std::invalid_argument& e)
    {
        std::cout << __FILE__ << " [EnvFileDocument::get_entry]: threw invalid_argument for invalid key, OK!\n";
    }

    example_env.set_entry(demo_name_1, demo_literal_1, collections::EnvLexicalType::env_lexical_type_number);

    if (!(example_env.get_entry(demo_name_1) == demo_entry_1))
    {
        std::cerr << __FILE__ << ": Unexpected entry, value mismatch!\n";
        return 1;
    }

    if (example_env.view_entries().size() != 1)
    {
        std::cerr << __FILE__ << ": Unexpected size, expected 1!\n";
        return 1;
    }

    return 0;
}
