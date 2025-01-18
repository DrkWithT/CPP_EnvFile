#include "parser/lexer.hpp"

namespace CPPEnvFile::Parser {
    Lexer::Lexer()
    : m_src {}, m_pos {0U}, m_end {0U}, m_line {1U} {}

    void Lexer::reset(const std::string& src) {
        m_src = src;
        m_pos = 0U;
        m_end = m_src.size();
        m_line = 1U;
    }

    const std::string& Lexer::viewSrc() const noexcept {
        return m_src;
    }

    [[nodiscard]] Token Lexer::lexNext() {
        if (atEOF()) {
            return {
                .begin = m_end,
                .length = 1U,
                .line = m_line,
                .type = TokenType::eof
            };
        }

        char current = m_src[m_pos];

        switch (current) {
        case '#':
            return lexComment();
        case '=':
            return lexSingle(TokenType::op_bind);
        case '\"':
            return lexQuotedText();
        }

        if (Helpers::matchSpacing(current)) {
            return lexSpacing();
        } else if (Helpers::matchTexty(current)) {
            return lexText();
        }

        return lexSingle(TokenType::bad);
    }

    bool Lexer::atEOF() const noexcept {
        return m_pos >= m_end;
    }

    Token Lexer::lexSingle(TokenType type) {
        return {
            .begin = m_pos++,
            .length = 1U,
            .line = m_line,
            .type = type
        };
    }

    Token Lexer::lexSpacing() {
        auto begin = m_pos;
        auto length = 0U;

        while (not atEOF()) {
            auto c = m_src[m_pos];

            if (not Helpers::matchSpacing(c)) {
                break;
            }

            if (c == '\n') {
                m_line++;
            }

            m_pos++;
            length++;
        }

        return {
            begin,
            length,
            m_line,
            TokenType::spacing
        };
    }

    Token Lexer::lexText() {
        auto begin = m_pos;
        auto length = 0U;

        while (not atEOF()) {
            auto c = m_src[m_pos];

            if (not Helpers::matchTexty(c)) {
                break;
            }

            m_pos++;
            length++;
        }

        return {
            begin,
            length,
            m_line,
            TokenType::texty
        };
    }

    Token Lexer::lexQuotedText() {
        auto begin = ++m_pos;
        auto length = 0U;
        auto closed = false;

        while (not atEOF()) {
            auto c = m_src[m_pos];

            if (not Helpers::matchTexty(c) and c == '\"') {
                m_pos++;
                closed = true;
                break;
            }

            m_pos++;
            length++;
        }

        return {
            begin,
            length,
            m_line,
            (closed) ? TokenType::texty : TokenType::bad
        };
    }
}