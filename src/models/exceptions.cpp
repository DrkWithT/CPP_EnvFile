#include <format>
#include "parser/lexicals.hpp"
#include "models/exceptions.hpp"

namespace CPPEnvFile::Models {
    EnvParseError::EnvParseError(const Parser::Token& suspect, const std::string& src, const std::string& msg)
    : m_full_msg {std::format("Parsed suspect token: '{}', {}\n", Parser::stringify(suspect, src), msg)} {}

    const char* EnvParseError::what() const noexcept {
        return m_full_msg.c_str();
    }

    EnvKeyError::EnvKeyError(const std::string& suspect_key)
    : m_full_msg {std::format("Invalid access of key '{}'", suspect_key)} {}

    const char* EnvKeyError::what() const noexcept {
        return m_full_msg.c_str();
    }
}