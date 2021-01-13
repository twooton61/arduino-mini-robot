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
  Servo(Brain& robo_brain, const int pin);

  void setup() override;

  void reset();
private:
  const int m_pin = 0;
  ::Servo m_servo;
};
}  // namespace Robo

#endif  // ROBO_SERVO_H_
