#include <Robo/OLED.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
namespace Robo {
OLED::OLED(Brain& robo_brain) :
  AbstractPart(robo_brain, "OLED"),
  m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
}

void OLED::setup()
{
  m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  m_display.display();
}

void OLED::print(const char* message)
{

  m_display.setTextSize(2);
  m_display.setTextColor(WHITE);
  m_display.setCursor(0, 0);
  m_display.println(message);
  m_display.display();
}

void OLED::drawDot(const int x, const int y)
{
  m_display.drawPixel(x, y, SSD1306_WHITE);
  m_display.display();
}

void OLED::clear()
{
  m_display.clearDisplay();
}

}  // namespace Robo
