#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SD.h>

#include "hw_config.h"
extern "C"
{
#include "../nofrendo/log.h"
#include "../homebrew/homebrew.h"
}

extern "C" int homebrew_readlibrary(char *_library)
{
    char (*library)[MAX_ITEM_SIZE] = _library;
    int library_size = 0;
    FS filesystem = SD;

    File root = filesystem.open("/");

    if (root != NULL) 
    {
        File file = root.openNextFile();

        while (file != NULL)
        {
            if (!file.isDirectory())
            {
                char *filename = (char*) file.name();
                char *dot = strrchr(filename, '.');
                char *ext = strupr(dot);
                nofrendo_log_printf("Found file: %s\n", filename);
                if (ext && !strcmp(ext, ".NES"))
                {
                    nofrendo_log_printf("Is ROM\n");
                    int len = strlen(filename);
                    strcpy(library[library_size], filename);
                    library_size++;
                }
            }
            file = root.openNextFile();
        }
    }
    else
    {
        nofrendo_log_printf("Cant connect to SD card!!! Invalid state!\n");
    }

    return library_size;
}