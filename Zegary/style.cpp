#include "style.h"

Style::Style(QObject *parent, QColor color): QObject{parent}, m_color{color} {}

void Style::setColor(const QColor color){
    if (m_color==color) return;
    m_color=color;
    emit colorChanged();
}

QColor Style::color() const { return m_color; }

void Style::updateColor(const QColor color){
    setColor(color);
}

QColor Style::colorUpdate(const int fatigue, const int timeOfDay){
    // to do
    return QColor("red");
}

void Style::setFatigue(const int fatigue){
    m_fatigue = fatigue;
}

void Style::setTimeOfDay(const int timeOfDay){
    m_timeOfDay = timeOfDay;
}
