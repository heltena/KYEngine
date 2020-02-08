#include <KYEngine/Utility/Vector4.h>

#include <cmath>
#include <stdexcept>

Vector4::Vector4()
{
	for(int i = 0; i < 4; i++)
		m_values[i] = 0;
}

Vector4::Vector4(const Vector4& other)
{
	for(int i = 0; i < 4; i++)
		m_values[i] = other.m_values[i];
}

Vector4::Vector4(float x, float y, float z, float w)
{
	m_values[0] = x;
	m_values[1] = y;
	m_values[2] = z;
	m_values[3] = w;
}

const Vector4 Vector4::UNIT_X(1, 0, 0, 1);
const Vector4 Vector4::UNIT_Y(0, 1, 0, 1);
const Vector4 Vector4::UNIT_Z(0, 0, 1, 1);
const Vector4 Vector4::WHITE(1, 1, 1, 1);
const Vector4 Vector4::BLACK(0, 0, 0, 1);
const Vector4 Vector4::WHITE_TRANSPARENT(1, 1, 1, 0);
const Vector4 Vector4::BLACK_TRANSPARENT(0, 0, 0, 0);
const Vector4 Vector4::GRAVITY(0, -9.8, 0, 0);

Vector4 Vector4::fromPolar2D(double radians, double magnitude)
{
    return Vector4(magnitude * cos(radians), magnitude * sin(radians), 0, 1);
}

bool Vector4::operator==(const Vector4& other) const
{
    for(int i = 0; i < 4; i++)
        if (m_values[i] != other.m_values[i])
            return false;
    return true;
}

float& Vector4::operator[](int index)
{
#ifdef DEBUG
	if (index < 0 || index > 3)
		throw std::runtime_error("out of bound");
#endif
	return m_values[index];
}

float Vector4::operator[](int index) const
{
#ifdef DEBUG
	if (index < 0 || index > 3)
		throw std::runtime_error("out of bound");
#endif
	return m_values[index];
}

Vector4& Vector4::operator=(const Vector4& other)
{
	m_values[0] = other.m_values[0];
	m_values[1] = other.m_values[1];
	m_values[2] = other.m_values[2];
	m_values[3] = other.m_values[3];
	return *this;
}

Vector4 Vector4::operator*(double mag) const
{
    return Vector4(
        m_values[0] * mag,
        m_values[1] * mag,
        m_values[2] * mag,
        m_values[3] * mag);
}

Vector4 Vector4::operator/(double mag) const
{
    return Vector4(
                   m_values[0] / mag,
                   m_values[1] / mag,
                   m_values[2] / mag,
                   m_values[3] / mag);
}

Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4(
        m_values[0] + other.m_values[0],
        m_values[1] + other.m_values[1],
        m_values[2] + other.m_values[2],
        m_values[3] + other.m_values[3]);
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4(
        m_values[0] - other.m_values[0],
        m_values[1] - other.m_values[1],
        m_values[2] - other.m_values[2],
        m_values[3] - other.m_values[3]);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    m_values[0] += other.m_values[0];
    m_values[1] += other.m_values[1];
    m_values[2] += other.m_values[2];
    m_values[3] += other.m_values[3];
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    m_values[0] -= other.m_values[0];
    m_values[1] -= other.m_values[1];
    m_values[2] -= other.m_values[2];
    m_values[3] -= other.m_values[3];
    return *this;
}

void Vector4::clear()
{
    m_values[0] = 0;
    m_values[1] = 0;
    m_values[2] = 0;
    m_values[3] = 1;    
}

double Vector4::len() const
{
    return sqrt(m_values[0] * m_values[0]
                + m_values[1] * m_values[1] 
                + m_values[2] * m_values[2]);
}

double Vector4::sqrlen() const
{
    return m_values[0] * m_values[0]
           + m_values[1] * m_values[1] 
           + m_values[2] * m_values[2];
}

Vector4 Vector4::normalize() const
{
    double l = len();
    if (l == 0)
        return Vector4();
    else
        return *this * (1.0 / l);
}

bool Vector4::hasValidInfo() const
{
    for(int i = 0; i < 4; i++)
        if (std::isnan(m_values[i]) || std::isinf(m_values[i]))
            return false;
    return true;
}

std::ostream& Vector4::write(std::ostream& out) const
{
	return out
		<< "(" << m_values[0]
		<< ", " << m_values[1]
		<< ", " << m_values[2]
		<< ", " << m_values[3]
		<< ")";
}

Vector4 Vector4::interpolate(Vector4 from, Vector4 to, double interval, double accelMagnitude)
{
	if (interval > 1.0)
		interval = 1.0;
	if (interval < 0.0)
		interval = 0.0;

    bool useAccel = accelMagnitude > 1.0;
    if ((accelMagnitude < -1.0) && (interval > 0.5)) {
        useAccel = true;
        accelMagnitude = -accelMagnitude;
    }
    
	if (useAccel) {
		double xx = (interval-0.5) * M_PI * accelMagnitude;
		double ex = exp(xx);
		double emx = exp(-xx);
		
		interval = ((ex - emx) / (ex + emx) + 1) / 2.0;
    }
	
	float values[4];
	for(int i = 0; i < 4; i++)
		values[i] = from.m_values[i] * (1 - interval) + to.m_values[i] * interval;
	return Vector4(values[0], values[1], values[2], values[3]);
}

std::ostream& operator<<(std::ostream& out, const Vector4& item) {
	return item.write(out);
}

