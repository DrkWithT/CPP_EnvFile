/**
 * @file envdoc.cpp
 * @author Derek Tan
 * @brief Implements my homemade envfile data structure.
 * @date 2023-12-12
 */

#include "collections/envdoc.hpp"

/* EnvFileEntry Impl. */

collections::EnvFileEntry::EnvFileEntry()
: name {}, literal {}
{
    lexical_type = collections::EnvLexicalType::env_lexical_type_nil;
}

collections::EnvFileEntry::EnvFileEntry(const std::string& name, const std::string& literal, collections::EnvLexicalType type)
: name {name}, literal {literal}
{
    lexical_type = type;
}

collections::EnvFileEntry::EnvFileEntry(const collections::EnvFileEntry& other)
{
    if (other == *this)
    {
        return;
    }

    name = other.name;
    literal = other.literal;
    lexical_type = other.lexical_type;
}

collections::EnvFileEntry& collections::EnvFileEntry::operator=(const collections::EnvFileEntry& other)
{
    if (other == *this)
    {
        return *this;
    }

    name = other.name;
    literal = other.literal;
    lexical_type = other.lexical_type;

    return *this;
}

bool collections::EnvFileEntry::operator==(const collections::EnvFileEntry& other) const
{
    return name == other.name
        && literal == other.literal
        && lexical_type == other.lexical_type;
}

/* EnvFileDocument Impl. */

collections::EnvFileDocument::EnvFileDocument(const char* name_cstr)
: entries {}, name {name_cstr}
{}

const std::map<std::string, collections::EnvFileEntry>& collections::EnvFileDocument::view_entries() const
{
    return entries;
}

const std::string& collections::EnvFileDocument::view_name() const
{
    return name;
}

[[nodiscard]] bool collections::EnvFileDocument::has_entry(const std::string& key) const
{
    return entries.find(key) != entries.end();
}

const collections::EnvFileEntry& collections::EnvFileDocument::get_entry(const std::string& key) const
{
    if (!this->has_entry(key))
    {
        throw std::invalid_argument("Entry does not exist!");
    }

    return entries.at(key);
}

void collections::EnvFileDocument::set_entry(const std::string& key, const std::string& literal, EnvLexicalType type)
{
    if (this->entries.find(key) == this->entries.end())
    {
        this->entries.insert({key, {key, literal, type}});
    }

    this->entries[key] = {key, literal, type};
}
