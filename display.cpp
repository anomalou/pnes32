extern "C"
{
#include "src/util/nofrendo/nes/nes.h"
}

#include "hw_config.h"

#define ARDUINO_GFX

#ifdef ARDUINO_GFX
#include <Arduino_GFX_Library.h>
#else
#include <TFT_eSPI.h>
#endif

// #include <LovyanGFX.hpp>

/* M5Stack */
// #if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)

// #define TFT_BRIGHTNESS 255 /* 0 - 255 */
// #define TFT_BL 32
// Arduino_DataBus *bus = new Arduino_ESP32SPI(27 /* DC */, 14 /* CS */, SCK, MOSI, MISO);
// Arduino_ILI9342 *gfx = new Arduino_ILI9342(bus, 33 /* RST */, 1 /* rotation */);

/* Odroid-Go */
// #elif defined(ARDUINO_ODROID_ESP32)

// #define TFT_BRIGHTNESS 191 /* 0 - 255 */
// #define TFT_BL 14
// Arduino_DataBus *bus = new Arduino_ESP32SPI(21 /* DC */, 5 /* CS */, SCK, MOSI, MISO);
// Arduino_ILI9341 *gfx = new Arduino_ILI9341(bus, -1 /* RST */, 3 /* rotation */);

/* TTGO T-Watch */
// #elif defined(ARDUINO_T) || defined(ARDUINO_TWATCH_BASE) || defined(ARDUINO_TWATCH_2020_V1) || defined(ARDUINO_TWATCH_2020_V2) // TTGO T-Watch

// #define TFT_BRIGHTNESS 255 /* 0 - 255 */
// #define TFT_BL 12
// Arduino_DataBus *bus = new Arduino_ESP32SPI(27 /* DC */, 5 /* CS */, 18 /* SCK */, 19 /* MOSI */, -1 /* MISO */);
// Arduino_ST7789 *gfx = new Arduino_ST7789(bus, -1 /* RST */, 1 /* rotation */, true /* IPS */, 240, 240, 0, 80);

/* custom hardware */
// #else

// #define TFT_BRIGHTNESS 128 /* 0 - 255 */

/* HX8357B */
// #define TFT_BL 27
// Arduino_DataBus *bus = new Arduino_ESP32SPI(-1 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */);
// Arduino_TFT *gfx = new Arduino_HX8357B(bus, 33, 3 /* rotation */, true /* IPS */);

/* ST7789 ODROID Compatible pin connection */
// #define TFT_BL 14
// Arduino_DataBus *bus = new Arduino_ESP32SPI(4 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, 19 /* MISO */);
// Arduino_ST7789 *gfx = new Arduino_ST7789(bus, 22 /* RST */, 1 /* rotation */, true /* IPS */, 240, 240);

/* ST7796 on breadboard */
// #define TFT_BL 32
// Arduino_DataBus *bus = new Arduino_ESP32SPI(32 /* DC */, -1 /* CS */, 25 /* SCK */, 33 /* MOSI */, -1 /* MISO */);
// Arduino_TFT *gfx = new Arduino_ST7796(bus, -1 /* RST */, 1 /* rotation */);

/* ST7796 on LCDKit */
// #define TFT_BL 23
// Arduino_DataBus *bus = new Arduino_ESP32SPI(19 /* DC */, 5 /* CS */, 22 /* SCK */, 21 /* MOSI */, -1 /* MISO */);
// Arduino_ST7796 *gfx = new Arduino_ST7796(bus, 18, 1 /* rotation */);

// #endif /* custom hardware */

#define TFT_BRIGHTNESS 128 /* 0 - 255 */

#ifdef ARDUINO_GFX
// Arduino_GFX
Arduino_DataBus *bus = new Arduino_ESP32SPI(9 /* DC */, 17 /* CS */, 12 /* SCK */, 11 /* MOSI */, 13 /* MISO */);
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, 8 /* RST */, 3 /* rotation */, false /* IPS */, SCREEN_WIDTH, SCREEN_HEIGHT);
#else
TFT_eSPI gfx = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

static int16_t w, h, frame_x, frame_y, frame_x_offset, frame_width, frame_height, frame_line_pixels;
extern int16_t bg_color;
extern uint16_t myPalette[];

extern void display_begin()
{
#ifdef ARDUINO_GFX
    gfx->begin(80000000);
    bg_color = gfx->color565(24, 28, 24); // DARK DARK GREY
    gfx->fillScreen(bg_color);
#else
    gfx.init();
    gfx.setRotation(1);
    gfx.setSwapBytes(true);
#endif

#ifdef TFT_BL
    // turn display backlight on
    ledcSetup(1, 12000, 8);       // 12 kHz PWM, 8-bit resolution
    ledcAttachPin(TFT_BL, 1);     // assign TFT_BL pin to channel 1
    ledcWrite(1, TFT_BRIGHTNESS); // brightness 0 - 255
#endif
}

