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

Robo::Servo main_robo_servo(robo_brain, DIGITAL_IO_PIN(10));

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

  main_robo_servo.reset();

  delay(1000);

  robo_oled.clear();

  delay(1000);

  robo_oled.print("test");

  delay(1000);
}
