#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    StMsg::pLog = ui->textBrowser_log;
    qDebug() << QSqlDatabase::drivers();
    DB = QSqlDatabase::addDatabase("QSQLITE", QString("STP-%1").arg(QDateTime::currentMSecsSinceEpoch()));
    DB.setDatabaseName("STP.db");
    if (!DB.open()){
        qDebug() << DB.lastError();
    }
}

MainWindow::~MainWindow()
{
    DB.close();
    delete ui;
}

