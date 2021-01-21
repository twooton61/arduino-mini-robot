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

Robo::Servo robo_servo_1(robo_brain, DIGITAL_IO_PIN(2));
Robo::Servo robo_servo_2(robo_brain, DIGITAL_IO_PIN(3));
Robo::Servo robo_servo_3(robo_brain, DIGITAL_IO_PIN(4));
Robo::Servo robo_servo_4(robo_brain, DIGITAL_IO_PIN(5));

Robo::OLED robo_oled(robo_brain);

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  robo_brain.setup();
}

void loop()
{
  Serial.println("loop2");
  robo_oled.clear();


  robo_servo_1.reset();
  robo_servo_2.reset();
  robo_servo_3.reset();
  robo_servo_4.reset();
  robo_oled.print("0");

  delay(1000);

  robo_servo_1.set_angle(20);
  robo_servo_2.set_angle(20);
  robo_servo_3.set_angle(20);
  robo_servo_4.set_angle(20);
  robo_oled.print("1");

  delay(2000);
}
