#ifndef CPPPICASSO_INPUT_PARSER_H
#define CPPPICASSO_INPUT_PARSER_H

#include <optional>

#include "CommandObject.h"

class CommandInputParser {
public:
    static std::optional<CommandObject> parse(const std::string& input);
};

#endif //CPPPICASSO_INPUT_PARSER_H