extern "C" void display_init()
{
#ifdef ARDUINO_GFX
    w = gfx->width();
    h = gfx->height();
#else
    w = gfx.width();
    h = gfx.height();
#endif

    nofrendo_log_printf("Screen size: %dx%d\n", w, h);

    if (w < 480) // assume only 240x240 or 320x240
    {
        if (w > NES_SCREEN_WIDTH)
        {
            frame_x = (w - NES_SCREEN_WIDTH) / 2;
            frame_x_offset = 0;
            frame_width = NES_SCREEN_WIDTH;
            frame_height = NES_SCREEN_HEIGHT;
            frame_line_pixels = frame_width;
        }
        else
        {
            frame_x = 0;
            frame_x_offset = (NES_SCREEN_WIDTH - w) / 2;
            frame_width = w;
            frame_height = NES_SCREEN_HEIGHT;
            frame_line_pixels = frame_width;
        }

#ifdef ARDUINO_GFX
        frame_y = (gfx->height() - NES_SCREEN_HEIGHT) / 2;
#else
        frame_y = (gfx.height() - NES_SCREEN_HEIGHT) / 2;
#endif

    }
    else // assume 480x320
    {
        frame_x = 0;
        frame_y = 0;
        frame_x_offset = 8;
        frame_width = w;
        frame_height = h;
        frame_line_pixels = frame_width / 2;
    }
}

extern "C" void display_write_frame(const uint8_t *data[])
{
#ifdef ARDUINO_GFX
    gfx->startWrite();
#else
    gfx.startWrite();
#endif
    if (w < 480)
    {
#ifdef ARDUINO_GFX
        gfx->writeAddrWindow(frame_x, frame_y, frame_width, frame_height);
        for (int32_t i = 0; i < NES_SCREEN_HEIGHT; i++)
        {
            gfx->writeIndexedPixels((uint8_t *)(data[i] + frame_x_offset), myPalette, frame_line_pixels);
        }
#else
        for (int32_t i = 0; i < NES_SCREEN_HEIGHT; i++)
        {
            gfx.setAddrWindow(frame_x, i, frame_width, 1);
            gfx.pushPixels((void *)(data[i] + frame_x_offset), frame_line_pixels);
        }
#endif
    }
#ifdef ARDUINO_GFX
    else
    {

        /* ST7796 480 x 320 resolution */

        /* Option 1:
         * crop 256 x 240 to 240 x 214
         * then scale up width x 2 and scale up height x 1.5
         * repeat a line for every 2 lines
         */
        // gfx->writeAddrWindow(frame_x, frame_y, frame_width, frame_height);
        // for (int16_t i = 10; i < (10 + 214); i++)
        // {
        //     gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     if ((i % 2) == 1)
        //     {
        //         gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     }
        // }

        /* Option 2:
         * crop 256 x 240 to 240 x 214
         * then scale up width x 2 and scale up height x 1.5
         * simply blank a line for every 2 lines
         */
        int16_t y = 0;
        for (int16_t i = 10; i < (10 + 214); i++)
        {
            gfx->writeAddrWindow(frame_x, y++, frame_width, 1);
            gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
            if ((i % 2) == 1)
            {
                y++; // blank line
            }
        }

        /* Option 3:
         * crop 256 x 240 to 240 x 240
         * then scale up width x 2 and scale up height x 1.33
         * repeat a line for every 3 lines
         */
        // gfx->writeAddrWindow(frame_x, frame_y, frame_width, frame_height);
        // for (int16_t i = 0; i < 240; i++)
        // {
        //     gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     if ((i % 3) == 1)
        //     {
        //         gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     }
        // }

        /* Option 4:
         * crop 256 x 240 to 240 x 240
         * then scale up width x 2 and scale up height x 1.33
         * simply blank a line for every 3 lines
         */
        // int16_t y = 0;
        // for (int16_t i = 0; i < 240; i++)
        // {
        //     gfx->writeAddrWindow(frame_x, y++, frame_width, 1);
        //     gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     if ((i % 3) == 1)
        //     {
        //         y++; // blank line
        //     }
        // }
    }
#endif

#ifdef ARDUINO_GFX
    gfx->endWrite();
#else
    gfx.endWrite();
#endif
    
}

extern "C" void display_clear()
{
#ifdef ARDUINO_GFX
    gfx->fillScreen(bg_color);
#else
    gfx.fillScreen(TFT_BLACK);
#endif
}
