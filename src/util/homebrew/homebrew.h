#ifndef _HOMEBREW_H_
#define _HOMEBREW_H_

#include "../nofrendo/noftypes.h"

#define MAX_LIBRARY_SIZE 255
#define MAX_TITLE_SIZE 255
#define MAX_ITEM_SIZE 255
#define MAX_MENU_SIZE 255

typedef void (*menu_callback)(void *data);

typedef struct menu_item_s {
    char name[MAX_TITLE_SIZE];
    menu_callback select;
    menu_callback left;
    menu_callback right;
    void *additional_data;
} menu_item_t;

typedef struct menu_s {
    char title[MAX_TITLE_SIZE];
    int menu_size;
    int selected_item;
    menu_item_t menu_item[MAX_MENU_SIZE];
} menu_t;

extern int homebrew_init(void);
extern void homebrew_setrom(const char *rom_name);
extern int homebrew_readlibrary(char library[MAX_LIBRARY_SIZE][MAX_ITEM_SIZE]);

extern menu_t *homebrew(void);

extern void homebrew_toggle(void);
extern bool homebrew_visible(void);

extern void homebrew_action_up(void);
extern void homebrew_action_down(void);
extern void homebrew_action_left(void);
extern void homebrew_action_right(void);
extern void homebrew_action_select(void);
extern void homebrew_action_back(void);

#endif