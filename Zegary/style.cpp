#include "style.h"

Style::Style(QObject *parent, QColor color, QColor textColor): QObject{parent}, m_color{color}, m_textColor{textColor} {
    m_pulse=false;
    m_fatigue = 0;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Style::increaseFatigue);
    connect(this , &Style::fatigueChanged, this, &Style::updateColor);


    m_timer->start(FATIGUETIME);
}

//increases Fatigue with check
void Style::increaseFatigue(){
    if(m_fatigue==sleepy) return;
    m_fatigue++;
    if(!m_pulse) setPulseActive(true);
    emit fatigueChanged();
}
//decreases Fatigue with check
void Style::decreaseFtigue(){
    if(m_fatigue==fresh) {
        if(m_pulse) setPulseActive(false);
        return;
    }
    m_fatigue--;
    emit fatigueChanged();
}

// sets background color
void Style::setColor(const QColor color){
    if (m_color==color) return;
    m_color=color;
    emit colorChanged();
}
// sets text color
void Style::setTextColor(const QColor color){
    if (m_color==color) return;
    m_textColor=color;
    emit textColorChanged();
}

QColor Style::color() const { return m_color; }

QColor Style::textColor() const {return m_textColor;}

bool Style::pulseActive() const {return m_pulse;}

//updates color after fatigue has changed
void Style::updateColor(){
    setColor(BACKGROUNDCOLORS[m_fatigue-1]);
    setTextColor(TEXTCOLORS[m_fatigue-1
    ]);
}


QColor Style::colorUpdate(const int fatigue, const int timeOfDay, const int expositionTime){
    // to do
    return QColor("red");
}

void Style::setFatigue(const int fatigue){
    m_fatigue = fatigue;
}

void Style::setTimeOfDay(const int timeOfDay){
    m_timeOfDay = timeOfDay;
}

//activates pulsating background effect
void Style::setPulseActive(const bool pa){
    if (m_pulse==pa) return;
    m_pulse = pa;
    emit pulseActiveChanged();
}

