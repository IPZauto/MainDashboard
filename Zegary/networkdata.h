#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTimer>
#include "game.h"

const QString TELEMETREY_URL = "http://192.168.18.36:25555/api/ets2/telemetry";

class NetworkData : public QObject
{
    Q_OBJECT
public:
    explicit NetworkData(QObject *parent = nullptr, QString url = TELEMETREY_URL, Game *game = nullptr);
    ~NetworkData();
private:
    Game *m_gameData;
    QUrl m_url;
    QNetworkAccessManager *m_manager;
    QTimer *m_timer;
private slots:
    void fetchTelemetryData();
};

#endif // NETWORKDATA_H
