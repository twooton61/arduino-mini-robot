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
}

void Servo::reset() {
  m_servo.write(0);
}

void Servo::set_angle(const int angle)
{
  m_servo.write(angle);
}
}  // namespace Robo
