/**
 * @file test_envparse.cpp
 * @author DrkWithT
 * @brief Implements test program for my envfile parser.
 * @date 2025-01-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <format>
#include <iostream>
#include "api/myenv.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << std::format("usage: {} <case-number> <file-path>\n", argv[0]);
        return 1;
    }

    auto case_num = std::stoi(argv[1]);

    if (case_num == 3) {
        auto doc = CPPEnvFile::Api::parseEnv(argv[2]);

        if (not doc.hasEntry("foo")) {
            return 1;
        }

        if (not doc.hasEntry("bar")) {
            return 1;
        }

        if (auto baz_value = std::get<std::string>(doc.viewEntry("baz").data); baz_value != "123") {
            return 1;
        }
    }
}