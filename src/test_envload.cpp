/**
 * @file test_envload.cpp
 * @author DrkWithT
 * @brief Implements simple test program for dotenv loading.
 * @date 2025-01-20
 * @copyright Copyright (c) 2025
 * 
 */

#include <string_view>
#include <format>
#include <iostream>
#include "api/myenv.hpp"

using OverwriteFlag = CPPEnvFile::Api::OverwriteOpt;

static constexpr std::string_view expected_foo_v = "hello";
static constexpr std::string_view expected_baz_v = "123";

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << std::format("usage: {} <case-number> <file-path>\n", argv[0]);
        return 1;
    }

    auto case_num = std::stoi(argv[1]);

    // For: testfiles/sample_03.txt
    if (case_num == 3) {
        CPPEnvFile::Api::loadEnv(argv[2], OverwriteFlag::no);

        std::string_view checked_foo {getenv("foo")};

        if (checked_foo != expected_foo_v) {
            std::cout << std::format("unexpected value of foo: expected \"{}\"\n", expected_foo_v);
            return 1;
        }

        std::string_view checked_baz {getenv("baz")};

        if (checked_baz != expected_baz_v) {
            std::cout << std::format("unexpected value of baz: expected \"{}\"\n", expected_baz_v);
            return 1;
        }
    }

    std::cout << "PASS\n";
}
