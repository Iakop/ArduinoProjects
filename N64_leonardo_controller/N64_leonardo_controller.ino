#include <Joystick.h>
#include <N64Controller.h>

#define N64_PIN 13

Joystick_ VirtJoystick; // Instantiates the joystick.
N64Controller NController(N64_PIN);

void setup() {
  // put your setup code here, to run once:
  VirtJoystick.setXAxisRange(0,255);
  VirtJoystick.setYAxisRange(0,255);
  VirtJoystick.begin();
  NController.begin(N64_PIN);
  Serial.begin(115200);
}

void loop() {
  NController.update();
  VirtJoystick.setButton(0,NController.button_D_up());
  VirtJoystick.setButton(1,NController.button_D_down());
  VirtJoystick.setButton(2,NController.button_D_left());
  VirtJoystick.setButton(3,NController.button_D_right());
  VirtJoystick.setButton(4,NController.button_Start());
  VirtJoystick.setButton(5,NController.button_A());
  VirtJoystick.setButton(6,NController.button_B());
  VirtJoystick.setButton(7,NController.button_Z());
  VirtJoystick.setButton(8,NController.button_L());
  VirtJoystick.setButton(9,NController.button_R());
  VirtJoystick.setButton(10,NController.button_C_up());
  VirtJoystick.setButton(11,NController.button_C_down());
  VirtJoystick.setButton(12,NController.button_C_left());
  VirtJoystick.setButton(13,NController.button_C_right());
  VirtJoystick.setXAxis(NController.axis_x());
  VirtJoystick.setYAxis(NController.axis_y());
  Serial.print("X axis: "); Serial.println(NController.axis_x());
  Serial.print("Y axis: "); Serial.println(NController.axis_y());
}
