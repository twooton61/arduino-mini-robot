/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <Robo/Brain.h>
#include <Robo/Servo.h>
#include <Robo/OLED.h>

Robo::Brain robo_brain;


Robo::Servo robo_servo_front_left(robo_brain, DIGITAL_IO_PIN(12));
Robo::Servo robo_servo_front_right(robo_brain, DIGITAL_IO_PIN(11));
Robo::Servo robo_servo_back_left(robo_brain, DIGITAL_IO_PIN(10));
Robo::Servo robo_servo_back_right(robo_brain, DIGITAL_IO_PIN(9));

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  pinMode(LED_BUILTIN , OUTPUT);

  robo_brain.setup();
}
namespace spider
{
  inline void base();
  inline void sploot();
}

void loop()
{
  spider::base();

  delay(1000);

  spider::sploot();

  delay(1000);
}

namespace spider
{
inline void base()
{
  robo_servo_front_right.set_angle(180);
  robo_servo_front_left.set_angle(0);

  robo_servo_back_left.set_angle(180);
  robo_servo_back_right.set_angle(0);
}

inline void sploot()
{
  robo_servo_front_right.set_angle(90);
  robo_servo_front_left.set_angle(90);

  robo_servo_back_left.set_angle(90);
  robo_servo_back_right.set_angle(90);
}
}
