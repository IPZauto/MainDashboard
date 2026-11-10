// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include <QtQml/QQmlExtensionPlugin>

Q_IMPORT_QML_PLUGIN(ZegaryContentPlugin)
#include "game.h"
#include "networkdata.h"
#include "style.h"
#include "researchsettings.h"
#include "messagewindow.h"
#include "platformserver.h"

const QString dConfigPath = ":/config/config.json";

int main(int argc, char *argv[])
{
    qputenv("QML_COMPAT_RESOLVE_URLS_ON_ASSIGNMENT", "1");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "0");
    qputenv("QT_LOGGING_RULES", "qt.qml.connections=false");
    qputenv("QT_QUICK_CONTROLS_CONF", ":/qtquickcontrols2.conf");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QString configFolder = QCoreApplication::applicationDirPath() + "/config";
    const QString configPath = QDir(configFolder).filePath("config.json");
    if (!QFile::exists(configPath)) {
        if (!QDir().mkpath(configFolder) || !QFile::copy(dConfigPath, configPath)) {
            qCritical() << "Cannot create config:" << configPath;
            return 1;
        }
        QFile::setPermissions(configPath, QFile::permissions(configPath) | QFileDevice::WriteOwner);
    }
    Game backend;
    NetworkData network(&app, TELEMETREY_URL, &backend);
    Style *styl = new Style(&app);
    ResearchSettings research(styl, configPath);
    MessageWindow message;

    PlatformServer ps(&app, styl);
    QObject::connect(&research, &ResearchSettings::websocketUrlChanged, &ps, &PlatformServer::setUrl);
    if (!research.load()) {
        qCritical() << "Config error in" << configPath << research.error();
        return 1;
    }
    engine.rootContext()->setContextProperty("research", &research);

    QObject::connect(&backend, &Game::TruckDamaged, &message, &MessageWindow::damagedTruck);
    QObject::connect(&backend, &Game::timeOfDayChanged, styl, &Style::updateTimeOfDay);

    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("styl", styl);
    engine.rootContext()->setContextProperty("network",&network);
    engine.rootContext()->setContextProperty("message", &message);
    engine.rootContext()->setContextProperty("webSocket", &ps);

    const QUrl url(QStringLiteral("qrc:/qt/qml/ZegaryContent/App.qml"));
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);


    if (engine.rootObjects().isEmpty())
        return -1;

    // backend.setBatteryVoltageWarningOn(true);
    backend.setSpeed(70);
    // backend.setCsSpeed(120);
    // backend.setCsOn(true);
    backend.setGear(5);
    backend.setRpm(2500);
    backend.setBlinkerLeftActive(true);
    backend.setLightsOn(true);
    message.setAlert(1);


    return app.exec();
}
