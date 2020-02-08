#include <KYEngine/Touch.h>

Touch::Touch()
    : m_id(0)
    , m_x(0)
    , m_y(0)
    , m_used(false)
{
}

Touch::Touch(int id, int x, int y)
    : m_id(id)
    , m_x(x)
    , m_y(y)
    , m_used(false)
{
}

Touch::Touch(const Touch& other)
    : m_id(other.m_id)
    , m_x(other.m_x)
    , m_y(other.m_y)
    , m_used(other.m_used)
{
}

Touch::~Touch()
{
}