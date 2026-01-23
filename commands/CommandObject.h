#ifndef CPPPICASSO_COMMAND_OBJECT_H
#define CPPPICASSO_COMMAND_OBJECT_H

#include <string>
#include <vector>

struct CommandObject {
    std::string text;
    std::string name;
    std::vector<std::string> params;
};

#endif //CPPPICASSO_COMMAND_OBJECT_H