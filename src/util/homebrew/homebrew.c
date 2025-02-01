#include <stdio.h>
#include <stdlib.h>

#include "homebrew.h"
#include "src/util/nofrendo/log.h"
#include "src/util/nofrendo/osd.h"

static struct 
{
    bool poweroff;
} homebrew;

/* Init homebrew for the first time */
void homebrew_init(void)
{
    homebrew.poweroff = false;
}

menu_t *menu = NULL;

void homebrew_loop(void) 
{
    menu = NOFRENDO_MALLOC(sizeof(*menu));
    menu->lable = "HOMEBREW :3";

    nofrendo_log_printf("Homebrew started\n");

    while (!homebrew.poweroff) 
    {
        
    }
}

void homebrew_close(void)
{
    homebrew.poweroff = true;

    nofrendo_log_printf("Homebrew closing\n");
} 

void homebrew_open(void)
{
    homebrew.poweroff = true;

    nofrendo_log_printf("Homebrew opening\n");
}