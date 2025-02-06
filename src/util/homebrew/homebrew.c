#include <stdio.h>
#include <stdlib.h>

#include "homebrew.h"
#include "../nofrendo/log.h"
#include "../nofrendo/osd.h"
#include "../nofrendo/nes/nes.h"

static bool option_showhomebrew = false;

/* Init homebrew for the first time */
void homebrew_init(void)
{
    option_showhomebrew = false;
    menu = NOFRENDO_MALLOC(sizeof(menu_t));
}

void homebrew_toggle(void)
{
    option_showhomebrew ^= true;
}