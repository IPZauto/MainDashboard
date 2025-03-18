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
public:
    explicit Style(QObject* parent=nullptr, QColor color = "#151414");

    //setter
    void setColor(const QColor);
    void setFatigue(const int);
    void setTimeOfDay(const int);
    //getter
    QColor color() const;

    QColor colorUpdate(const int fatigue,const int timeOfDay);

    int fatigue() const;

    int timeOfDay() const;
signals:
    void colorChanged();

public slots:
    void updateColor(const QColor color);

private:

    QColor m_color;

    int m_fatigue;

    int m_timeOfDay;
};

#endif // STYLE_H
