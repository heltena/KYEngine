#include <KYEngine/Optimizations/FullVertexData.h>

FullVertexData::FullVertexData()
{
}

FullVertexData::FullVertexData(const Vector4& vert, const Vector4& texCoord)
    : m_vert(vert)
    , m_texCoord(texCoord)
{
}

FullVertexData::FullVertexData(const FullVertexData& other)
    : m_vert(other.m_vert)
    , m_texCoord(other.m_texCoord)
{
}

FullVertexData::~FullVertexData()
{
}

void FullVertexData::scale(const Vector4& s)
{
    m_vert[0] *= s[0];
    m_vert[1] *= s[1];
    m_vert[2] *= s[2];
}

void FullVertexData::translate(const Vector4& t)
{
    m_vert += t;
}
