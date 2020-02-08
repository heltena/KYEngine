#pragma once

#include <ostream>

class Vector4
{
public:
	Vector4();
    Vector4(const Vector4& other);
	Vector4(float x, float y, float z = 0, float w = 1);

public:
    static Vector4 fromPolar2D(double radians, double magnitude);

    static const Vector4 UNIT_X;
    static const Vector4 UNIT_Y;
    static const Vector4 UNIT_Z;
    static const Vector4 WHITE;
    static const Vector4 BLACK;
    static const Vector4 WHITE_TRANSPARENT;
    static const Vector4 BLACK_TRANSPARENT;
    static const Vector4 GRAVITY;

public:
    bool operator==(const Vector4& other) const;
	float& operator[](int index);
	float operator[](int index) const;
	Vector4& operator=(const Vector4& other);
    Vector4 operator*(double mag) const;
    Vector4 operator/(double mag) const;
    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    void clear();
    double len() const;
    double sqrlen() const;
    Vector4 normalize() const;
    
    bool hasValidInfo() const;
    
	std::ostream& write(std::ostream& out) const;
	static Vector4 interpolate(Vector4 from, Vector4 to, double interval, double accelMagnitude = 0.0);
	
private:
	float m_values[4];
};

std::ostream& operator<<(std::ostream& out, const Vector4& item);
