#pragma once

class Blinker
{
public:
    Blinker();
    virtual ~Blinker();
  
public:
    void init(double minValue, double maxValue, double celerity);
    void init(double minValue, double maxValue, double initValue, double celerity);

    void update(const double elapsedTime);
    
    double value() const { return m_value; }

private:
    double m_minValue;
    double m_maxValue;
    double m_value;
    double m_celerity;
    bool m_growing;
};