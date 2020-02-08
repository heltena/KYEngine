#pragma once

#include <KYEngine/Entity.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class EntityFactory
{
private:
    EntityFactory();

public:
    static Entity* createAnimMeshEntity(const std::string& name, const std::string& animMeshCollectionRef, const Vector4& initialPos = Vector4::BLACK, double initialHPercent = 1, const Vector4& color = Vector4::WHITE, const Vector4& scale = Vector4::WHITE, bool useBlending = true);
    
    static Entity* createMeshEntity(const std::string& name, const std::string& meshRef, const Vector4& initialPos = Vector4::BLACK, double initialHPercent = 1, const Vector4& color = Vector4::WHITE, double angle = 0, bool useBlending = true);
    
    static Entity* createTextLayerEntity(const std::string& name, const std::string& fontRef, double lineLength, double lineSpacing, AlignType align = ALIGN_LEFT, const std::string& defaultText = "", const Vector4& pivot = Vector4::BLACK_TRANSPARENT, const Vector4& borderColor = Vector4::BLACK, bool useBlending = false);
};