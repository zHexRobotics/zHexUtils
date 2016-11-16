#include "Leg.h"

double Leg::calcL(double z_offset, double y)
{
  return sqrt(z_offset * z_offset + (y - length.coxa) * (y - length.coxa));
}


double Leg::calcAlpha(double L, double z_offset)
{
  double alpha_1 = acos(z_offset / L);
  double alpha_2 = acos((length.tibia * length.tibia - length.femur * length.femur - L * L) / (-2.0 * length.femur * L));
  return (alpha_1 + alpha_2) * 180.0 / 3.14;
}


double Leg::calcBeta(double L)
{
  return acos((L * L - length.tibia * length.tibia - length.femur * length.femur) / (-2.0 * length.tibia * length.femur)) * 180.0 / 3.14;
}


double Leg::calcGamma(double x, double y)
{
  return atan(x / y) * 180.0 / 3.14;
}


Leg::Leg()
{
    angles.alpha = 90;
    angles.beta = 90;
    angles.gamma = 90;
}


void Leg::init(int gamma_pin, int beta_pin, int alpha_pin, Side leg_side, int length_coxa, int length_femur,int length_tibia)
{
    side = leg_side;
    length.coxa = length_coxa;
    length.femur = length_femur;
    length.tibia = length_tibia;
    servos.gamma.attach(gamma_pin);
    servos.beta.attach(beta_pin);
    servos.alpha.attach(alpha_pin);
    servos.gamma.write(angles.gamma);
    servos.beta.write(angles.beta);
    servos.alpha.write(angles.alpha);
}


void Leg::write(int alpha, int beta, int gamma)
{
    if (side == LEFT)
    {
        angles.alpha = alpha;
        angles.beta = 180 - beta;
        angles.gamma = 90 - gamma;
    }
    else
    {
        angles.alpha = 180 - alpha;
        angles.beta = beta;
        angles.gamma = 90 + gamma;
    }

    servos.gamma.write(angles.gamma);
    servos.beta.write(angles.beta);
    servos.alpha.write(angles.alpha);
}


void Leg::reach(int x, int y, int z)
{
    double L = calcL(z, y);
    double alpha = calcAlpha(L, z);
    double beta =  calcBeta(L);
    double gamma = calcGamma(x, y);
    write(alpha, beta, gamma);
}
