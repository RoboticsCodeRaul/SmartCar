// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motorFreEsq(1);
AF_DCMotor motorTrasEsq(2);
AF_DCMotor motorFreDir(3);
AF_DCMotor motorTrasDir(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motorFreEsq.setSpeed(200);
  motorFreDir.setSpeed(200);
  motorTrasEsq.setSpeed(200);
  motorTrasDir.setSpeed(200);

  para();
}

void loop() {

}

void frente() {
  motorFreEsq.run(FORWARD);
  motorFreDir.run(FORWARD);
  motorTrasEsq.run(FORWARD);
  motorTrasDir.run(FORWARD);
}

void tras() {
  motorFreEsq.run(BACKWARD);
  motorFreDir.run(BACKWARD);
  motorTrasEsq.run(BACKWARD);
  motorTrasDir.run(BACKWARD);
}

void esq() {
  motorFreEsq.run(BACKWARD);
  motorFreDir.run(FORWARD);
  motorTrasEsq.run(BACKWARD);
  motorTrasDir.run(FORWARD);
}

void dir() {
  motorFreEsq.run(FORWARD);
  motorFreDir.run(BACKWARD);
  motorTrasEsq.run(FORWARD);
  motorTrasDir.run(BACKWARD);
}

void para() {
  motorFreEsq.run(RELEASE);
  motorFreDir.run(RELEASE);
  motorTrasEsq.run(RELEASE);
  motorTrasDir.run(RELEASE);
}
