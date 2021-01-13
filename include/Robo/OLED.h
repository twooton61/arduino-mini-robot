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
  OLED(Brain& robo_brain, const int pin);

  inline void setup() override;

  inline void reset();
private:
  const int m_pin = 0;
  Adafruit_SSD1306 m_display;
};
}  // namespace Robo

#endif  // ROBO_OLED_H_
