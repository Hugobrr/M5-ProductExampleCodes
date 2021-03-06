#include <M5Stack.h>
#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

#define SERVOMIN  102 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  512 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  500 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2500 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void setup() {
  M5.begin(true, true, true, true);
  pwm.begin();
  pwm.setPWMFreq(50); 
}

void setServoPulse(uint8_t n, double pulse) {
   double pulselength;
   pulselength = 1000000;   // 1,000,000 us per second
   pulselength /= 50;   // 50 Hz
   Serial.print(pulselength); Serial.println(" us per period"); 
   pulselength /= 4096;  // 12 bits of resolution
   Serial.print(pulselength); Serial.println(" us per bit"); 
   pulse *= 1000;
   pulse /= pulselength;
   Serial.println(pulse);
   pwm.setPWM(n, 0, pulse);
}

void servo_angle_write(uint8_t n, int Angle) {
  double pulse = Angle;
  pulse = pluse/90 + 0.5;
  setServoPulse(n, pulse);
}

void loop() {
  for(int i=0; i<16; i++) {
    servo_angle_write(i, 0);
    delay(500);
    servo_angle_write(i, 180);
  }

}
