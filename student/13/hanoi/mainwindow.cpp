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

    connect(&animate_timer_, &QTimer::timeout, this, &MainWindow::start_animation);
    connect(ui_->newGameButton, SIGNAL(clicked(bool)), this, SLOT(new_game()));
    connect(ui_->AtoBbutton, SIGNAL(clicked(bool)), this, SLOT(A_to_B()));
    connect(ui_->AtoCbutton, SIGNAL(clicked(bool)), this, SLOT(A_to_C()));
    connect(ui_->BtoAbutton, SIGNAL(clicked(bool)), this, SLOT(B_to_A()));
    connect(ui_->BtoCbutton, SIGNAL(clicked(bool)), this, SLOT(B_to_C()));
    connect(ui_->CtoAbutton, SIGNAL(clicked(bool)), this, SLOT(C_to_A()));
    connect(ui_->CtoBbutton, SIGNAL(clicked(bool)), this, SLOT(C_to_B()));
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
        Disk* new_disk = new Disk(disk, disk_width, disk_height, disk_x, disk_y);
        peg_A_.push_back(new_disk);
        disk_y -= disk_height;
        disk_x += (disk_width/(DISK_AMOUNT - i)) / 2;
        disk_width -= disk_width/(DISK_AMOUNT - i);
    }
}

void MainWindow::new_game()
{
    scene_->clear();
    enable_moves();

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
    qDebug() << x_left_ << " " << y_left_;
    // Rising the disk first upwards.
    if( rise_left_ != 0){
        disk_to_move_->get_disk()->moveBy(0, -STEP);
        rise_left_ -= STEP;
    }
    // Moving the disk over the right peg.
    else if(x_left_ != 0){
        if(x_left_ > 0){
            disk_to_move_->get_disk()->moveBy(STEP, 0);
            x_left_ -= STEP;
        } else {
            disk_to_move_->get_disk()->moveBy(-STEP, 0);
            x_left_ += STEP;
        }
    }
    // Lowering the disk on the correct height.
    else if(y_left_ != 0){
        if(y_left_ > 0){
            disk_to_move_->get_disk()->moveBy(0, STEP);
            y_left_ -= STEP;
        } else {
            disk_to_move_->get_disk()->moveBy(0, -STEP);
            y_left_ += STEP;
        }
    }
    // The disk is in the right place.
    else if(x_left_ == 0 && y_left_ == 0){
        enable_moves();
        disable_moves(false);
        animate_timer_.stop();
        qDebug() << "NEW:" << disk_to_move_->get_x() << " " << disk_to_move_->get_y();
    }
}

void MainWindow::disable_moves(bool all)
{
    if(all){
        ui_->AtoBbutton->setDisabled(true);
        ui_->AtoCbutton->setDisabled(true);
        ui_->BtoAbutton->setDisabled(true);
        ui_->BtoCbutton->setDisabled(true);
        ui_->CtoAbutton->setDisabled(true);
        ui_->CtoBbutton->setDisabled(true);
        ui_->newGameButton->setDisabled(true);
    }
    else {
        Disk* top_on_peg_A = nullptr;
        Disk* top_on_peg_B = nullptr;
        Disk* top_on_peg_C = nullptr;

        if(peg_A_.size() != 0 && peg_B_.size() != 0){
            top_on_peg_A = peg_A_.back();
            top_on_peg_B = peg_B_.back();

            if(top_on_peg_A->get_width() > top_on_peg_B->get_width()){
                ui_->AtoBbutton->setDisabled(true);
            }
            if(top_on_peg_A->get_width() < top_on_peg_B->get_width()){
                ui_->BtoAbutton->setDisabled(true);
            }

            top_on_peg_A = nullptr;
            top_on_peg_B = nullptr;
        }
        if(peg_A_.size() != 0 && peg_C_.size() != 0){
            top_on_peg_A = peg_A_.back();
            top_on_peg_C = peg_C_.back();

            if(top_on_peg_A->get_width() > top_on_peg_C->get_width()){
                ui_->AtoCbutton->setDisabled(true);
            }
            if(top_on_peg_A->get_width() < top_on_peg_C->get_width()){
                ui_->CtoAbutton->setDisabled(true);
            }

            top_on_peg_A = nullptr;
            top_on_peg_C = nullptr;
        }
        if(peg_B_.size() != 0 && peg_C_.size() != 0){
            top_on_peg_B = peg_B_.back();
            top_on_peg_C = peg_C_.back();

            if(top_on_peg_B->get_width() > top_on_peg_C->get_width()){
                ui_->BtoCbutton->setDisabled(true);
            }
            if(top_on_peg_B->get_width() < top_on_peg_C->get_width()){
                ui_->CtoBbutton->setDisabled(true);
            }

            top_on_peg_B = nullptr;
            top_on_peg_C = nullptr;
        }
    }
}

void MainWindow::enable_moves()
{
    ui_->AtoBbutton->setEnabled(true);
    ui_->AtoCbutton->setEnabled(true);
    ui_->BtoAbutton->setEnabled(true);
    ui_->BtoCbutton->setEnabled(true);
    ui_->CtoAbutton->setEnabled(true);
    ui_->CtoBbutton->setEnabled(true);
    ui_->newGameButton->setEnabled(true);
}

