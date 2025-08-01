#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QTextBrowser>
#include <QDebug>
#include <chrono>
#include <sstream>
#include <iterator>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

#include "CubeView.h"
#include "CubeModel.h"
#include "Solver.h"
#include "movesimplify.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void resetBtnHandle();
    void scrambleBtnHandle();
    void solveBtnHandle();
    void applySolveBtnHandle();

    void connectArduinoURB();
    void connectArduinoDLF();
    void disconnectArduinoURB();
    void disconnectArduinoDLF();
    void scrambleHW();
    void solveHW();
    void sendCommandsHW(std::vector<std::string>);
    void sendMoveHW(char URB_command, char DLF_command);

    void FBtnHandle();
    void FprimeBtnHandle();
    void BBtnHandle();
    void BprimeBtnHandle();
    void UBtnHandle();
    void UprimeBtnHandle();
    void DBtnHandle();
    void DprimeBtnHandle();
    void LBtnHandle();
    void LprimeBtnHandle();
    void RBtnHandle();
    void RprimeBtnHandle();
    void F2BtnHandle();
    void B2BtnHandle();
    void U2BtnHandle();
    void D2BtnHandle();
    void L2BtnHandle();
    void R2BtnHandle();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    CubeView *cubeView;
    CubeModel cube;
    Solver* solver;
    std::vector<std::string> scrambleState;
    MoveSimplify moveSimplify;

    QSerialPort *serial_urb;
    QSerialPort *serial_dlf;
    QSerialPortInfo info;
};
#endif // MAINWINDOW_H
