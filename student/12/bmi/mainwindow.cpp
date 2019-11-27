#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->countButton, SIGNAL(clicked(bool)), this, SLOT(calculate_bmi()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_bmi()
{
    QString weight_qstr = ui->weightLineEdit->text();
    QString height_qstr = ui->heightLineEdit->text();

    if(not height_qstr.isEmpty() && not weight_qstr.isEmpty()){
        ui->infoTextBrowser->clear();

        double weight = weight_qstr.toDouble();
        double height = height_qstr.toDouble() / 100;

        double bmi = weight / ( height * height );
        QString bmi_qstr = QString::number(bmi);

        ui->resultLabel->setText(bmi_qstr);

        if( bmi > 0 && bmi <= 18.5 ){
            ui->infoTextBrowser->append(QString::fromStdString("You are underweight."));
        } else if ( bmi > 18.5 && bmi < 25 ){
            ui->infoTextBrowser->append(QString::fromStdString("Your weight is normal."));
        } else if ( bmi >= 25 ){
            ui->infoTextBrowser->append(QString::fromStdString("You are overweight."));
        }
    }
}
