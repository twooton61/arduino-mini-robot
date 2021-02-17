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

Robo::Servo robo_servo_front_left_hip(robo_brain, DIGITAL_IO_PIN(12), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);
Robo::Servo robo_servo_front_right_hip(robo_brain, DIGITAL_IO_PIN(11), 90, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_left_hip(robo_brain, DIGITAL_IO_PIN(10), 90, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_right_hip(robo_brain, DIGITAL_IO_PIN(9), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);

Robo::Servo robo_servo_front_left_knee(robo_brain, DIGITAL_IO_PIN(8), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);
Robo::Servo robo_servo_front_right_knee(robo_brain, DIGITAL_IO_PIN(7), 0, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_left_knee(robo_brain, DIGITAL_IO_PIN(6), 0, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_right_knee(robo_brain, DIGITAL_IO_PIN(5), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);

Robo::IRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(4));

namespace spider
{
inline void idle()
{
  delay(100);
}

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
  robo_servo_front_right_knee.flat();
  robo_servo_front_left_knee.flat();

  robo_servo_back_left_knee.flat();
  robo_servo_back_right_knee.flat();
}

inline void feet_base() {
  robo_servo_front_right_knee.base();
  robo_servo_front_left_knee.base();

  robo_servo_back_left_knee.base();
  robo_servo_back_right_knee.base();
}

inline void feet_straight()
{
  robo_servo_front_right_knee.straight();
  robo_servo_front_left_knee.straight();

  robo_servo_back_left_knee.straight();
  robo_servo_back_right_knee.straight();
}

inline void step_front_right()
{
  hips_base();
  idle();

  feet_base();
  idle();

  robo_servo_front_right_knee.straight();
  robo_servo_back_right_knee.straight();
  robo_servo_back_left_knee.straight();

  idle();

  robo_servo_front_right_knee.flat();
  robo_servo_front_right_hip.straight();
  idle();

  robo_servo_front_right_knee.straight();
  idle();

  hips_base();
  idle();

  feet_straight();
  idle();
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
      spider::feet_straight();
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
