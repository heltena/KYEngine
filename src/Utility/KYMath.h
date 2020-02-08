#pragma once

#include <KYEngine/Utility/Vector4.h>
#include <cmath>

class Math
{
private:
    Math() { }
    
public:
    static void init();
    static double abs(double v);
    static bool randomBool();
    static double randomBetween(double from, double to);
    static double randomWithOffset(double median, double offset);
    static double degrees(double radians);
    static double radians(double degrees);
    static double exp(double x);
    static double simplifyDegrees(double degrees);
    static double sin(double x);
    static double atan2Degrees(const Vector4& pos);
    static double interpolate(double from, double to, double interval, double accelMagnitude);
    static double clamp(double value, double min, double max);
    static bool isBetween(double value, double min, double max);
};