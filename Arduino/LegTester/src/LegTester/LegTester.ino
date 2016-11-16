#include <Servo.h>


class Leg
{
private:
    struct
    {
        Servo coxa;
        Servo femur;
        Servo tibia;
    } servos;
    struct
    {
        int coxa;
        int femur;
        int tibia;
    } positions;

    void write()
    {
        servos.coxa.write(positions.coxa);
        servos.femur.write(positions.femur);
        servos.tibia.write(positions.tibia);
    }
public:
    Leg() {}
    void init(uint8_t coxa_pin, uint8_t femur_pin, uint8_t tibia_pin)
    {
        servos.coxa.attach(coxa_pin);
        servos.femur.attach(femur_pin);
        servos.tibia.attach(tibia_pin);
    }
    void reset()
    {
        positions.coxa = 90;
        positions.femur = 90;
        positions.tibia = 90;
        write();
    }

    void up(int a)
    {
        positions.femur += a;
        positions.tibia += a;
        write();
    }

    void down(int a)
    {
        positions.femur -= a;
        positions.tibia -= a;
        write();
    }

    void move(int a)
    {
        positions.coxa -= a;
        write();
    }
};

Leg leg;
int delayt = 400;

void setup()
{
    leg.init(2, 3, 4);
    leg.reset();
    Serial.begin(9600);
}

void loop() {
    leg.reset();
    delay(delayt*5);
    leg.up(20);
    delay(delayt);
    leg.move(40);
    delay(delayt);
    leg.down(20);
    delay(delayt);
    leg.up(20);
    delay(delayt);
    leg.move(-40);
    delay(delayt);
    leg.down(20);
    delay(delayt);
}
