#include <string>
#include <memory>
#include <vector>
#include <stdarg.h>
#include "models.hpp"

namespace tools
{
    // returns item type as a character for use in switch cases
    char itemType(const std::shared_ptr<Item> &item)
    {
        if (auto armor = std::dynamic_pointer_cast<Armor>(item))
        {
            return 'a'; // armor detected
        }
        else if (auto weapon = std::dynamic_pointer_cast<Weapon>(item))
        {
            return 'w'; // weapon detected
        }
        else if (auto ranged = std::dynamic_pointer_cast<Ranged>(item))
        {
            return 'r'; // ranged weapon detected
        }
        else
        {
            return 'z';
        }
    }

    /* Prints message suitable for debug purposes,
use '__FILE__' for file argument.
use '__LINE__' for line argument.
Additional arguments must be string, you must add 'NULL' at the end of the parameters. (tools.h) */
    void pr_debug(char *message, char *file, int line, ...)
    {
        va_list args;
        va_start(args, line);

        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "***DEBUG*** (%s ln:%d) %s", file, line, message);

        const char *arg;
        while ((arg = va_arg(args, const char *)) != NULL)
        {
            strncat(buffer, " ", sizeof(buffer) - strlen(buffer) - 1);
            strncat(buffer, arg, sizeof(buffer) - strlen(buffer) - 1);
        }

        va_end(args);

        printf("\x1b[45m\x1b[30m%s\x1b[0m\n", buffer);
    }
}