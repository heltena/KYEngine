#pragma once

#include <KYEngine/Utility/Vector4.h>

class Touch
{
public:
    Touch();
    Touch(int id, int x, int y);
    Touch(const Touch& other);
    virtual ~Touch();
    
public:
    int id() const { return m_id; }
    int x() const { return m_x; }
    int y() const { return m_y; }
    Vector4 pos() const { return Vector4(m_x, m_y); }
    void setUsed(bool used = true) const { m_used = used; }
    bool used() const { return m_used; }
    
private:
    int m_id;
    int m_x;
    int m_y;
    mutable bool m_used;
};