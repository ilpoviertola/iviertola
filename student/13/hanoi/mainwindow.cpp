#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // We need a graphics scene in which to initialize gameboard.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates:
    int left_margin = 10; // x coordinate
    int top_margin = 270; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    setup_gameboard();

    connect(&timer_, &QTimer::timeout, this, &MainWindow::start_animation);
    connect(ui_->newGameButton, SIGNAL(clicked(bool)), this, SLOT(new_game()));
    connect(ui_->AtoBbutton, SIGNAL(clicked(bool)), this, SLOT(A_to_B()));
}

MainWindow::~MainWindow()
{
    delete ui_;

    for( Disk* disk : peg_A_ ){
        delete disk;
        disk = nullptr;
    }

    for( Disk* disk : peg_B_ ){
        delete disk;
        disk = nullptr;
    }

    for( Disk* disk : peg_C_ ){
        delete disk;
        disk = nullptr;
    }
}

void MainWindow::setup_gameboard()
{
    qreal disk_width = 20 * DISK_AMOUNT;
    qreal disk_height = 10;
    qreal disk_x = 170 - DISK_AMOUNT * 10;
    qreal disk_y = 250 - disk_height;

    qreal peg_width = 10;
    qreal peg_height = 220;

    QBrush black_brush(Qt::black);
    QBrush green_brush(Qt::green);
    QPen black_pen(Qt::black);
    QPen yellow_pen(Qt::yellow);

    // Ground for the gameboard.
    scene_->addRect(0, 250, 680, 10, yellow_pen, black_brush);

    // Create pegs.
    for( int i = 1; i < 4; ++i ){
        scene_->addRect(( i * (BORDER_RIGHT / 4) ) - ( peg_width / 2 ) , 30, peg_width, peg_height, yellow_pen, black_brush);
    }

    //Create as many disks as wanted.
    for( int i = 0; i < DISK_AMOUNT; ++i){
        QGraphicsRectItem* disk = scene_->addRect(disk_x, disk_y, disk_width, disk_height, black_pen, green_brush);
        Disk* new_disk = new Disk(disk, disk_width, disk_x, disk_y);
        peg_A_.push_back(new_disk);
        disk_y -= disk_height;
        disk_x += 10;
        disk_width -= 20;
    }
}

void MainWindow::new_game()
{
    scene_->clear();

    for( Disk* disk : peg_A_ ){
        delete disk;
        disk = nullptr;
    }

    peg_A_.clear();

    for( Disk* disk : peg_B_ ){
        delete disk;
        disk = nullptr;
    }

    peg_B_.clear();

    for( Disk* disk : peg_C_ ){
        delete disk;
        disk = nullptr;
    }

    peg_C_.clear();

    setup_gameboard();
}

void MainWindow::start_animation()
{
    if(x_left_ != 0){
        disk_to_move_->get_disk()->moveBy(STEP, 0);
        x_left_ -= STEP;
    }
    else if(y_left_ != 0){
        disk_to_move_->get_disk()->moveBy(0, STEP);
        y_left_ -= STEP;
    }
    else if(x_left_ == 0 && y_left_ == 0){
        timer_.stop();
    }
}

void MainWindow::start_clock()
{
    timer_.start(200);
}

void MainWindow::A_to_B()
{
    disk_to_move_ = peg_A_.back();
    x_left_ = 170;
    y_left_ = 50;
    start_clock();

//    peg_A_.back()->get_disk()->moveBy(170, 0);

}
