#ifndef _HOMEBREW_H_
#define _HOMEBREW_H_

#include "../nofrendo/noftypes.h"

#define MAX_TITLE_SIZE 255
#define MAX_ITEM_SIZE 255
#define MAX_MENU_SIZE 16

typedef struct menu_s {
    char title[MAX_TITLE_SIZE];
    char menu_item[MAX_MENU_SIZE][MAX_ITEM_SIZE];
    void (*menu_callback)(void *data);
    void *menu_additional_data;
} menu_t;

static menu_t *menu = NULL;

extern void homebrew_init(void);

extern void homebrew_toggle(void);

#endif