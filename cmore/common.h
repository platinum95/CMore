#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define LOG_MODULE( level, module, log, ... ) printf( #level " (" #module "): " log "\n", ##__VA_ARGS__ );

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

typedef struct PomCommonNode PomCommonNode;

struct PomCommonNode{
    union{
        PomCommonNode * _Atomic aNext;
        PomCommonNode * next;
    };
    void *data;
};

#endif // COMMON_H
