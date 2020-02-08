#pragma one

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/Vector4.h>

class SimpleDraw
{
private:
    SimpleDraw();
    
public:
    static void drawLine(const Vector4& from, const Vector4& to, const Vector4& color, double width);
    static void drawBox(const Box& box, const Vector4& color, double width);
};