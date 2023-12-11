#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add cube to the scene
    scene = new QGraphicsScene(0,0,600,400);
    cubeView = new CubeView(scene, QString::fromStdString(cube.toString()));
    ui->cubeView->setScene(scene);

    //Set up push buttons
    connect(ui->resetBtn, &QPushButton::released, this, &MainWindow::resetBtnHandle);
    connect(ui->scrambleBtn, &QPushButton::released, this, &MainWindow::scrambleBtnHandle);
    connect(ui->solveBtn, &QPushButton::released, this, &MainWindow::solveBtnHandle);
    connect(ui->applySolveMovesBtn, &QPushButton::released, this, &MainWindow::applySolveBtnHandle);

    connect(ui->connectURBBtn,  &QPushButton::released, this, &MainWindow::connectArduinoURB);
    connect(ui->connectDLFBtn,  &QPushButton::released, this, &MainWindow::connectArduinoDLF);
    connect(ui->disconnectURBBtn,  &QPushButton::released, this, &MainWindow::disconnectArduinoURB);
    connect(ui->disconnectDLFBtn,  &QPushButton::released, this, &MainWindow::disconnectArduinoDLF);

    // Ports
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->URBcomboBox->addItems(stringPorts);
    ui->DLFcomboBox->addItems(stringPorts);
    serial_urb = new QSerialPort();
    serial_dlf = new QSerialPort();

    connect(ui->scrambleHWBtn,  &QPushButton::released, this, &MainWindow::scrambleHW);
    connect(ui->solveHWBtn,  &QPushButton::released, this, &MainWindow::solveHW);

    connect(ui->FBtn, &QPushButton::released, this, &MainWindow::FBtnHandle);
    connect(ui->FprimeBtn, &QPushButton::released, this, &MainWindow::FprimeBtnHandle);
    connect(ui->BBtn, &QPushButton::released, this, &MainWindow::BBtnHandle);
    connect(ui->BprimeBtn, &QPushButton::released, this, &MainWindow::BprimeBtnHandle);
    connect(ui->UBtn, &QPushButton::released, this, &MainWindow::UBtnHandle);
    connect(ui->UprimeBtn, &QPushButton::released, this, &MainWindow::UprimeBtnHandle);
    connect(ui->DBtn, &QPushButton::released, this, &MainWindow::DBtnHandle);
    connect(ui->DprimeBtn, &QPushButton::released, this, &MainWindow::DprimeBtnHandle);
    connect(ui->LBtn, &QPushButton::released, this, &MainWindow::LBtnHandle);
    connect(ui->LprimeBtn, &QPushButton::released, this, &MainWindow::LprimeBtnHandle);
    connect(ui->RBtn, &QPushButton::released, this, &MainWindow::RBtnHandle);
    connect(ui->RprimeBtn, &QPushButton::released, this, &MainWindow::RprimeBtnHandle);
    connect(ui->F2Btn, &QPushButton::released, this, &MainWindow::F2BtnHandle);
    connect(ui->B2Btn, &QPushButton::released, this, &MainWindow::B2BtnHandle);
    connect(ui->U2Btn, &QPushButton::released, this, &MainWindow::U2BtnHandle);
    connect(ui->D2Btn, &QPushButton::released, this, &MainWindow::D2BtnHandle);
    connect(ui->L2Btn, &QPushButton::released, this, &MainWindow::L2BtnHandle);
    connect(ui->R2Btn, &QPushButton::released, this, &MainWindow::R2BtnHandle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetBtnHandle()
{
    ui->scrambleMovesText->setText("");
    ui->currCubeStateText->setText("");
    ui->numSolveMovesText->setText("");
    ui->solutionMovesText->setText("");
    ui->solveTimeText->setText("0.0");
    ui->HWsolveTimeLabel->setText("0.0");
    ui->numSolveMovesText->setText("0");
//    ui->numSimpleMoves->setText("0");

    cubeView->setCube(QString::fromStdString(cube.reset()));
}

void MainWindow::scrambleBtnHandle()
{
    scrambleState = cube.scramble(int(ui->scrambleMovesNumSpinBox->value()));
    std::ostringstream imploded;
    std::copy(scrambleState.begin(), scrambleState.end(),
              std::ostream_iterator<std::string>(imploded, " "));
    ui->scrambleMovesText->setText(QString::fromStdString(imploded.str()));
    ui->currCubeStateText->setText(QString::fromStdString((cube.toString())));
    cubeView->setCube(QString::fromStdString(cube.toString()));
}

void MainWindow::solveBtnHandle()
{
    //solve the cube
    solver = new Solver();
    std::vector<std::string> temp = cube.getSolverOutput();
    auto start = std::chrono::high_resolution_clock::now();
    solver->solve(temp);
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

    //output the solution
    std::vector<std::string> solved = solver->getSolveMoves();
    QString output = "";
    for (unsigned int i = 0; i < solved.size(); i++) {
        output = output + QString::fromStdString(solved[i]) + " ";
    }

//    moveSimplify.simplify(solved);
    ui->solutionMovesText->setText(output);
//    ui->simplifiedSolutionText->setText(QString::fromStdString(moveSimplify.getSolveMovesString()));
    ui->solveTimeText->setText(QString::number(microseconds.count()/1000.0));
    ui->numSolveMovesText->setText(QString::number(solved.size()));
//    ui->numSimpleMoves->setText(QString::number(moveSimplify.getSolveMoves().size()));
}

void MainWindow::applySolveBtnHandle()
{
    std::vector<std::string> solved = solver->getSolveMoves();
    std::vector<CubeModel::MOVE> moves = moveSimplify.getSolveMovesCube(solved);
    for (unsigned int i = 0; i < moves.size(); i++) {
        cube.move(moves[i]);
    }
    cubeView->setCube(QString::fromStdString(cube.toString()));
    ui->currCubeStateText->setText(QString::fromStdString(cube.toString()));

}


void MainWindow::connectArduinoURB()
{
    serial_urb->setPortName(ui->URBcomboBox->currentText());
    serial_urb->setBaudRate(QSerialPort::Baud9600);
    serial_urb->setDataBits(QSerialPort::Data8);
    serial_urb->setParity(QSerialPort::NoParity);
    serial_urb->setStopBits(QSerialPort::OneStop);
    serial_urb->setFlowControl(QSerialPort::NoFlowControl);
    serial_urb->open(QIODevice::ReadWrite);
    if (serial_urb->isOpen()) {
        ui->URBconnectedCheckBox->setChecked(true);
    }
    else {
        QMessageBox::critical(this, tr("Error"), serial_urb->errorString());
    }
}

void MainWindow::connectArduinoDLF()
{
    serial_dlf->setPortName(ui->DLFcomboBox->currentText());
    serial_dlf->setBaudRate(QSerialPort::Baud9600);
    serial_dlf->setDataBits(QSerialPort::Data8);
    serial_dlf->setParity(QSerialPort::NoParity);
    serial_dlf->setStopBits(QSerialPort::OneStop);
    serial_dlf->setFlowControl(QSerialPort::NoFlowControl);
    serial_dlf->open(QIODevice::ReadWrite);
    if (serial_dlf->isOpen()) {
        ui->DLFconnectedCheckBox->setChecked(true);
    }
    else {
        QMessageBox::critical(this, tr("Error"), serial_dlf->errorString());
    }
}

void MainWindow::disconnectArduinoURB()
{
    serial_urb->close();
    if (!serial_urb->isOpen()){
        ui->URBconnectedCheckBox->setChecked(false);
    }
}
void MainWindow::disconnectArduinoDLF()
{
    serial_dlf->close();
    if (!serial_dlf->isOpen()){
        ui->DLFconnectedCheckBox->setChecked(false);
    }
}
void MainWindow::scrambleHW()
{
    this->sendCommandsHW(scrambleState);
}

void MainWindow::solveHW()
{
    auto start = std::chrono::high_resolution_clock::now();
    this->sendCommandsHW(moveSimplify.getSolveMoves());
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    ui->HWsolveTimeLabel->setText(QString::number(microseconds.count()/1000.0/1000.0));
}

void MainWindow::sendCommandsHW(std::vector<std::string> movesToMake)
{

    std::string urb_options = "uUzrRxbBc";
    std::string dlf_options = "dDvlLnfFm";

    for (unsigned int i=0; i < movesToMake.size(); i++)
    {
        char urb_command = '?';
        char dlf_command = '?';
        char curr_command = '&';

        if (movesToMake[i] == "U") { curr_command = 'u'; }
        else if (movesToMake[i] == "U'") { curr_command = 'U'; }
        else if (movesToMake[i] == "U2") { curr_command = 'z'; }
        else if (movesToMake[i] == "R") { curr_command = 'r'; }
        else if (movesToMake[i] == "R'") { curr_command = 'R'; }
        else if (movesToMake[i] == "R2") { curr_command = 'x'; }
        else if (movesToMake[i] == "B") { curr_command = 'b'; }
        else if (movesToMake[i] == "B'") { curr_command = 'B'; }
        else if (movesToMake[i] == "B2") { curr_command = 'c'; }
        else if (movesToMake[i] == "D") { curr_command = 'd'; }
        else if (movesToMake[i] == "D'") { curr_command = 'D'; }
        else if (movesToMake[i] == "D2") { curr_command = 'v'; }
        else if (movesToMake[i] == "L") { curr_command = 'l'; }
        else if (movesToMake[i] == "L'") { curr_command = 'L'; }
        else if (movesToMake[i] == "L2") { curr_command = 'n'; }
        else if (movesToMake[i] == "F") { curr_command = 'f'; }
        else if (movesToMake[i] == "F'") { curr_command = 'F'; }
        else if (movesToMake[i] == "F2") { curr_command = 'm'; }

        if (urb_options.find(curr_command) != std::string::npos)
        {
            urb_command = curr_command;
        }
        if (urb_command == '?' && (dlf_options.find(curr_command) != std::string::npos))
        {
            dlf_command = curr_command;
        }
        this->sendMoveHW(urb_command, dlf_command);
    }
}


void MainWindow::sendMoveHW(char URB_command, char DLF_command)
{
    if (URB_command != '?' && serial_urb->isOpen())
    {
        serial_urb->write(&URB_command);
        serial_urb->waitForReadyRead();
    }
    if (DLF_command != '?' && serial_dlf->isOpen())
    {
        serial_dlf->write(&DLF_command);
        serial_dlf->waitForReadyRead();
    }
}

void MainWindow::FBtnHandle()
{
    cube.f();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"F"};
        this->sendCommandsHW(vect);
    }
}

