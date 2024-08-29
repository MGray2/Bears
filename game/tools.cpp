#include <string>
#include <memory>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>

namespace tools
{
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