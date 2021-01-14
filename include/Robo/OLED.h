#ifndef ROBO_OLED_H_
#define ROBO_OLED_H_

#include <Arduino.h>
#include <Helpers.h>
#include <Robo/AbstractPart.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

namespace Robo {
class OLED : public AbstractPart
{
  DISABLE_COPY_AND_ASSIGN(OLED)
public:
  explicit OLED(Brain& robo_brain);

  void setup() override;
  void print(const char* message);
  void clear();
private:
  Adafruit_SSD1306 m_display;
};
}  // namespace Robo

#endif  // ROBO_OLED_H_
