#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>

struct Placement
{
    float x;        // X coordinate in the world
    float y;        // Y coordinate in the world
    float z;        // Z coordinate in the world
    float heading;  // The angle is measured counterclockwise in horizontal plane
                    // when looking from top where 0 corresponds to forward (north),
                    // 0.25 to left (west), 0.5 to backward (south) and 0.75 to right (east).
                    // Stored in unit range where (0,1) corresponds to (0,360).

    float pitch;    // The pitch angle is zero when in horizontal direction,
                    // with positive values pointing up (0.25 directly to zenith),
                    // and negative values pointing down (-0.25 directly to nadir).
                    // Stored in unit range where (-0.25,0.25) corresponds to (-90,90).

    float roll;     // The angle is measured in counterclockwise
                    // when looking in direction of the roll axis.
                    // Stored in unit range where (-0.5,0.5) corresponds to (-180,180).
};

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(int engineRPM READ rpm WRITE setRpm NOTIFY rpmChanged FINAL)
    Q_PROPERTY(int engineRPMmax READ maxRpm WRITE setMaxRpm NOTIFY maxRpmChanged FINAL)
    Q_PROPERTY(bool fuelWarningOn READ fuelWarningOn WRITE setFuelWarningOn NOTIFY fuelWarningOnChanged FINAL)
    Q_PROPERTY(bool parkBrakeOn READ parkBrakeOn WRITE setParkBrakeOn NOTIFY parkBrakeOnChanged FINAL)
    Q_PROPERTY(bool blinkerRightActive READ blinkerRightActive WRITE setBlinkerRightActive NOTIFY blinkerRightActiveChanged FINAL)
    Q_PROPERTY(bool blinkerLeftActive READ blinkerLeftActive WRITE setBlinkerLeftActive NOTIFY blinkerLeftActiveChanged FINAL)
    Q_PROPERTY(bool lightsOn READ lightsOn WRITE setLightsOn NOTIFY lightsOnChanged FINAL)
    Q_PROPERTY(bool highBeamOn READ highBeamOn WRITE setHighBeamOn NOTIFY highBeamOnChanged FINAL)

public:
    explicit Game(QObject *parent = nullptr){
        GameInfo.placement.x=0.0;
        GameInfo.placement.y=0.0;
        GameInfo.placement.z=0.0;
        GameInfo.placement.heading=0.0;
        GameInfo.placement.pitch=0.0;
        GameInfo.placement.roll=0.0;
        GameInfo.connected=false;
        GameInfo.paused=true;
        GameInfo.date="1 sty 2025 00:00:00";
        setSpeed(0);
        setRpm(0);
        setMaxRpm(0);
        setFuelWarningOn(false);
        setBlinkerLeftActive(false);
        setBlinkerRightActive(false);
        setHighBeamOn(false);
        Truck.lightsDashboardValue=0.0;
        setParkBrakeOn(false);
        setLightsOn(false);
    };

    // settery
    void setPlacement(
                    const float x,
                    const float y,
                    const float z,
                    const float heading,
                    const float pitch,
                    const float roll
        );
    void setConnected(const bool);

    void setPaused(const bool);

    void setDate(const QString);

    void setSpeed(const int);

    void setRpm(const int);

    void setMaxRpm(const int);

    void setFuelWarningOn(const bool);

    void setParkBrakeOn(const bool);

    void setLDV(const float);

    void setBlinkerRightActive(const bool);

    void setBlinkerLeftActive(const bool);

    void setLightsOn(const bool);

    void setHighBeamOn(const bool);

    // gettery

    Placement placement() const;
    bool conneted() const;
    bool paused() const;
    QString date() const;

    int speed() const;
    int rpm() const;
    int maxRpm() const;
    bool fuelWarningOn() const;
    bool parkBrakeOn() const;
    float getLdv() const;
    bool blinkerRightActive() const;
    bool blinkerLeftActive() const;
    bool lightsOn() const;
    bool highBeamOn() const;


signals:
    void speedChanged();
    void rpmChanged();
    void maxRpmChanged();
    void fuelWarningOnChanged();
    void parkBrakeOnChanged();
    void blinkerLeftActiveChanged();
    void blinkerRightActiveChanged();
    void lightsOnChanged();
    void highBeamOnChanged();

private:
    struct GameInfo{
        Placement placement;

        bool connected;     // indicates wheater the telemetry server is connected to the game

        bool paused;        // true if game is currently paused, false otherwise

        QString date;

    }GameInfo;

    struct Truck{
        int speed;        // truck speed

        int engineRPM;    // truck RPM

        int engineRPMmax;

        bool fuelWarningOn;

        bool parkBrakeOn;

        float lightsDashboardValue;

        bool blinkerRightActive;
        bool blinkerLeftActive;  //if both true hazard lights are on

        bool lightsOn;
        bool highBeamOn;

    }Truck;

};



#endif // GAME_H
