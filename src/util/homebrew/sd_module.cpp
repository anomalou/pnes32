#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SD.h>

#include "hw_config.h"
extern "C"
{
#include "../nofrendo/log.h"
#include "homebrew.h"
}

int homebrew_readlibrary(char library[MAX_LIBRARY_SIZE][MAX_ITEM_SIZE])
{
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
                    if (library_size < 255)
                    {
                        nofrendo_log_printf("Is ROM\n");
                        int len = strlen(filename);
                        strncpy(library[library_size], filename, len);
                        library[library_size][len] = '\0';
                        library_size++;
                    }
                    else
                    {
                        nofrendo_log_printf("Library full, skipping: %s\n", filename);
                    }
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