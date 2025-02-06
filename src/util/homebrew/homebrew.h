#ifndef _HOMEBREW_H_
#define _HOMEBREW_H_

#include "../nofrendo/noftypes.h"

#define MAX_TITLE_SIZE 255
#define MAX_ITEM_SIZE 255
#define MAX_MENU_SIZE 16

typedef void (*menu_callback)(void *data);

typedef struct menu_s {
    char title[MAX_TITLE_SIZE];
    char menu_item[MAX_MENU_SIZE][MAX_ITEM_SIZE];
    menu_callback callback[MAX_MENU_SIZE];
    void (*menu_callback)(void *data);
    void *menu_additional_data;
} menu_t;

extern int homebrew_init(void);
extern void homebrew_setrom(const char *rom_name);

extern menu_t *homebrew(void);

extern void homebrew_toggle(void);
extern bool homebrew_visible(void);

#endif