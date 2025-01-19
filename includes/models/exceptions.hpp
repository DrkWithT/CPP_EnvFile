#pragma once

#include <exception>
#include <string>
#include "parsing/lexicals.hpp"

namespace CPPEnvFile::Parser {
    struct Token;
}

namespace CPPEnvFile::Models {
    class EnvParseError : public std::exception {
    public:
        EnvParseError(const Parsing::Token& suspect, const std::string& src, const std::string& msg);

        const char* what() const noexcept;

    private:
        std::string m_full_msg;
    };

    class EnvKeyError {
    public:
        EnvKeyError(const std::string& suspect_key);

        const char* what() const noexcept;

    private:
        std::string m_full_msg;
    };
}