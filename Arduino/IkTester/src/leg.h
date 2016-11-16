#include <Servo.h>
#include <Math.h>

enum Side
{
    LEFT = 0,
    RIGHT = 1
};

class Leg
{
private:
    Side side;
    struct
    {
        Servo alpha;
        Servo beta;
        Servo gamma;
    } servos;

    struct
    {
        int alpha;
        int beta;
        int gamma;
    } angles;

    struct
    {
        int coxa;
        int tibia;
        int femur;
    } length;


    double calcL(double z_offset, double y);
    double calcAlpha(double L, double z_offset);
    double calcBeta(double L);
    double calcGamma(double x, double y);
public:
    Leg();
    void init(int gamma_pin, int beta_pin, int alpha_pin, Side leg_side, int length_coxa, int length_femur,int length_tibia);
    void write(int alpha, int beta, int gamma);
    void reach(int x, int y, int z);
};
