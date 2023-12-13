#ifndef ENVPARSE_HPP
#define ENVPARSE_HPP

#include "collections/envdoc.hpp"

namespace parser
{
    /// @brief utility functions for character types 
    namespace utils
    {
        [[nodiscard]] constexpr bool is_whitespace(char c);
        [[nodiscard]] constexpr bool is_alpha(char c);
        [[nodiscard]] constexpr bool is_digit(char c);
    }

    enum TokenType : uint8_t
    {
        env_comment,    // "#" (*)* LF
        env_whitespace, // (SP | TAB | CR | LF)+
        env_identifier, // (ALPHA | "_")+
        env_binder,     // "="
        env_number,     // ([0-9])+
        env_string,     // QUOTE (ALPHA | "_")* QUOTE,
        env_unknown,    // undefined token type
        env_eof         // when the parser stops past the last character
    };

    struct Token
    {
        uint32_t begin;
        uint32_t length;
        TokenType type;
    };

    enum ParseStatus : uint8_t
    {
        env_parse_ok,       // OK
        env_parse_bad_decl, // bad decl syntax
        env_parse_bad_empty // file empty
    };

    struct ParseDump
    {
        uint32_t line;
        ParseStatus status;
    };

    /**
     * @brief Helper function to stringify a token when its bounds are valid. Validity of bounds is when begin <= length.
     * 
     * @param buffer_str 
     * @param source 
     * @param token 
     * @return true If the token can be stringified.
     * @return false
     */
    [[nodiscard]] bool token_as_text(std::string& buffer_str, const char* source, const Token& token);

    class Lexer
    {
    private:
        /// @note This is only borrowed by Lexer... it must be externally freed!
        const char* source_ptr;
        uint32_t source_length;
        uint32_t source_pos;
        uint32_t source_line;

        void skip_comment();
        void skip_whitespace();
        Token lex_identifier();
        Token lex_single(TokenType type);
        Token lex_number();
        Token lex_string();

    public:
        Lexer() = default; /// @note I let the compiler do its job here. I won't actually use a default Lexer constructor since it needs loaded source text for now.
        Lexer(const char* source_ptr);

        constexpr bool has_ended() const;
        constexpr uint32_t tell_line() const;

        /**
         * @brief Lexes and yields the next token on each call until EOF.
         * 
         * @param source 
         * @return Token 
         */
        Token lex_next(const char* source);
    };

    class Parser
    {
    private:
        Lexer lexer;
        std::string file_name;
        std::unique_ptr<char> buffer_ptr;

        [[nodiscard]] bool parse_decl(collections::EnvFileDocument& doc);

    public:
        Parser(const char* file_name_cstr, char* file_source_cstr);
        ~Parser() = default;

        [[nodiscard]] ParseDump parse_all(collections::EnvFileDocument& doc);
    };
};

#endif