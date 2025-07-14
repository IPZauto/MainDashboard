/// module responsible for everything connected with the colors side of the screen.
/// There are 2 ways of operating it:
/// - web socket connected to procjrct responsible for fatigue increase
/// - config file (not implemnted yet)

#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QCoreApplication>
#include <QColor>
#include <QTimer>

// enums responsible for driver's fatigue and Time of day used for background and text colors
enum Fatigue{rapid =-1,fresh=0,slightly_tired,tired,sleepy};
enum TimeOfDay{day=0,evening,night};

// default colors for rapid fatigue for each time of day.
// BCK -> background color
// TXT -> text color
// D -> day
// E -> evening
// N -> night
const QColor RAPID_BCKD = QColor("white");
const QColor RAPID_BCKE = QColor("gray");
const QColor RAPID_BCKN = QColor("black");
const QColor RAPID_TXTD = QColor("black");
const QColor RAPID_TXTE = QColor("magenta");
const QColor RAPID_TXTN = QColor("white");


// background colors for fatigues in order excluding fresh and rapid
const QVector<QColor> BACKGROUNDCOLORSD = {QColor("white"),QColor("yellow"),QColor("yellow")};
const QVector<QColor> BACKGROUNDCOLORSE = {QColor("gray"), QColor("gray"),  QColor("gray")};
const QVector<QColor> BACKGROUNDCOLORSN = {QColor("black"),QColor("black"), QColor("blue")};

// text colors for fatigues in order excluding fresh and rapid
const QVector<QColor> TEXTCOLORSD = {QColor("blue"),  QColor("blue"),   QColor("black")};
const QVector<QColor> TEXTCOLORSE = {QColor("white"), QColor("yellow"), QColor("green")};
const QVector<QColor> TEXTCOLORSN = {QColor("green"), QColor("yellow"), QColor("yellow")};

// background and text color for fresh state
const QColor b_default = "#151414";
const QColor t_default = "#e8e8e8";

class Style : public QObject
{
    Q_OBJECT
    // Q_Properties used for communication with QML
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(bool pulseActive READ pulseActive WRITE setPulseActive NOTIFY pulseActiveChanged FINAL)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged FINAL)
public:
    explicit Style(
        QObject* parent=nullptr, bool config = false,
        QColor color = b_default, QColor textColor = t_default,
        QVector<QColor> b_colorsD = BACKGROUNDCOLORSD, QVector<QColor> t_colorsD = TEXTCOLORSD,
        QVector<QColor> b_colorsE = BACKGROUNDCOLORSE, QVector<QColor> t_colorsE = TEXTCOLORSE,
        QVector<QColor> b_colorsN = BACKGROUNDCOLORSN, QVector<QColor> t_colorsN = TEXTCOLORSN,
        QColor r_colorD = RAPID_BCKD, QColor r_textD = RAPID_TXTD,
        QColor r_colorE = RAPID_BCKE, QColor r_textE = RAPID_TXTE,
        QColor r_colorN = RAPID_BCKN, QColor r_textN = RAPID_TXTN,
        QVector<int> durations = QVector<int>(), QVector<int> sequence = QVector<int>(), int no_timers=0);

    //setter
    void setColor(const QColor);
    void setFatigue(const int);
    void setTimeOfDay(const int);
    void setPulseActive(const bool);
    void setTextColor(const QColor);
    //getter
    QColor color() const;

    // QColor colorUpdate(const int fatigue,const int timeOfDay, const int expositionTime);

    int fatigue() const;

    int timeOfDay() const;

    bool pulseActive() const;

    QColor textColor() const;
    //changes timer interval of sending a signal to perform an action
    void setInterval(int time);
    // starts the timer
    void start();
    // stops the timer
    void stop();
    // return state of a timer (active or not)
    bool isTimerRunning()const;
signals:
    void colorChanged();
    void pulseActiveChanged();
    void textColorChanged();
    void fatigueChanged();
    void timerRunningChanged();
    void intervalChanged();
    void timeOfDayChanged();
public slots:
    void updateColor();
    void increaseFatigue();
    void decreaseFatigue();
    void updateSequence();
    void updateTimeOfDay(int tod);
private:

    QColor m_color;

    int m_fatigue;

    int m_timeOfDay;

    bool m_pulse;

    QColor m_textColor;

    QTimer* m_timer;

    int m_timerInterval;

    QColor m_rapid_bColorD;

    QColor m_rapid_textColorD;

    QColor m_rapid_bColorE;

    QColor m_rapid_textColorE;

    QColor m_rapid_bColorN;

    QColor m_rapid_textColorN;

    QVector<QColor> m_bColorsD;

    QVector<QColor> m_tColorsD;

    QVector<QColor> m_bColorsN;

    QVector<QColor> m_tColorsN;

    QVector<QColor> m_bColorsE;

    QVector<QColor> m_tColorsE;

    int m_no_timers;

    int m_curent_timer;

    QVector<int> m_durations;

    QVector<int> m_sequence;

    bool m_config;

    int m_tod; //TIME OF DAY
};

#endif // STYLE_H
