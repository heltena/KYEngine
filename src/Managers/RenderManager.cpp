#include <KYEngine/Core.h>

#include <KYEngine/Private/AchievementPage.h>
#include <KYEngine/Private/RenderLayerImpl.h>

#include <KYEngine/Managers/RenderManager.h>

#include <KYEngine/Utility/DirectionEnum.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <stdexcept>

RenderManager::RenderManager()
    : m_screenBounds(0, 0, 960, 640)
    , m_achievementPage(NULL)
    , m_fpsCounter(0.250)
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrthof(0, 960, 640, 0, -100.0f, 100.0f);
    
    glEnable(GL_LINE_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_NOTEQUAL, 0);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendEquationSeparateOES(GL_ADD, GL_FUNC_REVERSE_SUBTRACT_OES);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepthf(1);
}

void RenderManager::update(const double elapsedTime)
{
    /*if (m_fpsCounter.update(elapsedTime)) {
        double fps = m_fpsCounter.fps();
    }*/

	for(std::map<std::string, RenderLayerImpl*>::iterator it = m_layers.begin(); it != m_layers.end(); it++)
		it->second->update(elapsedTime);
    if (m_achievementPage)
        m_achievementPage->update(elapsedTime);
}

void RenderManager::render()
{	
//    m_fpsCounter.rendered();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
/* Lo que había antes
	// TODO: optimize this matrix mult
	GLfloat aspect = 960.0f / 640.0;
    glScalef(aspect, 1.0f / aspect, 1.0f);
	glRotatef(-90.0f, 0, 0, 1);
	glScalef(1.0f, -1.0f, 1.0f);
    glTranslatef(-960, -640, 0);
	// TODO: end of optimize
*/
    glScalef(1.0f, -1.0f, 1.0f);
    glTranslatef(0, -640, 0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::multiset<RenderLayerImpl*, SortRenderLayers>::iterator it = m_orderedLayers.begin(); it != m_orderedLayers.end(); it++) {
        RenderLayerImpl* layer = *it;
        glClear(GL_DEPTH_BUFFER_BIT);
        layer->render();
    }
    
    glClear(GL_DEPTH_BUFFER_BIT);
    for(std::set<RenderDebugListener*>::const_iterator it = m_debugListeners.begin(); it != m_debugListeners.end(); it++) {
        RenderDebugListener* listener = *it;
        listener->debugRender();
    }
}


bool RenderManager::SortRenderLayers::operator()(const RenderLayerImpl* lhs, const RenderLayerImpl* rhs) const
{
	return lhs->zorder() < rhs->zorder();
}

RenderLayer* RenderManager::createLayer(const std::string& name, int zorder)
{
#ifdef DEBUG 
	if (m_layers.find(name) != m_layers.end())
		throw std::runtime_error("Layer exists: " + name);
#endif
    RenderLayerImpl* result = new RenderLayerImpl(name, zorder);
    m_layers[name] = result;
    m_orderedLayers.insert(result);
    return result;
}

bool RenderManager::containsLayer(const std::string& name)
{
    return m_layers.find(name) != m_layers.end();
}

RenderLayer* RenderManager::layer(const std::string& name)
{
#ifdef DEBUG
	if (m_layers.find(name) == m_layers.end())
		throw std::runtime_error("Layer not created: " + name);
#endif
	return m_layers[name];
}

void RenderManager::removeLayer(const std::string& name)
{
#ifdef DEBUG
	if (m_layers.find(name) == m_layers.end())
		throw std::runtime_error("Layer not created before: " + name);
#endif
    RenderLayerImpl* toKill = m_layers[name];
    // TODO: optimize it, m_orderedLayers.erase(toKill); doesn't work
    std::multiset<RenderLayerImpl*, SortRenderLayers>::iterator it = m_orderedLayers.begin();
    while (it != m_orderedLayers.end() && *it != toKill)
        it++;
    if (it != m_orderedLayers.end())
        m_orderedLayers.erase(it);
    toKill->eraseOwnEntities();
	m_layers.erase(name);
    delete toKill;
}

void RenderManager::addRenderDebugListener(RenderDebugListener* listener)
{
    m_debugListeners.insert(listener);
}

void RenderManager::removeRenderDebugListener(RenderDebugListener* listener)
{
    m_debugListeners.erase(listener);
}


void RenderManager::initAchievementPage(const Vector4& hidePos, const Vector4& showPos, const std::string& meshRef, const std::string& fontRef, double lineLength, double lineSpacing, AlignType align, const Vector4& pivot, const Vector4& borderColor, double appearDuration, double showingDuration, double disappearDuration, double accelMagnitude)
{
    if (m_achievementPage != NULL)
        throw std::runtime_error("AchievementManager::init: cannot init again");
    m_achievementPage = new AchievementPage();
    m_achievementPage->init(hidePos, showPos, meshRef, fontRef, lineLength, lineSpacing, align, pivot, borderColor, appearDuration, showingDuration, disappearDuration, accelMagnitude);
}

void RenderManager::doneAchievementPage()
{
    if (m_achievementPage == NULL)
        return;
    m_achievementPage->done();
    delete m_achievementPage;
    m_achievementPage = NULL;
}

void RenderManager::showAchievementPage(const std::string& message)
{
    if (m_achievementPage)
        m_achievementPage->pushNewMessage(message);
}
