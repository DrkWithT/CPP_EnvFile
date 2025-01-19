#pragma once

#include "models/envdoc.hpp"

namespace CPPEnvFile::Api {
    [[nodiscard]] Models::Document parseEnv(const std::string& path);
}
