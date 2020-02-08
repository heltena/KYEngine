#include <KYEngine/Core.h>
#include <KYEngine/TextLayerExtension.h>
#include <KYEngine/Private/AchievementPage.h>
#include <KYEngine/Factories/EntityFactory.h>
#include <KYEngine/Mesh.h>

AchievementPage::AchievementPage()
    : m_state(DEACTIVATED)
    , m_layer(NULL)
    , m_backgroundEntity(NULL)
    , m_textEntity(NULL)
    , m_appearDuration(0)
    , m_showingDuration(0)
    , m_disappearDuration(0)
    , m_timeout(0)
{
}

AchievementPage::~AchievementPage()
{
    done();
}

void AchievementPage::init(const Vector4& hidePos, const Vector4& showPos, const std::string& meshRef, const std::string& fontRef, double lineLength, double lineSpacing, AlignType align, const Vector4& pivot, const Vector4& borderColor, double appearDuration, double showingDuration, double disappearDuration, double accelMagnitude)
{
    if (m_state != DEACTIVATED)
        throw std::runtime_error("AchievementPageManager::init: it's singleton");
        
    m_layer = Core::renderManager().createLayer("#AchievementPage", 20);

    Mesh* mesh = Core::resourceManager().mesh(meshRef);
    if (mesh == NULL)
        throw std::runtime_error("AchievementPageManager::init: mesh not found");

    m_hidePos = hidePos;
    m_showPos = showPos;

    m_backgroundEntity = EntityFactory::createMeshEntity("#AchievementPageBackground", meshRef);
    m_textEntity = EntityFactory::createTextLayerEntity("#AchievementPageText", fontRef, lineLength, lineSpacing, align, "", pivot, borderColor, true);
    m_layer->addEntity(m_backgroundEntity, true);
    m_layer->addEntity(m_textEntity, true);

    
    m_backgroundEntity->setPos(m_hidePos);
    m_textEntity->setPos(m_hidePos);

    m_appearDuration = appearDuration;
    m_showingDuration = showingDuration;
    m_disappearDuration = disappearDuration;
    m_accelMagnitude = accelMagnitude;
    
    startHide();
}

void AchievementPage::done()
{
    if (m_state == DEACTIVATED)
        return;
    startHide();
    Core::renderManager().removeLayer("#AchievementPage"); 
    m_layer = NULL;
    m_backgroundEntity = NULL; // deleted by layer
    m_textEntity = NULL; // deleted by layer
}

void AchievementPage::update(const double elapsedTime)
{
    switch(m_state) {
    case DEACTIVATED:
        break;
    case HIDE:
        updateHide(elapsedTime);
        break;
    case APPEARING:
        updateAppearing(elapsedTime);
        break;
    case SHOWING:
        updateShowing(elapsedTime);
        break;
    case DISAPPEARING:
        updateDisappearing(elapsedTime);
        break;
    }
}

void AchievementPage::pushNewMessage(const std::string& message)
{
    m_messages.push_back(message);
    if (m_state == HIDE)
        testForNewMessage();
}

void AchievementPage::updateHide(const double elapsedTime)
{
}

void AchievementPage::updateAppearing(const double elapsedTime)
{
    m_timeout -= elapsedTime;
    Vector4 newPos = Vector4::interpolate(m_hidePos, m_showPos, 1 - m_timeout / m_appearDuration, m_accelMagnitude);
    m_backgroundEntity->setPos(newPos);
    m_textEntity->setPos(newPos);
    if (m_timeout <= 0)
        startShowing();
}

void AchievementPage::updateShowing(const double elapsedTime)
{
    m_timeout -= elapsedTime;
    if (m_timeout <= 0)
        startDisappearing();
}

void AchievementPage::updateDisappearing(const double elapsedTime)
{
    m_timeout -= elapsedTime;
    Vector4 newPos = Vector4::interpolate(m_showPos, m_hidePos, 1 - m_timeout / m_disappearDuration, m_accelMagnitude);
    m_backgroundEntity->setPos(newPos);
    m_textEntity->setPos(newPos);
    if (m_timeout <= 0)
        testForNewMessage();
}

void AchievementPage::startHide()
{
    m_state = HIDE;
    m_layer->hide();
}

void AchievementPage::startAppearing()
{
    m_state = APPEARING;
    m_layer->show();
    m_timeout = m_appearDuration;
}

void AchievementPage::startShowing()
{
    m_state = SHOWING;
    m_layer->show();
    m_timeout = m_showingDuration;
}

void AchievementPage::startDisappearing()
{
    m_state = DISAPPEARING;
    m_timeout = m_disappearDuration;
}

void AchievementPage::testForNewMessage()
{
    if (m_messages.size() == 0)
        startHide();
    else {
        m_textEntity->textLayerInterface()->setText(m_messages.front());
        m_messages.pop_front();
        startAppearing();
    }
}
