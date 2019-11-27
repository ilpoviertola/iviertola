#include <iostream>
#include <fstream>
#include <QDebug>
#include <string>

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->findPushButton, SIGNAL(clicked(bool)), this, SLOT(read_file()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_file()
{
    ui->textBrowser->clear();
    std::string line = "";
    std::vector<std::string> fields = {};
    int words_found = 0;

    QString file_name_qstr = ui->fileLineEdit->text();
    std::string file_name = file_name_qstr.toStdString();
    std::ifstream file(file_name);

    if(file.is_open()){
        if(not ui->keyLineEdit->text().isEmpty()){
            std::string searcing_for = ui->keyLineEdit->text().toStdString();

            while(getline(file, line)){
                split(line, fields, ' ');
                for( std::string field : fields ){
                    if( not ui->matchCheckBox->isChecked() ){
                        std::for_each(field.begin(), field.end(), [](char & c){
                            c = ::toupper(c);
                        });
                        std::for_each(searcing_for.begin(), searcing_for.end(), [](char & c){
                            c = ::toupper(c);
                        });
                    }
                    if( field == searcing_for ){
                        ++ words_found;
                    }
                }
            }
            if(words_found){ui->textBrowser->append(QString::fromStdString("Word found"));}
            else {ui->textBrowser->append(QString::fromStdString("Word not found"));}

        } else {
            ui->textBrowser->append(QString::fromStdString("File found"));
        }
    } else {
        ui->textBrowser->append(QString::fromStdString("File not found"));
    }

}

void MainWindow::split(const std::string& line, std::vector<std::string>& result,
           char separator){
    result.clear();
    result.push_back("");
    for ( char c : line ){
        if ( c == separator ){
            result.push_back("");
        } else {
            result.back().push_back(c);
        }
    }

    if ( result.size() > 0 && result.back() == "" ){
        result.erase(--result.end());
    }
}
