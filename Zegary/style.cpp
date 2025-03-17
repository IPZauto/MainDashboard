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
