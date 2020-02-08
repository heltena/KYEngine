#include <KYEngine/Factories/EntityFactory.h>
#include <KYEngine/Private/Resources/AnimMeshEntityResource.h>
#include <KYEngine/Private/Resources/MeshEntityResource.h>
#include <KYEngine/Private/Resources/TextLayerEntityResource.h>

EntityFactory::EntityFactory()
{
}

Entity* EntityFactory::createAnimMeshEntity(const std::string& name, const std::string& animMeshCollectionRef, const Vector4& initialPos, double initialHPercent, const Vector4& color, const Vector4& scale, bool useBlending)
{
    AnimMeshEntityResource* result = new AnimMeshEntityResource();
    
    result->setName(name);
    result->setAnimMeshCollectionRef(animMeshCollectionRef);
    result->setInitialPos(initialPos);
    result->setInitialHPercent(initialHPercent);
    result->setColor(color);
    result->setScale(scale);
    result->setUseBlending(useBlending);
    
    result->load();
    
    return result;
}


Entity* EntityFactory::createMeshEntity(const std::string& name, const std::string& meshRef, const Vector4& initialPos, double initialHPercent, const Vector4& color, double angle, bool useBlending)
{
    MeshEntityResource* result = new MeshEntityResource();

	result->setName(name);
	result->setMeshRef(meshRef);
	result->setInitialPos(initialPos);
    result->setInitialHPercent(initialHPercent);
    result->setColor(color);
    result->setAngle(angle);
    result->setUseBlending(useBlending);

    result->load();
    
    return result;
}



Entity* EntityFactory::createTextLayerEntity(const std::string& name, const std::string& fontRef, double lineLength, double lineSpacing, AlignType align, const std::string& defaultText, const Vector4& pivot, const Vector4& borderColor, bool useBlending)
{
    TextLayerEntityResource* result = new TextLayerEntityResource();
	result->setName(name);
	result->setFontRef(fontRef);
	result->setLineLength(lineLength);
	result->setLineSpacing(lineSpacing);
	result->setAlign(align);
	result->setDefaultText(defaultText);
    result->setPivot(pivot);
    result->setBorderColor(borderColor);
	result->setInitialPos(Vector4());
    result->setUseBlending(useBlending);
    
    result->load();

    return result;
}
