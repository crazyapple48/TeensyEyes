#pragma once

#include <ST7796_t3.h>
#include <array>

#include "Display.h"

typedef struct {
  int8_t cs;           // Chip select pin, or -1.
  int8_t dc;            // DC pin.
  int8_t mosi;          // MOSI pin.
  int8_t sck;           // SCK pin.
  int8_t rst;           // reset pin, or -1 to disable reset.
  uint8_t rotation;     // The rotation value for the display (0-3).
  bool mirror;          // Mirror the display in the X direction.
  bool useFrameBuffer;  // Whether to use frame buffering.
  bool asyncUpdates;    // Whether to update the screen asynchronously (for better performance).
} ST7796_Config;

class ST7796_Display : public Display<ST7796_Display> {
private:
  ST7796_t3* display;
  bool asyncUpdates;
  int displayNum;

#ifdef SHOW_FPS
  uint32_t framesDrawn{};
  uint32_t fps{};
  elapsedMillis elapsed{};
#endif

public:
  /// Creates a generic wrapper for a 240x240 ST7789 TFT display screen.
  /// \param config the screen's configuration.
  ST7796_Display(const ST7796_Config &config);

  virtual ~ST7796_Display();

  void drawPixel(int16_t x, int16_t y, uint16_t color565);

  void drawFastVLine(int16_t x, int16_t y, int16_t height, uint16_t color565);

  void drawText(int16_t x, int16_t y, char *text);

  void update();

  bool isAvailable() const;
};
