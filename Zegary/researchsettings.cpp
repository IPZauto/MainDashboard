#include "researchsettings.h"
#include <QFile>
#include <QSaveFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QUrl>
#include <cmath>

ResearchSettings::ResearchSettings(Style *style, QString path, QObject *parent)
    : QObject(parent), m_style(style), m_path(std::move(path)) {
    connect(&m_timer, &QTimer::timeout, this, &ResearchSettings::tick);
    m_timer.setTimerType(Qt::PreciseTimer);
}

QString ResearchSettings::validate(const QVariantMap &s) {
    const QRegularExpression hex("^#[0-9a-fA-F]{6}$");
    auto colorsValid = [&](const QVariantMap &v) {
        return hex.match(v.value("background").toString()).hasMatch()
            && hex.match(v.value("foreground").toString()).hasMatch();
    };
    if (!colorsValid(s) || !hex.match(s.value("baseBackground").toString()).hasMatch()
        || !hex.match(s.value("baseForeground").toString()).hasMatch())
        return "Colors must use #RRGGBB hex notation.";
    if (s.value("mode") != "manual" && s.value("mode") != "demo") return "Mode must be manual or demo.";
    if (!QStringList{"steady", "fade", "flash"}.contains(s.value("flash").toString())) return "Unknown flashing style.";
    for (const auto &key : {"fadeInMs", "holdMs", "fadeOutMs", "pauseMs"}) {
        bool ok = false;
        double n = s.value(key).toDouble(&ok);
        if (!ok || !std::isfinite(n) || n < 0 || n > 3600000 || n != std::floor(n))
            return QString("%1 must be a whole number from 0 to 3600000.").arg(key);
    }
    if (s.value("flash") != "steady" && (s.value("holdMs").toInt() == 0 || s.value("pauseMs").toInt() == 0))
        return "Flashing requires positive hold and pause durations.";
    for (const auto &key : {"debug", "release", "demoLoop"})
        if (s.value(key).metaType().id() != QMetaType::Bool) return QString("%1 must be true or false.").arg(key);
    const QString address = s.value("websocketUrl").toString();
    QUrl url(address);
    if (!address.isEmpty() && (!url.isValid() || url.host().isEmpty() || (url.scheme() != "ws" && url.scheme() != "wss")))
        return "WebSocket URL must start with ws:// or wss:// and contain a host.";
    const auto steps = s.value("demoSteps").toList();
    if (steps.isEmpty()) return "Provide at least one demo step.";
    for (const auto &entry : steps) {
        const auto step = entry.toMap();
        bool ok = false;
        double duration = step.value("durationMs").toDouble(&ok);
        if (!colorsValid(step) || !ok || !std::isfinite(duration) || duration < 1 || duration > 3600000 || duration != std::floor(duration))
            return "Each demo step needs hex background/foreground and durationMs from 1 to 3600000.";
    }
    return {};
}

bool ResearchSettings::fail(QString message) {
    m_error = std::move(message);
    emit errorChanged();
    return false;
}

bool ResearchSettings::load() {
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly)) return fail(file.errorString());
    QJsonParseError error;
    const auto doc = QJsonDocument::fromJson(file.readAll(), &error);
    if (error.error != QJsonParseError::NoError || !doc.isObject()) return fail("Invalid config JSON: " + error.errorString());
    auto s = doc.object().toVariantMap();
    const auto problem = validate(s);
    if (!problem.isEmpty()) return fail(problem);
    install(s);
    return true;
}

void ResearchSettings::install(const QVariantMap &s) {
    const QString previousUrl = m_settings.value("websocketUrl").toString();
    m_settings = s;
    m_error.clear();
    m_clock.restart();
    emit settingsChanged();
    emit errorChanged();
    if (previousUrl != s.value("websocketUrl").toString()) emit websocketUrlChanged(s.value("websocketUrl").toString());
    tick();
    m_timer.start(16);
}

bool ResearchSettings::apply(const QVariantMap &s) {
    if (!debug()) return fail("Live editing is disabled. Enable debug in the config and restart.");
    const auto problem = validate(s);
    if (!problem.isEmpty()) return fail(problem);
    install(s);
    return true;
}

bool ResearchSettings::save(const QVariantMap &s) {
    if (!debug()) return fail("Live editing is disabled.");
    const auto problem = validate(s);
    if (!problem.isEmpty()) return fail(problem);
    QSaveFile file(m_path);
    if (!file.open(QIODevice::WriteOnly)) return fail(file.errorString());
    const auto bytes = QJsonDocument(QJsonObject::fromVariantMap(s)).toJson();
    if (file.write(bytes) != bytes.size() || !file.commit()) return fail(file.errorString());
    install(s);
    return true;
}

bool ResearchSettings::setWebsocketUrl(const QString &url) {
    auto s = m_settings;
    s["websocketUrl"] = url.trimmed();
    const auto problem = validate(s);
    if (!problem.isEmpty()) return fail(problem);
    install(s);
    return true;
}

void ResearchSettings::tick() {
    auto s = m_settings;
    qint64 elapsed = m_clock.elapsed();
    if (!remote() && s.value("mode") == "demo") {
        const auto steps = s.value("demoSteps").toList();
        qint64 total = 0;
        for (const auto &entry : steps) total += entry.toMap().value("durationMs").toLongLong();
        if (s.value("demoLoop").toBool()) elapsed %= total;

        for (qsizetype index = 0; index < steps.size(); ++index) {
            const auto step = steps[index].toMap();
            const auto duration = step.value("durationMs").toLongLong();
            if (elapsed < duration || index == steps.size() - 1) {
                s["background"] = step.value("background");
                s["foreground"] = step.value("foreground");
                break;
            }
            elapsed -= duration;
        }
    }
    QColor bg = remote() ? m_style->color() : QColor(s.value("background").toString());
    QColor fg = remote() ? m_style->textColor() : QColor(s.value("foreground").toString());
    QString effect = s.value("flash").toString();
    if (remote() && !m_style->pulseActive()) effect = "steady";
    double amount = 1;
    if (effect != "steady") {
        qint64 fadeIn = effect == "fade" ? s.value("fadeInMs").toInt() : 0;
        qint64 fadeOut = effect == "fade" ? s.value("fadeOutMs").toInt() : 0;
        qint64 hold = s.value("holdMs").toInt(), pause = s.value("pauseMs").toInt();
        qint64 t = elapsed % (fadeIn + hold + fadeOut + pause);
        if (t < fadeIn) amount = double(t) / fadeIn;
        else if (t < fadeIn + hold) amount = 1;
        else if (t < fadeIn + hold + fadeOut) amount = 1 - double(t - fadeIn - hold) / fadeOut;
        else amount = 0;
    }
    auto blend = [amount](QColor base, QColor target) {
        return QColor::fromRgbF(base.redF() + (target.redF()-base.redF())*amount,
                                base.greenF() + (target.greenF()-base.greenF())*amount,
                                base.blueF() + (target.blueF()-base.blueF())*amount);
    };
    bg = blend(QColor(s.value("baseBackground").toString()), bg);
    fg = blend(QColor(s.value("baseForeground").toString()), fg);
    if (bg != m_background || fg != m_foreground) {
        m_background = bg; m_foreground = fg;
        emit appearanceChanged();
    }
}
