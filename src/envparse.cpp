/**
 * @file envparse.cpp
 * @author Derek Tan
 * @brief Implements parser for environment secret files with simple .env syntax .
 * @todo Support booleans!
 * @date 2023-12-12 First draft.
 * @date 2023-02-07 Slight refactor, removed unneeded "this->".
 */

#include "parser/envparse.hpp"

/* Lexer Helpers */

[[nodiscard]] constexpr bool parser::utils::is_whitespace(char c)
{
    return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

[[nodiscard]] constexpr bool parser::utils::is_alpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' || c <= 'z') || c == '_';
}

[[nodiscard]] constexpr bool parser::utils::is_digit(char c)
{
    return c >= '0' && c <= '9';
}

/* Helper Impl. */

[[nodiscard]] bool parser::token_as_text(std::string& buffer_str, const char* source, const Token& token)
{
    if (token.length == 0)
    {
        return false;
    }

    buffer_str.clear();

    size_t begin = static_cast<size_t>(token.begin);
    size_t end = static_cast<size_t>(token.begin + token.length - 1U);

    for (size_t source_i = begin; source_i <= end; source_i++)
    {
        buffer_str += source[source_i];
    }

    return true;
}

/* Lexer Impl. */

parser::Lexer::Lexer(const char* source_ptr)
{
    if (!source_ptr)
    {
        throw std::invalid_argument("Invalid handle to source, found nullptr.");
    }

    this->source_ptr = source_ptr;
    source_length = std::strlen(source_ptr);
    source_pos = 0U;
    source_line = 1U;
}

constexpr bool parser::Lexer::has_ended() const
{
    return source_pos >= source_length;
}

constexpr uint32_t parser::Lexer::tell_line() const
{
    return source_line;
}

void parser::Lexer::skip_comment()
{
    char temp = '\0';

    while (source_pos < source_length)
    {
        temp = source_ptr[source_pos];

        if (temp == '\n')
        {
            source_line++;
            break;
        }

        source_pos++;
    }
}

void parser::Lexer::skip_whitespace()
{
    char temp = '\0';

    while (source_pos < source_length)
    {
        temp = source_ptr[source_pos];

        if (temp == '\n') source_line++;

        if (!parser::utils::is_whitespace(temp))
        {
            break;
        }

        source_pos++;
    }
}

parser::Token parser::Lexer::lex_identifier()
{
    char temp = '\0';
    uint32_t temp_start = source_pos;
    uint32_t temp_span = 0U;

    while (source_pos < source_length)
    {

        temp = source_ptr[source_pos];

        if (!parser::utils::is_alpha(temp))
        {
            break;
        }

        source_pos++;
        temp_span++;
    }

    return (Token){.begin = temp_start, .length = temp_span, .type = env_identifier};
}

parser::Token parser::Lexer::lex_single(parser::TokenType type)
{
    uint32_t temp_start = source_pos;
    uint32_t temp_span = 1U;

    source_pos++;

    return (Token){.begin = temp_start, .length = temp_span, .type = type};
}

parser::Token parser::Lexer::lex_number()
{
    char temp = '\0';
    uint32_t temp_start = source_pos;
    uint32_t temp_span = 1U;

    while (source_pos < source_length)
    {
        temp = source_ptr[source_pos];

        if (!parser::utils::is_digit(temp))
        {
            break;
        }

        source_pos++;
        temp_span++;
    }

    return (Token){.begin = temp_start, .length = temp_span, .type = env_number};
}

parser::Token parser::Lexer::lex_string()
{
    source_pos++; // do this to skip leading double quote!

    char temp = '\0';
    uint32_t temp_start = source_pos;
    uint32_t temp_span = 1U;

    while (source_pos < source_length)
    {
        temp = source_ptr[source_pos];

        if (temp == '\"')
        {
            source_pos++;
            break;
        }

        source_pos++;
        temp_span++;
    }

    return (Token){.begin = temp_start, .length = temp_span, .type = env_string};
}

parser::Token parser::Lexer::lex_next()
{
    char pre_temp = source_ptr[source_pos];

    if (pre_temp == '\0' || source_pos >= source_length)
    {
        return (Token){.begin = source_pos, .length = 0U, .type = env_eof};
    }

    // First... skip any leftover whitespace or comments to find the next token.
    if (parser::utils::is_whitespace(pre_temp))
        skip_whitespace();
    if (pre_temp == '#')
        skip_comment();

    // As soon as the next token is reached, it must be scanned.
    if (parser::utils::is_alpha(pre_temp))
        return lex_identifier();
    else if (pre_temp == '=')
        return lex_single(parser::env_binder);
    else if (parser::utils::is_digit(pre_temp))
        return lex_number();
    else if (pre_temp == '\"')
        return lex_string();

    // All valid types of tokens have been exhausted, so the unknown tokens are left behind.
    return (Token){.begin = source_pos, .length = 1U, .type = env_unknown};
}

/* Parse Impl. */

parser::Parser::Parser(const char* file_name_cstr, char* file_source_cstr)
: buffer_ptr {file_source_cstr}, lexer {buffer_ptr.get()}, file_name {file_name_cstr }
{}

[[nodiscard]] bool parser::Parser::parse_decl(collections::EnvFileDocument& doc)
{
    /// Follow grammar rule: IDENTIFIER BINDER (STRING | NUMBER)

    Token identifier_token = lexer.lex_next();

    if (identifier_token.type != env_identifier)
    {
        return false;
    }

    Token literal_token = lexer.lex_next();
    std::string temp_name {};
    std::string temp_literal {};
    
    if (!token_as_text(temp_name, buffer_ptr.get(), identifier_token) || !token_as_text(temp_literal, buffer_ptr.get(), literal_token))
    {
        return false;
    }

    if (literal_token.type == env_number)
    {
        doc.set_entry(temp_name, temp_literal, collections::env_lexical_type_number);
    }
    else if (literal_token.type == env_string)
    {
        doc.set_entry(temp_name, temp_literal, collections::env_lexical_type_string);
    }
    else
    {
        /// @note When control flow reaches here, I forbid syntax like bar = foo or bar = = for simplicity.
        return false;
    }

    return true;
}

[[nodiscard]] parser::ParseDump parser::Parser::parse_all(collections::EnvFileDocument& doc)
{
    /// @note This loop is empty because parse_decl returns a stopping false on an EOF or invalid .env declaration statement. Thus, no extra iterative work applies.
    while (parse_decl(doc));

    uint32_t final_line = lexer.tell_line();

    // Parse errors count iff not all field lines were successfully processed.
    if (final_line < 1U)
    {
        return (ParseDump){.line = final_line, .status = env_parse_bad_empty};
    }
    else if (!lexer.has_ended())
    {
        return (ParseDump){.line = final_line, .status = env_parse_bad_decl};
    }

    return (ParseDump){.line = final_line, .status = env_parse_ok};
}
