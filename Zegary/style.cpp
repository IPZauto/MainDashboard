#include "style.h"

Style::Style(QObject* parent, bool config,
             QColor color, QColor textColor, QVector<QColor> b_colors, QVector<QColor> t_colors,
             QColor r_color, QColor r_text,
             QVector<int> durations , QVector<int> sequence , int no_timers):
    QObject{parent}, m_config{config},
    m_color{color}, m_textColor{textColor},m_bColors{b_colors},m_tColors{t_colors},
    m_no_timers{no_timers}, m_durations{durations}, m_sequence{sequence}
{
    m_pulse=false;
    m_fatigue = 0;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Style::updateSequence);
    connect(this , &Style::fatigueChanged, this, &Style::updateColor);
    if (config){
        m_curent_timer = 0;
        m_timer->setInterval(durations[m_curent_timer] * 1000);
        m_timer->start();
    }
}

//increases Fatigue with check
void Style::increaseFatigue(){
    if(m_fatigue==sleepy) return;
    m_fatigue++;
    if(!m_pulse) setPulseActive(true);
    emit fatigueChanged();
}
//decreases Fatigue with check
void Style::decreaseFatigue(){
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
    if (m_fatigue==rapid){
        setColor(m_rapid_bColor);
        setTextColor(m_rapid_textColor);
    }
    else{
        setColor(m_bColors[m_fatigue-1]);
        setTextColor(m_tColors[m_fatigue-1]);
    }
}

void Style::setFatigue(const int fatigue){
    if ( fatigue == rapid || fatigue <= sleepy && fatigue >= fresh)
    {
        m_fatigue = fatigue;
        if ((fatigue == rapid||fatigue > fresh) && !m_pulse) setPulseActive(true);
        emit fatigueChanged();
    }
    return;
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

void Style::setInterval(int time){
    m_timer->setInterval(time);
    emit intervalChanged();
}

void Style::start(){
    m_timer->start(m_timerInterval);
    emit timerRunningChanged();
}

void Style::stop(){
    m_timer->stop();
    emit timerRunningChanged();
}

bool Style::isTimerRunning() const{return m_timer->isActive();}

void Style::updateSequence() {
    m_curent_timer ++;
    if(m_curent_timer>=m_no_timers){
        m_timer->stop();
        return;
    }
    setFatigue(m_sequence[m_curent_timer]);
    m_timer->setInterval(m_durations[m_curent_timer] * 1000);
    m_timer->start();
}
