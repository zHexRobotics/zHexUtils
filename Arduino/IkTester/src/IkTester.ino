#include <Servo.h>
#include "Leg.h"

const int ALPHA_PINS[6] = {30,31,36,37,42,43};
const int BETA_PINS[6] = {32,33,38,39,44,45};
const int GAMMA_PINS[6] = {28,29,34,35,40,41};

const int coxa_pin = 29;
const int femur_pin = 33;
const int tibia_pin = 31;
const int delayt = 250;

const double length_coxa = 40;
const double length_femur = 85;
const double length_tibia = 115;




Leg leg[6];
void setup()
{
  for (int i = 0; i < 6; i++)
  {
    leg[i].init(GAMMA_PINS[i], BETA_PINS[i], ALPHA_PINS[i], (i % 2 == 0) ? Side::RIGHT : Side::LEFT, length_coxa, length_femur, length_tibia);
  }
  Serial.begin(57600);
}

void loop()
{
  while(Serial.available() >= 4)
  {
    int n = Serial.parseInt();
    int x = Serial.parseInt();
    int y = Serial.parseInt();
    int z = Serial.parseInt();
    Serial.print(n);
    Serial.print(" | ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.print(z);
    Serial.print(" |");
    leg[n].reach(x, y, z);
    Serial.println();
  }
}
