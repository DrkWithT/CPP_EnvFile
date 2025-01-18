#include "parser/envparse.hpp"
#include "api/myenv.hpp"

namespace CPPEnvFile::Api {
    Models::Document parseEnv(const std::string& path) {
        Parser::Parser parser {path};

        return parser.parseGiven();        
    }
}