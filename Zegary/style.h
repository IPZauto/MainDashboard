#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QColor>

class Style : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
public:
    explicit Style(QObject* parent=nullptr, QColor color = "#151414");

    //setter
    void setColor(const QColor);

    //getter
    QColor color() const;

signals:
    void colorChanged();

public slots:
    void updateColor(const QColor color);

private:
    QColor m_color;
};

#endif // STYLE_H
