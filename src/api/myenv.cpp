#include "parsing/envparse.hpp"
#include "api/myenv.hpp"

namespace CPPEnvFile::Api {
    Models::Document parseEnv(const std::string& path) {
        Parsing::Parser parser {path};

        return parser.parseGiven();        
    }
}