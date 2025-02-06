#include <stdio.h>
#include <stdlib.h>

#include "homebrew.h"
#include "../nofrendo/log.h"
#include "../nofrendo/osd.h"
#include "../nofrendo/nes/nes.h"

char library[MAX_LIBRARY_SIZE][MAX_ITEM_SIZE];
int library_size = 0;

menu_t *menu = NULL;
static bool option_showhomebrew = false;

/* Init homebrew for the first time */
int homebrew_init(void)
{
    option_showhomebrew = false;
    menu = NOFRENDO_MALLOC(sizeof(menu_t));
    menu->menu_size = 0;
    menu->selected_item = 0;
    nofrendo_log_printf("Menu is %d\n", menu);

    library_size = homebrew_readlibrary(library);

    return 0;
}

void homebrew_setrom(const char *rom_name)
{
    nofrendo_log_printf("Set rom '%s' to homebrew\n", rom_name);
    int len = strlen(rom_name);
    strcpy(menu->title, rom_name);
    menu->title[len] = '\0';

    menu->menu_size = library_size;
    memcpy(menu->menu_item, library, sizeof(char) * MAX_MENU_SIZE * MAX_ITEM_SIZE);
}

menu_t *homebrew(void)
{
    return menu;
}

void homebrew_toggle(void)
{
    option_showhomebrew ^= true;
}

bool homebrew_visible(void)
{
    return option_showhomebrew;
}
