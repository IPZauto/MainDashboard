#include "platformserver.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

PlatformServer::PlatformServer(QObject *parent, Style* styl)
    : QObject(parent), m_styl(styl)
{
    connect(this, &PlatformServer::urlChanged, this, &PlatformServer::connectToServerS);
    connect(&socket, &QWebSocket::connected, this, &PlatformServer::onConnected);
    connect(&socket, &QWebSocket::disconnected, this, &PlatformServer::onDisconnected);
    connect(&socket, &QWebSocket::textMessageReceived, this, &PlatformServer::onTextMessageReceived);
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &PlatformServer::onError);
}

void PlatformServer::connectToServer(const QUrl url)
{
    qDebug() << "Connecting to WebSocket server at:" << url;
    socket.open(url);
}

void PlatformServer::connectToServerS()
{
    QUrl url = QUrl(m_url);
    qDebug() << "Connecting to WebSocket server at:" << m_url;
    socket.open(url);
}

void PlatformServer::onConnected()
{
    qDebug() << "Connected to WebSocket server.";
}

void PlatformServer::onTextMessageReceived(QString message)
{
    qDebug() << "Received message:" << message;

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (!doc.isNull() && doc.isObject()) {
        QJsonObject obj = doc.object();
        QString type = obj["type"].toString();
        int value = obj["value"].toInt();

        if (type == "formData") {
            qDebug() << "Wybrano:" << value;
            m_styl->setFatigue(value);
        } else {
            qDebug() << "Inna wiadomość:" << message;
        }
    } else {
        qDebug() << "Tekst:" << message;
    }
}

void PlatformServer::onDisconnected()
{
    qDebug() << "WebSocket connection closed.";
}

void PlatformServer::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    qDebug() << "WebSocket error:" << socket.errorString();
}


void PlatformServer::setUrl(const QString url){
    m_url = url;
    emit urlChanged();
}

QString PlatformServer::url() const{
    return m_url;
}
