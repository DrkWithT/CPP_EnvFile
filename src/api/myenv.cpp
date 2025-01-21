#include <cstdlib>
#include <stdexcept>
#include "parsing/envparse.hpp"
#include "api/myenv.hpp"

namespace CPPEnvFile::Api {
    bool Utils::loadToEnv(const Models::Document &doc, OverwriteOpt overwrite) {
        const auto overwrite_flag = static_cast<int>(overwrite);

        for (const auto& property : doc.viewEntryMap()) {
            auto property_value = std::get<1>(property.second.data);

            if (setenv(property.first.c_str(), property_value.c_str(), overwrite_flag) == -1) {
                return false;
            }
        }

        return true;
    }

    Models::Document parseEnv(const std::string& path) {
        Parsing::Parser parser {path};

        return parser.parseGiven();        
    }

    void loadEnv(const std::string &path, OverwriteOpt overwrite) {
        auto env_document = parseEnv(path);

        if (not Utils::loadToEnv(env_document, overwrite)) {
            throw std::logic_error {"Failed to parse dotenv file."};
        }
    }
}