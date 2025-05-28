#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QCoreApplication>
#include <QColor>
#include <QTimer>

#define FATIGUETIME 10000 //10 sek

//konfiguracja timera z pliku

enum Fatigue{rapid =-1,fresh=0,slightly_tired,tired,sleepy}; //dodać rapid
enum TimeOfDay{morning,day,evening,night};

const QColor RAPID_BCK = QColor("green");
const QColor RAPID_TXT = QColor("blue");

const QVector<QColor> BACKGROUNDCOLORS = {QColor("#f22245"),QColor("#1cfc54"),QColor("#717ef5")};
const QVector<QColor> TEXTCOLORS = {QColor("yellow"), QColor("red"), QColor("magenta")};

const QColor b_default = "#ff12a8";
const QColor t_default = "#ebe534";

class Style : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(bool pulseActive READ pulseActive WRITE setPulseActive NOTIFY pulseActiveChanged FINAL)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged FINAL)
public:
    explicit Style(
        QObject* parent=nullptr, bool config = false,
        QColor color = b_default, QColor textColor = t_default, QVector<QColor> b_colors = BACKGROUNDCOLORS, QVector<QColor> t_colors = TEXTCOLORS,
        QColor r_color = RAPID_BCK, QColor r_text = RAPID_TXT,
        QVector<int> durations = QVector<int>(), QVector<int> sequence = QVector<int>(), int no_timers=0);

    //setter
    void setColor(const QColor);
    void setFatigue(const int);
    void setTimeOfDay(const int);
    void setPulseActive(const bool);
    void setTextColor(const QColor);
    //getter
    QColor color() const;

    QColor colorUpdate(const int fatigue,const int timeOfDay, const int expositionTime);

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
public slots:
    void updateColor();
    void increaseFatigue();
    void decreaseFatigue();
    void updateSequence();
private:

    QColor m_color;

    int m_fatigue;

    int m_timeOfDay;

    bool m_pulse;

    QColor m_textColor;

    QTimer* m_timer;

    int m_timerInterval;

    QColor m_rapid_bColor;

    QColor m_rapid_textColor;

    QVector<QColor> m_bColors;

    QVector<QColor> m_tColors;

    int m_no_timers;

    int m_curent_timer;

    QVector<int> m_durations;

    QVector<int> m_sequence;

    bool m_config;
};

#endif // STYLE_H
