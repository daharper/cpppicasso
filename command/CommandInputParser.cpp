#include "CommandInputParser.h"
#include "../Utils.h"

std::optional<CommandObject> CommandInputParser::parse(const std::string& input) {
    auto text = String::trim(input);

    if (input.empty()) return std::nullopt;

    CommandObject command;

    command.text = text;
    command.name = static_cast<char>(std::toupper(text[0]));

    if (text.size() == 1) return command;

    text = String::trim(text.erase(0, 1));

    auto inQuotes{ false };
    constexpr auto quote{ '"' };

    std::string buffer;

    for (const auto ch : text) {
        if (ch == quote) {
            if (!buffer.empty()) {
                command.params.emplace_back(buffer);
                buffer.clear();
            }

            inQuotes = !inQuotes;
            continue;
        }

        if (ch == ' ' && !inQuotes) {
            command.params.emplace_back(buffer);
            buffer.clear();
            continue;
        }

        buffer += ch;
    }

    if (!buffer.empty()) {
        command.params.emplace_back(buffer);
    }

    return command;
}