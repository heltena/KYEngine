#include <KYEngine/Utility/KYMath.h>

#include <cmath>
#include <cstdlib>

void Math::init()
{
    srand(time(NULL));
}

double Math::abs(double v)
{
    return fabs(v);
}

bool Math::randomBool()
{
    return rand() % 2 == 0;
}
    
double Math::randomBetween(double from, double to)
{
    return from + (to - from) * (double) rand() / (RAND_MAX + 1.);
}

double Math::randomWithOffset(double median, double offset)
{
    return randomBetween(median - offset / 2., median + offset / 2.);
}

double Math::degrees(double radians)
{
    return radians * 180.0 / M_PI;
}

double Math::radians(double degrees)
{
    return degrees * M_PI / 180.0;
}

double Math::exp(double x)
{
    return ::exp(x);
}

double Math::simplifyDegrees(double degrees)
{
    double p = degrees / 360.;
    int r = (int) p;
    p -= r;
    if (p < 0)
        p = 1 + p;
    return p * 360;
}

double Math::sin(double x)
{
    return ::sin(x);
}

double Math::atan2Degrees(const Vector4& pos)
{
    return degrees(atan2(pos[1], pos[0]));
}

double Math::interpolate(double from, double to, double interval, double accelMagnitude)
{
	if (interval > 1.0)
		interval = 1.0;
	if (interval < 0.0)
		interval = 0.0;
    
	if (accelMagnitude > 1.0) {
		double xx = (interval-0.5) * M_PI * accelMagnitude;
		double ex = exp(xx);
		double emx = exp(-xx);
		
		interval = ((ex - emx) / (ex + emx) + 1) / 2.0;
	}
	
	return from * (1 - interval) + to * interval;
}

double Math::clamp(double value, double min, double max)
{
    if (value <= min)
        return min;
    else if (value >= max)
        return max;
    else
        return value;
}

bool Math::isBetween(double value, double min, double max)
{
    return (value >= min && value < max);
}
