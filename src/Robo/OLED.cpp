#include <Arduino.h>
#include <Robo/OLED.h>
#include <Helpers.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

namespace Robo {
OLED::OLED(Brain& robo_brain, const int pin) :
  AbstractPart(robo_brain, "OLED"),
  m_pin(pin),
  m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
}

void OLED::setup()
{
  m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

}  // namespace Robo
