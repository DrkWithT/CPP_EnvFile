#include <utility>
#include "parser/envparse.hpp"
#include "models/exceptions.hpp"
#include "parser/lexicals.hpp"

namespace CPPEnvFile::Parser {
    Parser::Parser(const std::string& path)
    : m_line_reader {path}, m_lexer {}, m_current {0U, 0U, 1U, TokenType::eof}, m_previous {0U, 0U, 1U, TokenType::eof} {}

    Models::Document Parser::parseGiven() {
        Models::Document doc;
        
        while (true) {
            auto line_opt = m_line_reader.nextLine();

            if (not line_opt) {
                break;
            }

            auto temp_line = line_opt.value();

            m_lexer.reset(temp_line);
            m_previous = {0U, 0U, 1U, TokenType::eof};
            m_current = {0U, 0U, 1U, TokenType::eof};
            consume();

            auto [secret_name, secret_value] = parseLine(temp_line);

            doc.setEntry(secret_name, std::get<1>(secret_value));
        }

        return doc;
    }

    bool Parser::atLineEOF() const {
        return match(TokenOpt::current, TokenType::eof);
    }

    const Token& Parser::viewPrevious() const {
        return m_previous;
    }

    const Token& Parser::viewCurrent() const {
        return m_current;
    }

    bool Parser::match(TokenOpt opt, TokenType type) const {
        return (opt == TokenOpt::current)
            ? m_current.type == type
            : m_previous.type == type;
    }

    Token Parser::advance() {
        Token temp;

        while (true) {
            temp = m_lexer.lexNext();

            if (temp.type == TokenType::spacing or temp.type == TokenType::comment) {
                continue;
            }

            break;
        }

        return temp;
    }

    void Parser::consume() {
        m_previous = m_current;
        m_current = advance();
    }

    void Parser::consume(TokenType type, const std::string& src_ref) {
        if (match(TokenOpt::current, type)) {
            consume();
            return;
        }

        throw Models::EnvParseError {m_current, src_ref, "token was unexpected"};
    }

    Parser::ParseResult Parser::parseLine(const std::string& line_src_ref) {
        consume(TokenType::texty, line_src_ref);

        auto pname = stringify(viewPrevious(), line_src_ref);

        consume(TokenType::op_bind, line_src_ref);
        consume(TokenType::texty, line_src_ref);

        auto pliteral = stringify(viewPrevious(), line_src_ref);

        return {
            .name = std::move(pname),
            .value = std::move(pliteral)
        };
    }
}