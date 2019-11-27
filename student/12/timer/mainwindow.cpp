#include <QDebug>

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mins_(0), secs_(0)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(start_clock()));

    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(start_timer()));
    connect(ui->resetButton, SIGNAL(clicked(bool)), this, SLOT(reset_clock()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stop_clock()));

    ui->lcdNumberMin->setPalette(Qt::red);
    ui->lcdNumberMin->setAutoFillBackground(true);
    ui->lcdNumberSec->setPalette(Qt::green);
    ui->lcdNumberSec->setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::start_timer()
{
    timer->start(1000);
    ui->startButton->setDisabled(true);
}

void MainWindow::start_clock()
{
    ++secs_;
    if( secs_ == 60 ){
        secs_ = 0;
        mins_ = 1;
        ui->lcdNumberMin->display(mins_);
        ui->lcdNumberSec->display(secs_);
    } else {
        ui->lcdNumberSec->display(secs_);
    }
}

void MainWindow::stop_clock()
{
    timer->stop();
    ui->startButton->setEnabled(true);
}

void MainWindow::reset_clock()
{
    secs_ = 0;
    mins_ = 0;
    ui->lcdNumberMin->display(mins_);
    ui->lcdNumberSec->display(secs_);
}
