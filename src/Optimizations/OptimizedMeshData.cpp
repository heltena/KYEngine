#include <KYEngine/Optimizations/OptimizedMeshData.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <stdexcept>

OptimizedMeshData::OptimizedMeshData()
    : m_verts(NULL)
    , m_texCoords(NULL)
    , m_texture(NULL)
    , m_optimized(false)
    , m_infoLength(0)
{
}

OptimizedMeshData::~OptimizedMeshData()
{
    if (m_verts)
        delete[] m_verts;
    if (m_texCoords)
        delete[] m_texCoords;
}

void OptimizedMeshData::clear()
{
    if (m_verts)
        delete[] m_verts;
    m_verts = NULL;
    if (m_texCoords)
        delete[] m_texCoords;
    m_texCoords = NULL;
    m_optimized = false;
}

void OptimizedMeshData::prepareData(Texture* texture)
{
    m_texture = texture;
    m_data.clear();
    m_optimized = false;
}

void OptimizedMeshData::addFullVertexData(Texture* texture, const Vector4& vert, const Vector4& texCoord)
{
    if (m_texture == NULL)
        m_texture = texture;
    else if (m_texture != texture)
        throw std::runtime_error("OptimizedMeshData cannot optimize using different textures");
    m_data.push_back(FullVertexData(vert, texCoord));
}

void OptimizedMeshData::addFullVertexData(const OptimizedMeshData& data)
{
    if (m_texture == NULL)
        m_texture = data.m_texture;
    else if (m_texture != data.m_texture)
        throw std::runtime_error("OptimizedMeshData cannot optimize using different textures");
    for(std::list<FullVertexData>::const_iterator it = data.m_data.begin(); it != data.m_data.end(); it++)
        m_data.push_back(*it);
}

void OptimizedMeshData::scale(const Vector4& s)
{
    for(std::list<FullVertexData>::iterator it = m_data.begin(); it != m_data.end(); it++)
        it->scale(s);
}

void OptimizedMeshData::translate(const Vector4& t)
{
    for(std::list<FullVertexData>::iterator it = m_data.begin(); it != m_data.end(); it++)
        it->translate(t);
}

void OptimizedMeshData::optimize()
{
    if (m_optimized)
        throw std::runtime_error("OptimizedMeshData cannot optimize again");

    m_infoLength = m_data.size();
    
    if (m_verts)
        delete[] m_verts;
    m_verts = new float[ m_infoLength * 4 ];
    
    if (m_texCoords)
        delete[] m_texCoords;
    m_texCoords = new float[ m_infoLength * 2 ];
    
    int index = 0;
    for(std::list<FullVertexData>::const_iterator it = m_data.begin(); it != m_data.end(); it++) {
        const FullVertexData& item = *it;
        
        m_verts[index * 4 + 0] = item.vert()[0];
        m_verts[index * 4 + 1] = item.vert()[1];
        m_verts[index * 4 + 2] = item.vert()[2];
        m_verts[index * 4 + 3] = 1; // Always 1
        
        m_texCoords[index * 2 + 0] = item.texCoord()[0];
        m_texCoords[index * 2 + 1] = item.texCoord()[1];
        
        index++;
    }
    m_optimized = true;
    m_data.clear();
}

void OptimizedMeshData::draw()
{
    if (m_texture == NULL)
        throw std::runtime_error("OptimizedMeshData::draw: m_texture is NULL (maybe an empty grouped-mesh in resource group?)");

    glEnable(GL_TEXTURE_2D);
    m_texture->bind();
    glVertexPointer(4, GL_FLOAT, 0, m_verts);
    glTexCoordPointer(2, GL_FLOAT, 0, m_texCoords);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glNormal3f(0, 0, 1);
    glDrawArrays(GL_TRIANGLES, 0, m_infoLength);
}