#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define CHAINED_MOTOR_NUM	2
#define pinCS	10

L6470Stepper stepper(pinCS, CHAINED_MOTOR_NUM);	// pass CS pin number & number of chained motors

void setup()
{
  Serial.begin(9600);

  stepper.setup();
  stepper.angle(0);
  stepper.resetPos();
  stepper.softStop();
  //stepper.angle(0);	// this makes all motors do the same motion
}

void loop()
{
  static boolean switchAngle = false;
  static unsigned long timePoint = 0;

  unsigned long currentTime = millis() - timePoint;

  if (currentTime > 1000) {
    if (switchAngle) {
      stepper.setAngle(180, 0);
      stepper.setAngle(360, 1);
    } else {
      stepper.setAngle(0, 0);
      stepper.setAngle(0, 1);
    }
    stepper.execute();
    switchAngle = !switchAngle;
    timePoint = millis();
  }

  Serial.print(stepper.getCurrAngle(0));
  Serial.print(",");
  Serial.println(stepper.getCurrAngle(1));
}
