#include <stdio.h>
#include <stdlib.h>

#include "homebrew.h"
#include "src/util/nofrendo/log.h"
#include "src/util/nofrendo/osd.h"
#include "nes/nes.h"

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