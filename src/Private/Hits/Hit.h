#pragma once

#include <KYEngine/Utility/Vector4.h>

#include <string>

class Entity;
class HitTransform;
class RenderLayer;

class Hit
{
private:
    enum StateEnum {
        APPEAR,
        SHOWING,
        FINISHED
    };
    
public:
    Hit();
    virtual ~Hit();
    
public:
    void init(RenderLayer* layer, const Vector4& pos, double duration, const std::string& animMeshCollectionRef, const std::string& animRef, double delay = 0, HitTransform* transform = NULL, bool controlTransformLifeCycle = true);
    void done();
    void update(const double elapsedTime);
    bool isFinished() const { return m_state == FINISHED; }
    
private:
    void updateAppear(const double elapsedTime);
    void updateShowing(const double elapsedTime);
    
private:
    StateEnum m_state;
    RenderLayer* m_layer;
    Entity* m_entity;
    bool m_controlTransformLifeCycle;
    HitTransform* m_transform;
    double m_timeout;
    double m_duration;
};
