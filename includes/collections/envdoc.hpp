#ifndef ENVDOC_HPP
#define ENVDOC_HPP

#include <string>
#include <map>
#include <exception>

namespace collections
{
    enum EnvLexicalType : uint8_t
    {
        env_lexical_type_number,
        env_lexical_type_string,
        env_lexical_type_nil
    };

    struct EnvFileEntry
    {
        std::string name;
        std::string literal;
        EnvLexicalType lexical_type;

        EnvFileEntry();
        ~EnvFileEntry() = default;
        EnvFileEntry(const std::string& name, const std::string& literal, EnvLexicalType type);
        EnvFileEntry(const EnvFileEntry& other);
        EnvFileEntry& operator=(const EnvFileEntry& other);

        bool operator==(const EnvFileEntry& other) const;
    };

    class EnvFileDocument
    {
    private:
        std::map<std::string, EnvFileEntry> entries;
        std::string name;
    public:
        EnvFileDocument(const char* name_cstr);

        const std::map<std::string, EnvFileEntry>& view_entries() const;
        const std::string& view_name() const;

        [[nodiscard]] bool has_entry(const std::string& key) const;
        const EnvFileEntry& get_entry(const std::string& key) const;
        
        /**
         * @brief Update the entry for the specified name. This should only be used within the parser to build the entry collection for this ADT.
         * 
         * @param key 
         * @param literal 
         * @param type 
         */
        void set_entry(const std::string& key, const std::string& literal, EnvLexicalType type);
    };
}

#endif