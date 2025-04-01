#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QColor>

enum Fatigue{fresh,slightly_tired,tired,sleepy};
enum TimeOfDay{morning,day,evening,night};

class Style : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(bool pulseActive READ pulseActive WRITE setPulseActive NOTIFY pulseActiveChanged FINAL)
public:
    explicit Style(QObject* parent=nullptr, QColor color = "#ff12a8");

    //setter
    void setColor(const QColor);
    void setFatigue(const int);
    void setTimeOfDay(const int);
    void setPulseActive(const bool);
    //getter
    QColor color() const;

    QColor colorUpdate(const int fatigue,const int timeOfDay);

    int fatigue() const;

    int timeOfDay() const;

    bool pulseActive() const;
signals:
    void colorChanged();
    void pulseActiveChanged();

public slots:
    void updateColor(const QColor color);

private:

    QColor m_color;

    int m_fatigue;

    int m_timeOfDay;

    bool m_pulse;
};

#endif // STYLE_H
