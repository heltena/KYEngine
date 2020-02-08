#pragma once

#include <KYEngine/Platform.h>
#include <KYEngine/RenderLayer.h>

#include <KYEngine/Managers/RenderDebugListener.h>

#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/FPSCounter.h>
#include <KYEngine/Utility/Vector4.h>

#include <map>
#include <set>
#include <string>

class AchievementPage;
class Core;
class RenderLayerImpl;

class RenderManager
{
private:
	friend class Core;
	RenderManager();
	virtual ~RenderManager();

private:
	void init();
	void update(const double elapsedTime);
	void render();

private:
    struct SortRenderLayers
	{
		bool operator()(const RenderLayerImpl* lhs, const RenderLayerImpl* rhs) const;
	};

public:
	RenderLayer* createLayer(const std::string& name, int zorder);
	bool containsLayer(const std::string& name);
	RenderLayer* layer(const std::string& name);
	void removeLayer(const std::string& name);
    
    void addRenderDebugListener(RenderDebugListener* listener);
    void removeRenderDebugListener(RenderDebugListener* listener);

public:
    double width() const { return 960.0; }
    double height() const { return 640.0; }
    const Box& screenBounds() const { return m_screenBounds; }

// Achievement page  
public:
    void initAchievementPage(const Vector4& hidePos, const Vector4& showPos, const std::string& meshRef, const std::string& fontRef, double lineLength, double lineSpacing, AlignType align, const Vector4& pivot, const Vector4& borderColor, double appearDuration, double showingDuration, double disappearDuration, double accelMagnitude);
    void doneAchievementPage();
    void showAchievementPage(const std::string& message);
    
private:
    FPSCounter m_fpsCounter;
    std::multiset<RenderLayerImpl*, SortRenderLayers> m_orderedLayers;
	std::map<std::string, RenderLayerImpl*> m_layers;
    Box m_screenBounds;
    
    std::set<RenderDebugListener*> m_debugListeners;

    AchievementPage* m_achievementPage;
};
