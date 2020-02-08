#pragma once

#include <KYEngine/Utility/Vector4.h>

#include <ostream>

class Box
{
public:
	Box();
	Box(const Box& other);
	Box(float width, float height);
	Box(float left, float top, float width, float height);
	
public:
	float left() const { return m_values[0]; }
	float top() const { return m_values[1]; }
	float width() const { return m_values[2]; }
	float height() const { return m_values[3]; }
    float right() const { return m_values[0] + m_values[2]; }
    float bottom() const { return m_values[1] + m_values[3]; }
    float area() const { return m_values[2] * m_values[3]; }
    bool empty() const { return m_values[2] == 0 || m_values[3] == 0; }
    Vector4 center() const { return Vector4(m_values[0] + m_values[2] / 2, m_values[1] + m_values[3] / 2, 0, 0); }

	float& operator[](int index);
	float operator[](int index) const;
	Box& operator=(const Box& other);

	Box& addSize(double width, double height, bool center = true);
	Box& unionWith(const Box& other);
    Box& scale(const Vector4& scale);
	Box& translate(const Vector4& offset);

    Box intersection(const Box& other) const;
    
	bool contains(const Vector4& pos) const;
	
	std::ostream& write(std::ostream& out) const;

private:
	float m_values[4];
};

std::ostream& operator<<(std::ostream& out, const Box& item);

