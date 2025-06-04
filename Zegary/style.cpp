#include "style.h"

Style::Style(QObject* parent, bool config,
             QColor color, QColor textColor,
             QVector<QColor> b_colorsD, QVector<QColor> t_colorsD,
             QVector<QColor> b_colorsE, QVector<QColor> t_colorsE,
             QVector<QColor> b_colorsN, QVector<QColor> t_colorsN,
             QColor r_colorD, QColor r_textD,
             QColor r_colorE, QColor r_textE,
             QColor r_colorN, QColor r_textN,
             QVector<int> durations , QVector<int> sequence , int no_timers):
    QObject{parent}, m_config{config},
    m_color{color}, m_textColor{textColor},
    m_bColorsD{b_colorsD},m_tColorsD{t_colorsD},
    m_bColorsE{b_colorsE},m_tColorsE{t_colorsE},
    m_bColorsN{b_colorsN},m_tColorsN{t_colorsN},
    m_rapid_bColorD{r_colorD}, m_rapid_textColorD{r_textD},
    m_rapid_bColorE{r_colorE}, m_rapid_textColorE{r_textE},
    m_rapid_bColorN{r_colorN}, m_rapid_textColorN{r_textN},
    m_no_timers{no_timers}, m_durations{durations}, m_sequence{sequence}
{
    m_pulse=false;
    m_fatigue = 0;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Style::updateSequence);
    connect(this , &Style::fatigueChanged, this, &Style::updateColor);
    connect(this, &Style::timeOfDayChanged,this, &Style::updateColor);
    if (config){
        m_curent_timer = 0;
        m_timer->setInterval(durations[m_curent_timer] * 1000);
        m_timer->start();
    }
    m_tod = 0;
}

void Style::updateTimeOfDay(int tod){
    m_tod = tod;
    emit timeOfDayChanged();
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
        switch (m_tod) {
        case day:
            setColor(m_rapid_bColorD);
            setTextColor(m_rapid_textColorD);
            break;
        case evening:
            setColor(m_rapid_bColorE);
            setTextColor(m_rapid_textColorE);
            break;
        case night:
            setColor(m_rapid_bColorN);
            setTextColor(m_rapid_textColorN);
            break;
        }

    }
    else{
        switch(m_tod){
        case day:
            setColor(m_bColorsD[m_fatigue-1]);
            setTextColor(m_tColorsD[m_fatigue-1]);
            break;

        case evening:
            setColor(m_bColorsE[m_fatigue-1]);
            setTextColor(m_tColorsE[m_fatigue-1]);
            break;

        case night:
            setColor(m_bColorsN[m_fatigue-1]);
            setTextColor(m_tColorsN[m_fatigue-1]);
            break;
        }


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
