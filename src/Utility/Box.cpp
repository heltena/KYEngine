#include <KYEngine/Utility/Box.h>

#include <algorithm>

Box::Box()
{
	m_values[0] = 0.0f;
	m_values[1] = 0.0f;
	m_values[2] = 1.0f;
	m_values[3] = 1.0f;
}

Box::Box(const Box& other)
{
	for(int i = 0; i < 4; i++)
		m_values[i] = other.m_values[i];
}

Box::Box(float width, float height)
{
	m_values[0] = 0.0f;
	m_values[1] = 0.0f;
	m_values[2] = width;
	m_values[3] = height;
}

Box::Box(float left, float top, float width, float height)
{
	m_values[0] = left;
	m_values[1] = top;
	m_values[2] = width;
	m_values[3] = height;
}

float& Box::operator[](int index)
{
	return m_values[index];
}

float Box::operator[](int index) const
{
	return m_values[index];
}

Box& Box::operator=(const Box& other)
{
	for(int i = 0; i < 4; i++)
		m_values[i] = other.m_values[i];
	return *this;
}

Box& Box::addSize(double width, double height, bool center)
{
    if (center) {
        m_values[0] -= width / 2.;
        m_values[1] -= height / 2.;
    }
    m_values[2] += width;
    m_values[3] += height;
    return *this;
}

Box& Box::unionWith(const Box& other)
{
	float right = std::max(m_values[0] + m_values[2], other.m_values[0] + other.m_values[2]);
	float bottom = std::max(m_values[1] + m_values[3], other.m_values[1] + other.m_values[3]);
	
	m_values[0] = std::min(m_values[0], other.m_values[0]);
	m_values[1] = std::min(m_values[1], other.m_values[1]);
	m_values[2] = right - m_values[0];
	m_values[3] = bottom - m_values[1];
	return *this;
}

Box& Box::scale(const Vector4& scale)
{
    m_values[2] *= scale[0];
    m_values[3] *= scale[1];
    return *this;
}

Box& Box::translate(const Vector4& offset)
{
	m_values[0] += offset[0];
	m_values[1] += offset[1];
	return *this;
}

Box Box::intersection(const Box& other) const
{
    float f[2], t[2];
    
    for(int i = 0; i < 2; i++) {
        float a = m_values[i];
        float b = m_values[i] + m_values[2 + i];
        float c = other.m_values[i];
        float d = other.m_values[i] + other.m_values[2 + i];
        
        if (a > b)
            std::swap(a, b);
        if (c > d)
            std::swap(c, d);
        
        if (a > c) {
            std::swap(a, c);
            std::swap(b, d);
        }
        
        if (b < c) // a----b c----d
            return Box(0, 0, 0, 0);
        
        if (b == c) { // a----b/c----d
            f[i] = b;
            t[i] = b;
        } else if (b < d) { // a----c===b---d
            f[i] = c;
            t[i] = b;
        } else {    // a----c===d----b
            f[i] = c;
            t[i] = d;
        }
    }
    return Box(f[0], f[1], t[0] - f[0], t[1] - f[1]);
}

bool Box::contains(const Vector4& pos) const
{
	return (pos[0] >= m_values[0])
		&& (pos[0] <= m_values[0] + m_values[2])
		&& (pos[1] >= m_values[1])
		&& (pos[1] <= m_values[1] + m_values[3]);
}

std::ostream& Box::write(std::ostream& out) const
{
	return out
	<< "(" << m_values[0]
	<< ", " << m_values[1]
	<< ", " << m_values[2]
	<< ", " << m_values[3]
	<< ")";
}

std::ostream& operator<<(std::ostream& out, const Box& item) {
	return item.write(out);
}


