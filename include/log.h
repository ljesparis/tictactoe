#ifndef _LOG_H_
#define _LOG_H_

#include <stdlib.h>
#include <stdio.h>

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

#define DEBUG(msg)  \
    if (DEBUG_MODE) \
    printf("\033[94m[DEBUG] %s\033[0m\n", msg)

#define ERROR(msg)                                  \
    {                                               \
        printf("\033[91m[ERROR] %s\033[0m\n", msg); \
        exit(1);                                    \
    }

#define ASSERT(cond, msg) \
    if (cond)             \
    {                     \
        DEBUG(msg);       \
    }

#endif // _LOG_H_