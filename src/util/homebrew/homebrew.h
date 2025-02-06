#ifndef _HOMEBREW_H_
#define _HOMEBREW_H_

#include "../nofrendo/noftypes.h"

#define MAX_LIBRARY_SIZE 255
#define MAX_TITLE_SIZE 255
#define MAX_ITEM_SIZE 255
#define MAX_MENU_SIZE 16

typedef void (*menu_callback)(void *data);

typedef struct menu_s {
    char title[MAX_TITLE_SIZE];
    char menu_item[MAX_MENU_SIZE][MAX_ITEM_SIZE];
    int menu_size;
    int selected_item;
    menu_callback callback[MAX_MENU_SIZE];
    void (*menu_callback)(void *data);
    void *menu_additional_data;
} menu_t;

extern int homebrew_init(void);
extern void homebrew_setrom(const char *rom_name);
extern int homebrew_readlibrary(char **library);

extern menu_t *homebrew(void);

extern void homebrew_toggle(void);
extern bool homebrew_visible(void);

#endif