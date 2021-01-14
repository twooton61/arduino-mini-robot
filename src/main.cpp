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

Robo::Servo robo_servo(robo_brain, DIGITAL_IO_PIN(2));

Robo::OLED robo_oled(robo_brain);

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  robo_brain.setup();
}

void loop()
{
  Serial.println("loop1");

  robo_servo.reset();

  delay(1000);

  robo_oled.clear();

  delay(1000);

  robo_oled.drawDot(0, 0);
  robo_oled.drawDot(127, 0);
  robo_oled.drawDot(127, 63);
  robo_oled.drawDot(0, 63);

  delay(1000);

  robo_servo.set_angle(180);

  delay(1000);
}
