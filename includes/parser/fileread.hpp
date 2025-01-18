#pragma once

#include <fstream>
#include <optional>
#include <string>

namespace CPPEnvFile::Parser {
    class LineReader {
    public:
        LineReader(const std::string& file_path);

        explicit operator bool() const; 

        [[nodiscard]] std::optional<std::string> nextLine();

    private:
        std::ifstream m_reader;

    };
}