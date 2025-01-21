#pragma once

#include "models/envdoc.hpp"

namespace CPPEnvFile::Api {
    enum class OverwriteOpt {
        no,
        yes
    };

    namespace Utils {
        [[nodiscard]] bool loadToEnv(const Models::Document& doc, OverwriteOpt overwrite);
    }

    [[nodiscard]] Models::Document parseEnv(const std::string& path);

    void loadEnv(const std::string& path, OverwriteOpt overwrite);
}
