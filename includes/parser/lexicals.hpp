#pragma once

#include <string>

namespace CPPEnvFile::Parser {
    enum class TokenType {
        spacing,
        comment,
        texty,
        op_bind,
        eof,
        bad
    };

    using TokenNum = unsigned int;

    struct Token {
        TokenNum begin;
        TokenNum length;
        TokenNum line;
        TokenType type;
    };

    [[nodiscard]] std::string stringify(const Token& token, const std::string& source);
}