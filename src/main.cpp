/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <Robo/Brain.h>
#include <Robo/IRReceiver.h>
#include <Robo/Servo.h>

Robo::Brain robo_brain;

Robo::Servo robo_servo_front_left_hip(robo_brain, DIGITAL_IO_PIN(12), 90, 45, 0);
Robo::Servo robo_servo_front_right_hip(robo_brain, DIGITAL_IO_PIN(11), 90, 135, 180);
Robo::Servo robo_servo_back_left_hip(robo_brain, DIGITAL_IO_PIN(10), 90, 135, 180);
Robo::Servo robo_servo_back_right_hip(robo_brain, DIGITAL_IO_PIN(9), 90, 45, 0);

Robo::Servo robo_servo_front_left_foot(robo_brain, DIGITAL_IO_PIN(8), 90, 45, 0);
Robo::Servo robo_servo_front_right_foot(robo_brain, DIGITAL_IO_PIN(7), 0, 45, 90);
Robo::Servo robo_servo_back_left_foot(robo_brain, DIGITAL_IO_PIN(6), 0, 45, 90);
Robo::Servo robo_servo_back_right_foot(robo_brain, DIGITAL_IO_PIN(5), 90, 45, 0);

Robo::IRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(4));

namespace spider
{
inline void hips_sit()
{
  robo_servo_front_right_hip.flat();
  robo_servo_front_left_hip.flat();

  robo_servo_back_left_hip.flat();
  robo_servo_back_right_hip.flat();
}

inline void hips_base()
{
  robo_servo_front_right_hip.base();
  robo_servo_front_left_hip.base();
  robo_servo_back_left_hip.base();
  robo_servo_back_right_hip.base();
}

inline void hips_straight()
{
  robo_servo_front_right_hip.straight();
  robo_servo_front_left_hip.straight();
  robo_servo_back_left_hip.straight();
  robo_servo_back_right_hip.straight();
}

inline void feet_sit()
{
  robo_servo_front_right_foot.flat();
  robo_servo_front_left_foot.flat();

  robo_servo_back_left_foot.flat();
  robo_servo_back_right_foot.flat();
}

inline void feet_base() {
  robo_servo_front_right_foot.base();
  robo_servo_front_left_foot.base();

  robo_servo_back_left_foot.base();
  robo_servo_back_right_foot.base();
}

inline void feet_tippy_toe()
{
  robo_servo_front_right_foot.tippy_toe();
  robo_servo_front_left_foot.tippy_toe();

  robo_servo_back_left_foot.tippy_toe();
  robo_servo_back_right_foot.tippy_toe();
}

inline void step_front_right()
{

  hips_base();
  delay(500);

  feet_tippy_toe();
  delay(500);

  // lift front right foot
  robo_servo_front_right_foot.set_angle(45);
  delay(500);

  // move front right hip to staight in front
  robo_servo_front_right_hip.set_angle(180);
  delay(500);

  // put front right foot on ground
  robo_servo_front_right_foot.set_angle(90);
  delay(500);

  // base all the other feet
  robo_servo_front_left_foot.set_angle(0);
  robo_servo_back_left_foot.set_angle(90);
  robo_servo_back_right_foot.set_angle(0);

  // step
  robo_servo_front_right_hip.set_angle(135);

  // return to base
  robo_servo_front_right_foot.set_angle(45);
}

}  // namespace spider

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  pinMode(LED_BUILTIN , OUTPUT);

  robo_brain.setup();
}

static const int TICK_INTERVAL = 300;
unsigned long last_tick = 0;

void loop()
{
  if (millis() < last_tick + TICK_INTERVAL){
    return;
  }
  last_tick += TICK_INTERVAL;

  Serial.println("loop");

  Robo::IRReceiver::IRCode ir_code = 0;
  if (robo_ir_receiver.detect_signal()) {
    ir_code = robo_ir_receiver.get_ir_code();

    switch ( ir_code ){
      case 0xFFA25D:
      Serial.println("CH-");
      spider::hips_sit();
      delay(1000);

      break;
      case 0xFF629D:
      Serial.println("CH");
      spider::hips_base();
      delay(1000);

      break;
      case 0xFFE21D:
      Serial.println("CH+");
      spider::hips_straight();
      delay(1000);

      break;
      case 0xFF22DD:
      Serial.println("|<<");
      spider::feet_sit();
      delay(1000);

      break;
      case 0xFF02FD:
      Serial.println(">>|");
      spider::feet_base();
      delay(1000);

      break;
      case 0xFFC23D:
      Serial.println(">|");
      spider::feet_tippy_toe();
      delay(1000);

      break;
      case 0xFFE01F:
      Serial.println("-");
      break;
      case 0xFFA857:
      Serial.println("+");
      break;
      case 0xFF906F:
      Serial.println("EQ");
      break;
      case 0xFF6897:
      Serial.println("0");
      break;
      case 0xFF9867:
      Serial.println("100+");
      break;
      case 0xFFB04F:
      Serial.println("200+");
      break;
      case 0xFF30CF:
      Serial.println("1");
      break;
      case 0xFF18E7:
      Serial.println("2");
      break;
      case 0xFF7A85:
      Serial.println("3");
      spider::step_front_right();
      break;
      case 0xFF10EF:
      Serial.println("4");
      break;
      case 0xFF38C7:
      Serial.println("5");
      break;
      case 0xFF5AA5:
      Serial.println("6");
      break;
      case 0xFF42BD:
      Serial.println("7");
      break;
      case 0xFF4AB5:
      Serial.println("8");
      break;
      case 0xFF52AD:
      Serial.println("9");
      break;
    }

    Serial.println("IR CODE:");
    Serial.println(ir_code);

    robo_ir_receiver.resume();
  }
}
