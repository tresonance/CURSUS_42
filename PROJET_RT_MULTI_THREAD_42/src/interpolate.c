#include "rt.h"

double linear_interpolate(double a, double b, double t)
{
 return (1. - t) * a + t * b;
}

double cosine_interpolate(double a, double b, double t)
{
 double c = (1 - cos(t * 3.1415927)) * .5;
  return (1. - c) * a + c * b;
}

double cubic_interpolate(double before_p0, double p0,
 double p1, double after_p1, double t)
 {
  //Calcul des coefficients de notre polynôme
  double a3 = -0.5*before_p0 + 1.5*p0 - 1.5*p1 + 0.5*after_p1;
  double a2 = before_p0 - 2.5*p0 + 2*p1 - 0.5*after_p1;
  double a1 = -0.5*before_p0 + 0.5*p1;
  double a0 = p0;
  //Calcul de la valeur de ce polynôme en t
  return (a3 * t*t*t) + (a2 * t*t) + (a1 * t) + a0;
}
