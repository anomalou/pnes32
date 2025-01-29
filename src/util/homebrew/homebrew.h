#ifndef _HOMEBREW_H_
#define _HOMEBREW_H_

#include "src/util/nofrendo/noftypes.h"

typedef struct menu_s {
    char* lable;
} menu_t;

extern void homebrew_init(void);
extern void homebrew_loop(void);

extern void homebrew_close(void);
extern void homebrew_open(void);

#endif