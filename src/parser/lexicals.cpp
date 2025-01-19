#include "parsing/lexicals.hpp"

namespace CPPEnvFile::Parsing {
    std::string stringify(const Token &token, const std::string &source) {
        if (token.type == TokenType::spacing or token.type == TokenType::eof) {
            return "";
        }

        return source.substr(token.begin, token.length);
    }
}