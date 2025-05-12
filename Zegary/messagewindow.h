#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QObject>
#include <QTimer>

#define ALERTTIME 5 //alert time in seconds

const QString MESSAGES[] = {"","Bad wheather\n slow down","Find a place to stop\nYou need a break","You have damage\n Repair your vehicle"};
const QString ICONS[] = {"","images/WheatherWarning.svg"};
enum Alerts{empty =0, wheater, coffeBreak, damage};
class MessageWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged FINAL)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
public:
    explicit MessageWindow(QObject *parent = nullptr);
    // getters
    QString message() const;
    QString icon() const;
    //setters
    void setMessage(const QString mes);
    void setIcon(const QString ic);
    void setAlert(const int);

signals:
    void messageChanged();
    void iconChanged();
    void alertChanged();
    void alertReseted();

private slots:
    void startTheTimer();
    void stopTheTimer();
    void resetAlert();
private:
    QString m_message;
    QString m_iconSrc;
    int alert = 0;
    QTimer* alertT = nullptr;
};

#endif // MESSAGEWINDOW_H
