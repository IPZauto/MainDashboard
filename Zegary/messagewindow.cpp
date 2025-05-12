#include "messagewindow.h"

MessageWindow::MessageWindow(QObject *parent)
    : QObject{parent}
{
    alertT = new QTimer(this);
    connect(this, &MessageWindow::alertChanged, this, &MessageWindow::startTheTimer);
    connect(alertT, &QTimer::timeout, this, &MessageWindow::resetAlert);
    connect(this,&MessageWindow::alertReseted,this,&MessageWindow::stopTheTimer);    alert = 0;
    m_message = MESSAGES[0];
    m_iconSrc = ICONS[0];
}

//getters
QString MessageWindow::icon() const{
    return m_iconSrc;
}

QString MessageWindow::message() const{
    return m_message;
}

//setters

void MessageWindow::setMessage(const QString mes){
    m_message = mes;
    emit messageChanged();
}

void MessageWindow::setIcon(const QString ic){
    m_iconSrc = ic;
    emit iconChanged();
}

void MessageWindow::setAlert(const int alertNum){
    if (alertNum==alert) return;
    if(alertNum <=0 || alertNum > Alerts::damage) return;
    alert = alertNum;
    setMessage(MESSAGES[alert]);
    setIcon(ICONS[alert]);
    emit alertChanged();
}

void MessageWindow::resetAlert(){
    if (alert == Alerts::empty) return;
    alert = Alerts::empty;
    setMessage(MESSAGES[alert]);
    setIcon(ICONS[alert]);
    emit alertReseted();
}

void MessageWindow::startTheTimer(){
    alertT->start(ALERTTIME * 1000);
}

void MessageWindow::stopTheTimer(){
    alertT->stop();
}
