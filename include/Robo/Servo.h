#ifndef ROBO_SERVO_H_
#define ROBO_SERVO_H_

#include <Arduino.h>
#include <Helpers.h>
#include <Servo.h>
#include <Robo/AbstractPart.h>

namespace Robo {
class Servo : public AbstractPart
{
  DISABLE_COPY_AND_ASSIGN(Servo)
public:
  Servo(Brain& robo_brain, const int pin, const int flat_angle, const int base_angle, const int tippy_toe_angle);

  void setup() override;
  void reset();
  void set_angle(const int angle);

  void flat();

  void base();

  void tippy_toe();
  void straight();
private:
  const int m_pin = 0;
  ::Servo m_servo;
  const int m_flat_angle;
  const int m_base_angle;
  const int m_tippy_toe_angle;
};
}  // namespace Robo

#endif  // ROBO_SERVO_H_
