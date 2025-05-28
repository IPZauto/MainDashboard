#ifndef PLATFORMSERVER_H
#define PLATFORMSERVER_H

#include <QObject>
#include <QtWebSockets/QtWebSockets>
#include <QtWebSockets/QWebSocket>

#include "style.h"

class PlatformServer : public QObject {
    Q_OBJECT
public:
    explicit PlatformServer(QObject *parent = nullptr, Style* styl=nullptr);
    void connectToServer(const QUrl &url);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket socket;
    Style* m_styl;
};

#endif // PLATFORMSERVER_H
