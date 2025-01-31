#pragma once

#include "parsing/fileread.hpp"
#include "parsing/lexicals.hpp"
#include "parsing/lexer.hpp"
#include "models/envdoc.hpp"

namespace CPPEnvFile::Parsing {
    class Parser {
    public:
        enum class TokenOpt {
            previous,
            current
        };

        struct ParseResult {
            std::string name;
            Models::EntryValue value;
        };

        Parser(const std::string& file_name);

        [[nodiscard]] Models::Document parseGiven();

    private:
        bool atLineEOF() const;

        const Token& viewPrevious() const;

        const Token& viewCurrent() const;

        bool match(TokenOpt opt, TokenType type) const;

        Token advance();

        void consume();

        void consume(TokenType type, const std::string& src_ref);

        ParseResult parseLine(const std::string& line_src_ref);

        LineReader m_line_reader;
        Lexer m_lexer;
        Token m_current;
        Token m_previous;
    };
}
