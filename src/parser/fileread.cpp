#include "parsing/fileread.hpp"

namespace CPPEnvFile::Parsing {
    LineReader::LineReader(const std::string& file_path)
    : m_reader {file_path} {}

    LineReader::operator bool() const {
        return m_reader.is_open();
    }

    std::optional<std::string> LineReader::nextLine() {
        std::string temp;

        auto at_end = std::getline(m_reader, temp).eof();
        auto had_error = m_reader.bad();

        if (at_end or had_error) {
            return {};
        }

        return temp;
    }
}