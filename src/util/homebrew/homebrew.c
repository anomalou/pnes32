#include <stdio.h>
#include <stdlib.h>

#include "homebrew.h"
#include "hw_config.h"
#include "../nofrendo/log.h"
#include "../nofrendo/osd.h"
#include "../nofrendo/nes/nes.h"
#include "../nofrendo/nofrendo.h"

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

    library_size = homebrew_readlibrary(*library);

    return 0;
}

void homebrew_setrom(const char *rom_name)
{
    if (rom_name == NULL)
    {
        rom_name = NOFRENDO_STRDUP("Launcher");
    }
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
    if (menu != NULL)
    {
        menu->selected_item = 0;
    }
}

bool homebrew_visible(void)
{
    return option_showhomebrew;
}

void homebrew_action_up(void)
{
    if (menu != NULL)
    {
        if (menu->selected_item == 0)
        {
            menu->selected_item = menu->menu_size - 1;
        }
        else
        {
            menu->selected_item--;
        }
    }
}

void homebrew_action_down(void)
{
    if (menu != NULL)
    {
        if (menu->selected_item == (menu->menu_size - 1))
        {
            menu->selected_item = 0;
        }
        else
        {
            menu->selected_item++;
        }
    }
}

void homebrew_action_left(void)
{

}

void homebrew_action_right(void)
{
}

void homebrew_action_select(void)
{
    char filename[MAX_ITEM_SIZE];
    sprintf(filename, "%s/%s", FSROOT, menu->menu_item[menu->selected_item]);

    nofrendo_log_printf("Inserting: %s\n", filename);

    option_showhomebrew = false;
    menu->selected_item = 0;
    main_insert(filename, system_nes);
}

void homebrew_action_back(void)
{
}