void MainWindow::change_coords(char from, char to)
{
    std::vector<Disk*> move_to_peg = {};
    int new_peg_number = 0;

    if(from == 'A'){
        if(to == 'B'){
            move_to_peg = peg_B_;
            new_peg_number = 1;
        } else {
            move_to_peg = peg_C_;
            new_peg_number = 2;
        }
    }
    else if(from == 'B'){
        if(to == 'A'){
            move_to_peg = peg_A_;
            new_peg_number = 0;
        } else {
            move_to_peg = peg_C_;
            new_peg_number = 2;
        }
    }
    else {
        if(to == 'A'){
            move_to_peg = peg_A_;
            new_peg_number = 0;
        } else {
            move_to_peg = peg_B_;
            new_peg_number = 1;
        }
    }

    if(move_to_peg.size() == 0){
        int distance_between_new_and_old_y = 240 - disk_to_move_->get_y();
        disk_to_move_->change_peg(new_peg_number);
        disk_to_move_->new_coords(x_left_, distance_between_new_and_old_y);
    } else {
        int distance_between_new_and_old_y = move_to_peg.back()->get_y() - disk_to_move_->get_y() - 10;
        disk_to_move_->change_peg(new_peg_number);
        disk_to_move_->new_coords(x_left_, distance_between_new_and_old_y);
    }
}

void MainWindow::A_to_B()
{
    disable_moves(true);

    disk_to_move_ = peg_A_.back();
    x_left_ = 170;
    y_left_ = 230 - disk_to_move_->get_height()*peg_B_.size();
    rise_left_ = disk_to_move_->get_y() - 10;

    qDebug() << "ORIGINAL:" << disk_to_move_->get_x() << " " << disk_to_move_->get_y();

    // Setting new coordiantes for disk object.
    change_coords('A', 'B');

    peg_A_.pop_back();
    peg_B_.push_back(disk_to_move_);

    animate_timer_.start(100);
}

void MainWindow::A_to_C()
{
    disable_moves(true);

    disk_to_move_ = peg_A_.back();
    x_left_ = 340;
    y_left_ = 230 - disk_to_move_->get_height()*peg_C_.size();
    rise_left_ = disk_to_move_->get_y() - 10;

    qDebug() << "ORIGINAL:" << disk_to_move_->get_x() << " " << disk_to_move_->get_y();

    // Setting new coordiantes for disk object.
    change_coords('A', 'C');

    peg_A_.pop_back();
    peg_C_.push_back(disk_to_move_);

    animate_timer_.start(100);
}

void MainWindow::B_to_A()
{
    disable_moves(true);

    disk_to_move_ = peg_B_.back();
    x_left_ = -170;
    y_left_ = 230 - disk_to_move_->get_height()*peg_A_.size();
    rise_left_ = disk_to_move_->get_y() - 10;

    qDebug() << "ORIGINAL:" << disk_to_move_->get_x() << " " << disk_to_move_->get_y();

    // Setting new coordiantes for disk object.
    change_coords('B', 'C');

    peg_B_.pop_back();
    peg_A_.push_back(disk_to_move_);

    animate_timer_.start(100);
}

void MainWindow::B_to_C()
{
    disable_moves(true);

    disk_to_move_ = peg_B_.back();
    x_left_ = 170;
    y_left_ = 230 - disk_to_move_->get_height()*peg_C_.size();
    rise_left_ = disk_to_move_->get_y() - 10;

    qDebug() << "ORIGINAL:" << disk_to_move_->get_x() << " " << disk_to_move_->get_y();

    // Setting new coordiantes for disk object.
    change_coords('B', 'C');

    peg_B_.pop_back();
    peg_C_.push_back(disk_to_move_);

    animate_timer_.start(100);
}

void MainWindow::C_to_A()
{
    disable_moves(true);

    disk_to_move_ = peg_C_.back();
    x_left_ = -340;
    y_left_ = 230 - disk_to_move_->get_height()*peg_A_.size();
    rise_left_ = disk_to_move_->get_y() - 10;

    qDebug() << "ORIGINAL:" << disk_to_move_->get_x() << " " << disk_to_move_->get_y();

    // Setting new coordiantes for disk object.
    change_coords('B', 'C');

    peg_C_.pop_back();
    peg_A_.push_back(disk_to_move_);

    animate_timer_.start(100);
}

void MainWindow::C_to_B()
{
    disable_moves(true);

    disk_to_move_ = peg_C_.back();
    x_left_ = -170;
    y_left_ = 230 - disk_to_move_->get_height()*peg_B_.size();
    rise_left_ = disk_to_move_->get_y() - 10;

    qDebug() << "ORIGINAL:" << disk_to_move_->get_x() << " " << disk_to_move_->get_y();

    // Setting new coordiantes for disk object.
    change_coords('B', 'C');

    peg_C_.pop_back();
    peg_B_.push_back(disk_to_move_);

    animate_timer_.start(100);
}
