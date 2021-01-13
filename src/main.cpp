/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <RoboBrain.h>
#include <RoboServo.h>
#include <RoboLCD.h>
#include <RoboDancer.h>
#include <RoboUltrasonicSensor.h>
#include <RoboWeatherSensor.h>

RoboBrain robo_brain;

RoboServo main_robo_servo(robo_brain, DIGITAL_IO_PIN(10));

RoboDancer robo_dancer(robo_brain, main_robo_servo, DIGITAL_IO_PIN(6));

RoboUltrasonicSensor robo_ultrasonice_sensor(robo_brain, DIGITAL_IO_PIN(8), DIGITAL_IO_PIN(9));

RoboWeatherSensor robo_weather_sensor(robo_brain, DIGITAL_IO_PIN(13));

const int BUTTON_PIN = 7;

RoboLCD robo_lcd(
  robo_brain,
  DIGITAL_IO_PIN(12),
  DIGITAL_IO_PIN(11),
  DIGITAL_IO_PIN(5),
  DIGITAL_IO_PIN(4),
  DIGITAL_IO_PIN(3),
  DIGITAL_IO_PIN(2)
);

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  robo_brain.setup();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

unsigned long cm_to_inches(unsigned long cm)
{
  return cm / 2.54;
}

void loop()
{
  Serial.println("loop");

  char test3 = 'a';
  Serial.println("char size");
  Serial.println(sizeof(&test3)); // 2

  int int_array[2] = { 6, 7 };
  int* int_ptr = &int_array[0];

  Serial.println("test ptr");
  Serial.println((unsigned short)int_ptr, HEX); // 21F7
  Serial.println((unsigned short)(int_ptr + 1), HEX); // 21F9
  Serial.println((unsigned short)int_array, HEX); // 21F7
  Serial.println(int_array[0]); // 6
  Serial.println(int_array[1]); // 7
  Serial.println(int_array[2]); // 7

  Serial.println(*(int_ptr)); // 7 (ptr arith), same as int_array[1]
  Serial.println(*(int_ptr + 1)); // 7 (ptr arith), same as int_array[1]


  const unsigned long in_from_ultrasonic_sensor = cm_to_inches(robo_ultrasonice_sensor.get_cm_from_sensor());

  if (in_from_ultrasonic_sensor == 0) {
    Serial.println("sensor error, reading 0 distance");
  }
  else if (in_from_ultrasonic_sensor <= 5)
  {
    robo_lcd.write_double_line("Motion Detected", String(in_from_ultrasonic_sensor) + "in away");

    delay(3000);

    robo_lcd.write_double_line("Playing", "Star Wars");

    robo_dancer.play_star_wars(main_robo_servo);

  } else {
    const String lcd_line_1 = String(robo_weather_sensor.get_temperature_fahrenheit()) + String("F") + String("  ") + String(in_from_ultrasonic_sensor) + " away";
    const String lcd_line_2 = String(robo_weather_sensor.get_humidity()) + String(" humidity");
    robo_lcd.write_double_line(lcd_line_1, lcd_line_2);

    main_robo_servo.reset();
  }

  delay(1000);
}