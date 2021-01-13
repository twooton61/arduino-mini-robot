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

Robo::Brain robo_brain;

Robo::Servo main_robo_servo(robo_brain, DIGITAL_IO_PIN(10));

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  robo_brain.setup();
}

void loop()
{
  Serial.println("loop");

  main_robo_servo.reset();

  delay(1000);
}
