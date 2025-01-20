#include "models/envdoc.hpp"
#include "models/exceptions.hpp"

namespace CPPEnvFile::Models {
    Document::Document()
    : m_entries {} {}

    const std::map<std::string, EnvFileEntry>& Document::viewEntryMap() const {
        return m_entries;
    }

    bool Document::hasEntry(const std::string& key) const {
        return m_entries.contains(key);
    }

    const EnvFileEntry& Document::viewEntry(const std::string& key) const {
        if (m_entries.contains(key)) {
            return m_entries.at(key);
        }

        throw EnvKeyError {key};
    }
}