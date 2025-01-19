#pragma once

#include <type_traits>
#include <string>
#include <map>
#include <variant>
// #include "models/exceptions.hpp"

namespace CPPEnvFile::Models
{
    namespace Helpers {
        template <typename T>
        using strip_type_of = std::remove_cv_t<std::remove_reference_t<T>>;
    }

    struct Nil {};

    using EntryValue = std::variant<Nil, std::string>;

    struct EnvFileEntry {
        EntryValue data;

        constexpr explicit operator bool() noexcept {
            return data.index() != 0;
        }

        friend constexpr bool operator==(const EnvFileEntry& lhs, const EnvFileEntry& rhs) noexcept {
            if (lhs.data.index() == 0 or rhs.data.index() == 0) {
                return false;
            }

            return std::get<1>(lhs.data) == std::get<1>(rhs.data);
        }
    };

    class Document
    {
    private:
        std::map<std::string, EnvFileEntry> m_entries;

    public:
        Document();

        [[nodiscard]] bool hasEntry(const std::string& key) const;
        const EnvFileEntry& viewEntry(const std::string& key) const;

        template <typename T> requires (std::same_as<Helpers::strip_type_of<T>, Nil> or std::same_as<Helpers::strip_type_of<T>, std::string>)
        void setEntry(const std::string& key, T&& item) {
            using BareT = Helpers::strip_type_of<T>;

            if constexpr (std::is_same_v<BareT, std::string>) {
                m_entries[key] = {
                    .data = item
                };
                return;
            }

            m_entries[key] = {Nil {}};
        }
    };
}
