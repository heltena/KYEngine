#pragma once

#include <KYEngine/Utility/Vector4.h>

class FullVertexData
{
public:
    FullVertexData();
    FullVertexData(const Vector4& vert, const Vector4& texCoord);
    FullVertexData(const FullVertexData& other);
    virtual ~FullVertexData();
    
public:
    const Vector4& vert() const { return m_vert; }
    const Vector4& texCoord() const { return m_texCoord; }
    
public:
    void scale(const Vector4& s);
    void translate(const Vector4& t);
    
private:
    Vector4 m_vert;
    Vector4 m_texCoord;
};