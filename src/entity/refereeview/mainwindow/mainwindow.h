#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <src/entity/refereeview/soccerview/soccerview.h>
#include <include/vssref_common.pb.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent);
    ~MainWindow();

    // Detection updates
    void updateDetection(fira_message::Frame frame);

    // Referee
    void addRefereeCommand(QString command);
    void addRefereeWarning(QString command);
    void setCurrentTime(int time);
    void setRefereeCommand(QString command);
    bool getBlueIsLeftSide() { return blueIsLeft; }

    // GUI
    void drawText(vector2d pos, char *str);
    void setTeams(QString teamLeft, VSSRef::Color leftColor, QString teamRight, VSSRef::Color rightColor);

private:
    Ui::MainWindow *ui;

    // sides control
    bool blueIsLeft;
    QString leftTeamName;
    QString rightTeamName;

    // goal control
    int leftTeamGoalsScored;
    int rightTeamGoalsScored;

public slots:
    void switchSides();
    void addGoal(VSSRef::Color team);
};

#endif // MAINWINDOW_H
