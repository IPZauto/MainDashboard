// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include "autogen/environment.h"
#include "game.h"
#include "networkdata.h"
#include "style.h"
#include "messagewindow.h"
#include "platformserver.h"

const QString dConfigPath = ":/config/config.json";

int main(int argc, char *argv[])
{
    set_qt_environment();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QString execPath = QCoreApplication::applicationDirPath();
    QString configFolder = execPath + "/config";
    QString destPath = configFolder + "config.json";
    QString configFilePath = destPath;
    // config file logic
    if(!QFile(destPath).exists()){
        configFilePath = dConfigPath;
        QDir dir;
        if (!dir.exists(configFolder)) {
            dir.mkpath(configFolder);
        }
        if (QFile::copy(dConfigPath, destPath)) {
            qDebug() << "Copied config.json to:" << destPath;
        } else {
            qWarning() << "Failed to copy config.json!";
        }
    }
    // Reading
    bool config = false;
    int timers = 0;
    QVector<int> durations;
    QVector<QColor> bcolors;
    QVector<QColor> tcolors;
    QColor rapidBColors;
    QColor rapidTCOlors;
    QVector<int> fatigue;
    QFile configFile(configFilePath);
    if (configFile.open(QIODevice::ReadOnly)) {
        QByteArray data = configFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(!doc.isNull()){
            QJsonObject rootObject = doc.object();
            QJsonObject setup = rootObject["setup"].toObject();
            config = setup["config"].toBool();
            timers = setup["timers"].toInt();
            QJsonArray jDurations = setup["durations"].toArray();
            for (const QJsonValue& value : jDurations){
                durations.push_back(value.toInt());
            }
            if(durations.length()!=timers) {
                qDebug() << "wrong config file";
                return -1;
            }
            QJsonArray jbColors = setup["bcolors"].toArray();
            for (const QJsonValue& value : jbColors){
                bcolors.push_back(QColor(value.toString()));
            }
            if(bcolors.length()!=3) {
                qDebug() << "wrong config file";
                return -1;
            }
            QJsonArray jtColors = setup["tcolors"].toArray();
            for (const QJsonValue& value : jtColors){
                tcolors.push_back(QColor(value.toString()));
            }
            if(tcolors.length()!=3) {
                qDebug() << "wrong config file";
                return -1;
            }
            rapidBColors = QColor(setup["rbcolors"].toString());
            rapidTCOlors = QColor(setup["rtcolors"].toString());
            QJsonArray jfatigue = setup["fatigue"].toArray();
            for (const QJsonValue& value : jfatigue){
                fatigue.push_back(value.toInt());
            }
            if(fatigue.length()!=timers) {
                qDebug() << "wrong config file";
                return -1;
            }
        }
        configFile.close();
    }

    Game backend;

    NetworkData network(&app,TELEMETREY_URL,&backend);

    Style* styl;
    if(config){
        styl = new Style(&app,config, b_default, t_default, bcolors, tcolors, rapidBColors, rapidTCOlors, durations, fatigue, timers);
    }else{
        styl = new Style(&app);
    }

    MessageWindow message;

    PlatformServer ps(&app, styl);
    ps.connectToServer(Surl);

    qDebug() << "i am here";

    QObject::connect(&backend, &Game::TruckDamaged, &message, &MessageWindow::damagedTruck);

    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("styl", styl);
    engine.rootContext()->setContextProperty("network",&network);
    engine.rootContext()->setContextProperty("message", &message);

    const QUrl url(mainQmlFile);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    backend.setBlinkerLeftActive(true);
    backend.setBlinkerRightActive(true);
    backend.setBatteryVoltageWarningOn(true);
    backend.setFuelWarningOn(true);
    backend.setCsOn(true);
    backend.setCsSpeed(40);
    backend.setSpeed(40);
    backend.setRpm(2500);
    backend.setGear(4);
    backend.setLightsOn(true);

    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
