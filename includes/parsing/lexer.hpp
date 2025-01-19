#pragma once

#include "parsing/lexicals.hpp"
#include <cctype>

namespace CPPEnvFile::Parsing {
    namespace Helpers {
        [[nodiscard]] constexpr bool matchSpacing(char c) {
            return std::isspace(c);
        }

        [[nodiscard]] constexpr bool matchTexty(char c) {
            return std::isalnum(c) or std::ispunct(c);
        }
    }

    class Lexer {
    public:
        Lexer();

        void reset(const std::string& src);

        const std::string& viewSrc() const noexcept;

        [[nodiscard]] Token lexNext();

    private:
        bool atEOF() const noexcept;

        Token lexSingle(TokenType type);
        Token lexComment();
        Token lexSpacing();
        Token lexText();
        Token lexQuotedText();

        std::string m_src;
        unsigned int m_pos;
        unsigned int m_end;
        unsigned int m_line;
    };
}