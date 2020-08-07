#ifndef VSSREFEREE_H
#define VSSREFEREE_H

#include <src/entity/vssvisionclient/vssvisionclient.h>
#include <include/vssref_command.pb.h>
#include <include/vssref_placement.pb.h>

#include <QtCore>
#include <QUdpSocket>
#include <include/timer.h>

#define PLACEMENT_WAIT_TIME 10.0  // seconds
#define GAME_HALF_TIME      300   // seconds
#define GK_TIME_TAKEOUT     10.0  // seconds

class VSSReferee : public Entity
{
    Q_OBJECT
public:
    VSSReferee(VSSVisionClient *visionClient, const QString& refereeAddress, int refereePort);
    ~VSSReferee();
    QString name();

    // Network
    bool connect(const QString& refereeAddress, int refereePort);
    void disconnect();
    bool isConnected() const;

private:
    void initialization();
    void loop();
    void finalization();

    // Socket to send foul data
    QUdpSocket _socket;
    QString _refereeAddress;
    int _refereePort;
    VSSRef::ref_to_team::VSSRef_Command _refereeCommand;
    void sendPacket(VSSRef::ref_to_team::VSSRef_Command command);

    // VSSVisionClient to receive data from FIRASim
    VSSVisionClient *_visionClient;

    // Foul name by id
    QString getFoulNameById(VSSRef::Foul foul);

    // Foul placement analysis
    Timer _placementTimer;
    bool _yellowSent;
    bool _blueSent;
    bool _placementIsSet;
    QMutex _placementMutex;

    bool alreadySet;

    // Game time analysis
    Timer _gameTimer;
    int timePassed;

    /// FOULS

    // Utils
    bool isInsideGoalArea(VSSRef::Color teamColor, vector2d pos);

    // Penalty foul analysis
    bool checkPenalty();

    // GK alone with ball analysis
    bool checkGKTakeout();
    Timer _gkTimer;
    bool startedGKTimer;

signals:
    void setFoul(VSSRef::Foul foul);        // send foul to replacer (reset it vars)

public slots:
    void teamSent(VSSRef::Color color);     // if a team sent it packet
};

#endif // VSSREFEREE_H
