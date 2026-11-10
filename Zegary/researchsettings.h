#pragma once
#include <QObject>
#include <QVariantMap>
#include <QColor>
#include <QElapsedTimer>
#include <QTimer>
#include "style.h"

class ResearchSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap settings READ settings NOTIFY settingsChanged)
    Q_PROPERTY(bool debug READ debug NOTIFY settingsChanged)
    Q_PROPERTY(bool remote READ remote NOTIFY settingsChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(QColor background READ background NOTIFY appearanceChanged)
    Q_PROPERTY(QColor foreground READ foreground NOTIFY appearanceChanged)
public:
    ResearchSettings(Style *style, QString path, QObject *parent = nullptr);
    QVariantMap settings() const { return m_settings; }
    bool debug() const { return m_settings.value("debug").toBool(); }
    bool remote() const { return !m_settings.value("websocketUrl").toString().isEmpty(); }
    QString error() const { return m_error; }
    QColor background() const { return m_background; }
    QColor foreground() const { return m_foreground; }
    bool load();
    Q_INVOKABLE bool apply(const QVariantMap &settings);
    Q_INVOKABLE bool save(const QVariantMap &settings);
    Q_INVOKABLE bool setWebsocketUrl(const QString &url);
    static QString validate(const QVariantMap &settings);
signals:
    void settingsChanged();
    void errorChanged();
    void appearanceChanged();
    void websocketUrlChanged(QString url);
private:
    void install(const QVariantMap &settings);
    void tick();
    bool fail(QString error);
    Style *m_style;
    QString m_path, m_error;
    QVariantMap m_settings;
    QColor m_background, m_foreground;
    QElapsedTimer m_clock;
    QTimer m_timer;
};