void MainWindow::FprimeBtnHandle()
{
    cube.fPrime();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"F'"};
        this->sendCommandsHW(vect);
    }
}

void MainWindow::BBtnHandle() {
    cube.b();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"B"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::BprimeBtnHandle(){
    cube.bPrime();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"B'"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::UBtnHandle(){
    cube.u();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"U"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::UprimeBtnHandle(){
    cube.uPrime();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"U'"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::DBtnHandle(){
    cube.d();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"D"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::DprimeBtnHandle(){
    cube.dPrime();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"D'"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::LBtnHandle(){
    cube.l();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"L"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::LprimeBtnHandle(){
    cube.lPrime();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"L'"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::RBtnHandle(){
    cube.r();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"R"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::RprimeBtnHandle(){
    cube.rPrime();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"R'"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::F2BtnHandle(){
    cube.f2();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"F2"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::B2BtnHandle(){
    cube.b2();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"B2"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::U2BtnHandle(){
    cube.u2();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"U2"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::D2BtnHandle(){
    cube.d2();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"D2"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::L2BtnHandle(){
    cube.l2();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"L2"};
        this->sendCommandsHW(vect);
    }
}
void MainWindow::R2BtnHandle(){
    cube.r2();
    cubeView->setCube(QString::fromStdString(cube.toString()));

    if (ui->performOnHWCheckBox->isChecked()) {
        vector<std::string> vect{"R2"};
        this->sendCommandsHW(vect);
    }
}
