#include <Arduino.h>
#include <Robo/Servo.h>
#include <Helpers.h>

namespace Robo {
Servo::Servo(Brain& robo_brain, const int pin) :
  AbstractPart(robo_brain, String("Servo on pin ") + String(pin)),
  m_pin(pin)
{
}

void Servo::setup()
{
  m_servo.attach(m_pin);

  delay(100);
}

void Servo::reset() {
  set_angle(0);
}

void Servo::set_angle(const int angle)
{
  if (m_servo.read() == angle) {
    return;
  }

  m_servo.write(angle);
}
}  // namespace Robo
