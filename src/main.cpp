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

Robo::Servo robo_servo_front_left_hip(robo_brain, DIGITAL_IO_PIN(12));
Robo::Servo robo_servo_front_right_hip(robo_brain, DIGITAL_IO_PIN(11));
Robo::Servo robo_servo_back_left_hip(robo_brain, DIGITAL_IO_PIN(10));
Robo::Servo robo_servo_back_right_hip(robo_brain, DIGITAL_IO_PIN(9));

Robo::Servo robo_servo_front_left_foot(robo_brain, DIGITAL_IO_PIN(8));
Robo::Servo robo_servo_front_right_foot(robo_brain, DIGITAL_IO_PIN(7));
Robo::Servo robo_servo_back_left_foot(robo_brain, DIGITAL_IO_PIN(6));
Robo::Servo robo_servo_back_right_foot(robo_brain, DIGITAL_IO_PIN(5));

Robo::IRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(4));

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  pinMode(LED_BUILTIN , OUTPUT);

  robo_brain.setup();
}
namespace spider
{
  inline void hips_dive();
  inline void hips_capital_i();
  inline void hips_base();
  inline void feet_tippy_toe();
  inline void feet_base();
  inline void sit();
}

void loop()
{

  Serial.println("loop");

  spider::feet_base();
  delay(1000);

  spider::hips_base();
  delay(1000);

  spider::feet_tippy_toe();
  delay(1000);

  Robo::IRReceiver::IRCode ir_code = 0;
  if (robo_ir_receiver.detect_signal()) {
    ir_code = robo_ir_receiver.get_ir_code();

    switch ( ir_code ){
      case 0xFFA25D:
      Serial.println("CH-");
      break;
      case 0xFF629D:
      Serial.println("CH");
      break;
      case 0xFFE21D:
      Serial.println("CH+");
      break;
      case 0xFF22DD:
      Serial.println("|<<");
      break;
      case 0xFF02FD:
      Serial.println(">>|");
      break;
      case 0xFFC23D:
      Serial.println(">|");
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

  // spider::hips_capital_i();
  // delay(1000);


  // spider::feet_base();
  // delay(1000);

  // spider::sit();
  // delay(1000);
}

namespace spider
{
inline void hips_dive()
{
  robo_servo_front_right_hip.set_angle(180);
  robo_servo_front_left_hip.set_angle(0);

  robo_servo_back_left_hip.set_angle(180);
  robo_servo_back_right_hip.set_angle(0);
}

inline void hips_base()
{
  robo_servo_front_right_hip.set_angle(135);
  robo_servo_front_left_hip.set_angle(45);

  robo_servo_back_left_hip.set_angle(135);
  robo_servo_back_right_hip.set_angle(45);
}

inline void hips_capital_i()
{
  robo_servo_front_right_hip.set_angle(90);
  robo_servo_front_left_hip.set_angle(90);

  robo_servo_back_left_hip.set_angle(90);
  robo_servo_back_right_hip.set_angle(90);
}

inline void feet_tippy_toe()
{
  robo_servo_front_right_foot.set_angle(90);
  robo_servo_front_left_foot.set_angle(0);

  robo_servo_back_left_foot.set_angle(90);
  robo_servo_back_right_foot.set_angle(0);
}

inline void feet_base() {
  robo_servo_front_right_foot.set_angle(45);
  robo_servo_front_left_foot.set_angle(45);

  robo_servo_back_left_foot.set_angle(45);
  robo_servo_back_right_foot.set_angle(45);
}

inline void sit()
{
  robo_servo_front_right_foot.set_angle(0);
  robo_servo_front_left_foot.set_angle(0);

  robo_servo_back_left_foot.set_angle(0);
  robo_servo_back_right_foot.set_angle(0);
}

}  // namespace spider
