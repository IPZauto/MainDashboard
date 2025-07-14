#ifndef PLATFORMSERVER_H
#define PLATFORMSERVER_H

#include <QObject>
#include <QtWebSockets/QtWebSockets>
#include <QtWebSockets/QWebSocket>

#include "style.h"

// const QUrl Surl= QUrl("ws://192.168.56.1:8080");
const QUrl Surl= QUrl("ws://172.20.10.2:8080");

class PlatformServer : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged FINAL)
public:
    explicit PlatformServer(QObject *parent = nullptr, Style* styl=nullptr);
    void setUrl(const QString);
    QString url()const;
    void connectToServer(QUrl);

signals:
    void urlChanged();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void connectToServerS();

private:
    QString m_url;
    QWebSocket socket;
    Style* m_styl;
};

#endif // PLATFORMSERVER_H
