#include <Arduino.h>
#include <Robo/Servo.h>
#include <Helpers.h>

namespace Robo {
Servo::Servo(Brain& robo_brain, const int pin, const int flat_angle, const int base_angle, const int tippy_toe_angle) :
  AbstractPart(robo_brain, String("Servo on pin ") + String(pin)),
  m_pin(pin),
  m_flat_angle(flat_angle),
  m_base_angle(base_angle),
  m_tippy_toe_angle(tippy_toe_angle)
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

  Serial.print("writing: ");
  Serial.println(angle);

  m_servo.write(angle);
}

void Servo::flat()
{
  set_angle(m_flat_angle);
}

void Servo::base()
{
  set_angle(m_base_angle);
}

void Servo::tippy_toe()
{
  set_angle(m_tippy_toe_angle);
}

void Servo::straight()
{
  tippy_toe();
}
}  // namespace Robo
