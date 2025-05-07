#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QColor>
#include <QTimer>

#define FATIGUETIME 10000 //10 sek

enum Fatigue{fresh=0,slightly_tired=1,tired=2,sleepy=3};
enum TimeOfDay{morning,day,evening,night};

const QColor BACKGROUNDCOLORS[] = {QColor("#f22245"),QColor("#1cfc54"),QColor("#717ef5")};
const QColor TEXTCOLORS[] = {QColor("yellow"), QColor("red"), QColor("magenta")};



class Style : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(bool pulseActive READ pulseActive WRITE setPulseActive NOTIFY pulseActiveChanged FINAL)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged FINAL)
public:
    explicit Style(QObject* parent=nullptr, QColor color = "#ff12a8", QColor textColor = "#ebe534");

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
signals:
    void colorChanged();
    void pulseActiveChanged();
    void textColorChanged();
    void fatigueChanged();
public slots:
    void updateColor();
    void increaseFatigue();
    void decreaseFtigue();
private:

    QColor m_color;

    int m_fatigue;

    int m_timeOfDay;

    bool m_pulse;

    QColor m_textColor;

    QTimer* m_timer;

};

#endif // STYLE_H
