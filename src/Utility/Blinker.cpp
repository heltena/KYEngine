#include <KYEngine/Utility/Blinker.h>

Blinker::Blinker()
{
}

Blinker::~Blinker()
{
}

void Blinker::init(double minValue, double maxValue, double celerity)
{
    init(minValue, maxValue, minValue, celerity);
}

void Blinker::init(double minValue, double maxValue, double initValue, double celerity)
{
    m_minValue = minValue;
    m_maxValue = maxValue;
    m_value = initValue;
    m_celerity = celerity;
    m_growing = true;
}

void Blinker::update(const double elapsedTime)
{
    double remainValue = elapsedTime * m_celerity;
    while (remainValue > 0) {
        if (m_growing) {
            m_value += remainValue;
            if (m_value < m_maxValue)
                remainValue = 0;
            else {
                remainValue = m_value - m_maxValue;
                m_value = m_maxValue;
                m_growing = false;
            }
        } else {
            m_value -= remainValue;
            if (m_value > m_minValue)
                remainValue = 0;
            else {
                remainValue = m_minValue - m_value;
                m_value = m_minValue;
                m_growing = true;
            }
        }
    }
}
