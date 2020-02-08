#include <KYEngine/Utility/SimpleDraw.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

SimpleDraw::SimpleDraw()
{
}

void SimpleDraw::drawLine(const Vector4& from, const Vector4& to, const Vector4& color, double width)
{
    float verts[4] = { from[0], from[1], to[0], to[1] };
    glColor4f(color[0], color[1], color[2], color[3]);
   
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
    glLineWidth(width);
    glDisable(GL_TEXTURE_2D);
    glDrawArrays(GL_LINES, 0, 2); 
}

void SimpleDraw::drawBox(const Box& box, const Vector4& color, double width)
{
    float verts[8] = {
        box[0],          box[1],
        box[0] + box[2], box[1],
        box[0] + box[2], box[1] + box[3],
        box[0],          box[1] + box[3] };

    glColor4f(color[0], color[1], color[2], color[3]);
   
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
    glLineWidth(width);
    glDisable(GL_TEXTURE_2D);
    glDrawArrays(GL_LINE_LOOP, 0, 4); 
}

