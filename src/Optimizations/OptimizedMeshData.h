#pragma once

#include <KYEngine/Optimizations/FullVertexData.h>
#include <KYEngine/Texture.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>
#include <map>
#include <string>

// It uses GL_TRIANGLES!!!!

class OptimizedMeshData
{
public:
    OptimizedMeshData();
    virtual ~OptimizedMeshData();
    
public:
    void clear();
    void prepareData(Texture* texture);
    void addFullVertexData(Texture* texture, const Vector4& vert, const Vector4& texCoord);
    void addFullVertexData(const OptimizedMeshData& data);
    void scale(const Vector4& s);
    void translate(const Vector4& t);
    void optimize();
    bool optimized() const { return m_optimized; }
    
public:
    void draw();

private:
    bool m_optimized;
    Texture* m_texture;
    std::list<FullVertexData> m_data;
    float* m_verts;
    float* m_texCoords;
    int m_infoLength;
};