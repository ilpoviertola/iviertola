/* Source file for MainWindow module.
 *
 * Contains the logic and functions to make the game work.
 *
 * Program author
 * Name: Ilpo Viertola
 * Student number: 272634
 * UserID: viertoli ( Necessary due to gitlab folder naming. )
 * E-Mail: ilpo.viertola@tuni.fi
 *
 *
 * ---------------
 * TIE-02201 S2019
 * */
#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow), peg_A_({}), peg_B_({}), peg_C_({}), times_({}),
    disk_to_move_(nullptr), x_left_(0), y_left_(0), rise_left_(0),
    previous_event_(-1), secs_(0), moves_(0)
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

    // All the connections except for the closeButton
    // which has been made in the Designer.
    connect(&animate_timer_, &QTimer::timeout, this, &MainWindow::start_animation);
    connect(&clock_timer_, &QTimer::timeout, this, &MainWindow::time_elapsed);
    connect(ui_->newGameButton, SIGNAL(clicked(bool)), this, SLOT(new_game()));
    connect(ui_->AtoBbutton, SIGNAL(clicked(bool)), this, SLOT(A_to_B()));
    connect(ui_->AtoCbutton, SIGNAL(clicked(bool)), this, SLOT(A_to_C()));
    connect(ui_->BtoAbutton, SIGNAL(clicked(bool)), this, SLOT(B_to_A()));
    connect(ui_->BtoCbutton, SIGNAL(clicked(bool)), this, SLOT(B_to_C()));
    connect(ui_->CtoAbutton, SIGNAL(clicked(bool)), this, SLOT(C_to_A()));
    connect(ui_->CtoBbutton, SIGNAL(clicked(bool)), this, SLOT(C_to_B()));


    // Start the timer in ui immediately.
    clock_timer_.start(1000);
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
        scene_->addRect(( i * (BORDER_RIGHT / 4) ) - ( peg_width / 2 ) ,
                        30, peg_width, peg_height, yellow_pen, black_brush);
    }

    //Create as many disks as wanted.
    for( int i = 0; i < DISK_AMOUNT; ++i){
        QGraphicsRectItem* disk = scene_->addRect
                (disk_x, disk_y, disk_width, disk_height, black_pen, green_brush);
        Disk* new_disk = new Disk(disk, disk_width, disk_height, disk_x, disk_y);
        peg_A_.push_back(new_disk);
        disk_y -= disk_height;
        disk_x += (disk_width/(DISK_AMOUNT - i)) / 2;
        disk_width -= disk_width/(DISK_AMOUNT - i);
    }
}

void MainWindow::new_game()
{
    clock_timer_.stop();
    ui_->timeLCD->display(0);
    ui_->movesLCD->display(0);
    scene_->clear();
    ui_->textBrowser->clear();
    enable_moves();

    secs_ = 0;
    moves_ = 0;

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


    clock_timer_.start(1000);
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

    // Secondly moving the disk over the right peg.
    else if(x_left_ != 0){
        if(x_left_ > 0){
            disk_to_move_->get_disk()->moveBy(STEP, 0);
            x_left_ -= STEP;
        } else {
            disk_to_move_->get_disk()->moveBy(-STEP, 0);
            x_left_ += STEP;
        }
    }
    // Lastly lowering the disk on the correct height.
    else if(y_left_ != 0){
        if(y_left_ > 0){
            disk_to_move_->get_disk()->moveBy(0, STEP);
            y_left_ -= STEP;
        } else {
            disk_to_move_->get_disk()->moveBy(0, -STEP);
            y_left_ += STEP;
        }
    }
    // Finally the disk is in the right place.
    else if(x_left_ == 0 && y_left_ == 0){
        if(not has_won()){
            enable_moves();
            disable_moves(false);
            animate_timer_.stop();
            qDebug() << "NEW:" << disk_to_move_->get_x()
                     << " " << disk_to_move_->get_y();
        } else {
            animate_timer_.stop();
        }
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

std::pair<std::vector<Disk*>, int> MainWindow::get_peg_data(char from, char to)
{
    std::vector<Disk*> move_to_peg = {};
    int new_peg_number = -1;

    // User wants to move disk from peg A to B or C naturally.
    if(from == 'A' && peg_A_.size() != 0){
        disk_to_move_ = peg_A_.back();
        if(to == 'B'){
            move_to_peg = peg_B_;
            new_peg_number = 1;
            x_left_ = 170;
            ui_->textBrowser->append(QString::fromStdString("From A to B!"));
        } else {
            move_to_peg = peg_C_;
            new_peg_number = 2;
            x_left_ = 340;
            ui_->textBrowser->append(QString::fromStdString("From A to C!"));
        }
    }
    // User wants to move disk from peg B to A or C naturally.
    else if(from == 'B' && peg_B_.size() != 0){
        disk_to_move_ = peg_B_.back();
        if(to == 'A'){
            move_to_peg = peg_A_;
            new_peg_number = 0;
            x_left_ = -170;
            ui_->textBrowser->append(QString::fromStdString("From B to A!"));
        } else {
            move_to_peg = peg_C_;
            new_peg_number = 2;
            x_left_ = 170;
            ui_->textBrowser->append(QString::fromStdString("From B to C!"));
        }
    }
    // User wants to move disk from peg C to A or B naturally.
    else if(from == 'C' && peg_C_.size() != 0){
        disk_to_move_ = peg_C_.back();
        if(to == 'A'){
            move_to_peg = peg_A_;
            new_peg_number = 0;
            x_left_ = -340;
            ui_->textBrowser->append(QString::fromStdString("From C to A!"));
        } else {
            move_to_peg = peg_B_;
            new_peg_number = 1;
            x_left_ = -170;
            ui_->textBrowser->append(QString::fromStdString("From C to B!"));
        }
    // User wants to move disk from the peg where isn't any disks.
    } else {
        ui_->textBrowser->append(QString::fromStdString("Misclick!"));
    }

    return std::make_pair(move_to_peg, new_peg_number);
}

void MainWindow::move_disk(char from, char to)
{
    // Information to move the disk.
    std::pair<std::vector<Disk*>, int> peg_data = get_peg_data(from, to);

    // Zeroing the keyboard input.
    previous_event_ = -1;

    // Acceptable move.
    if(peg_data.second != -1){
        std::vector<Disk*> move_to_peg = peg_data.first;
        int new_peg_number = peg_data.second;

        // Disable buttons so user can't cause bugs during animation.
        disable_moves(true);

        // old_peg_number tells where the disk is moved from.
        int old_peg_number = disk_to_move_->get_peg();
        y_left_ = 230 - disk_to_move_->get_height()*move_to_peg.size();
        rise_left_ = disk_to_move_->get_y() - 10;

        qDebug() << "ORIGINAL:" << disk_to_move_->get_x()
                 << " " << disk_to_move_->get_y();

        // Setting new coordiantes and peg for disk object.
        if(move_to_peg.size() == 0){
            int distance_between_new_and_old_y = 240 - disk_to_move_->get_y();
            disk_to_move_->change_peg(new_peg_number);
            disk_to_move_->new_coords(x_left_, distance_between_new_and_old_y);
        } else {
            int distance_between_new_and_old_y =
                    move_to_peg.back()->get_y() - disk_to_move_->get_y() - disk_to_move_->get_height();
            disk_to_move_->change_peg(new_peg_number);
            disk_to_move_->new_coords(x_left_, distance_between_new_and_old_y);
        }

        // old_peg_number tells from which peg to delete the disk on the top.
        if(old_peg_number == 0){peg_A_.pop_back();}
        else if(old_peg_number == 1){peg_B_.pop_back();}
        else{peg_C_.pop_back();}

        // new_peg_number tells to which peg to add a new disk on the top.
        if(new_peg_number == 0){peg_A_.push_back(disk_to_move_);}
        else if(new_peg_number == 1){peg_B_.push_back(disk_to_move_);}
        else{peg_C_.push_back(disk_to_move_);}

        move_to_peg.clear();
        ++moves_;
        ui_->movesLCD->display(moves_);

        // Start animation.
        animate_timer_.start(50);
    }
    // User tried to move a disk from the peg that contains none.
    // Nothing happens.
    else { return; }
}

bool MainWindow::has_won()
{
    if(peg_C_.size() == DISK_AMOUNT){
        int fastest_time = 0;

        clock_timer_.stop();
        disable_moves(true);
        ui_->newGameButton->setEnabled(true);
        times_.push_back(secs_);

        ui_->textBrowser->append("");
        ui_->textBrowser->append
                (QString::fromStdString("You won! Let's play another one."));
        ui_->textBrowser->append
                (QString::fromStdString("Your time was " +
                                        std::to_string(secs_)) + " seconds");
        ui_->textBrowser->append
                (QString::fromStdString("and you made " +
                                        std::to_string(moves_)) + " moves.");
        for(int time : times_){
            if(time < fastest_time){
                fastest_time = time;
            } else if(fastest_time == 0){
                fastest_time = time;
            }
        }
        ui_->textBrowser->append("");
        ui_->textBrowser->append
                (QString::fromStdString("The best time yet is " +
                                   std::to_string(fastest_time) + " seconds."));
        return true;
    } else { return false; }
}

void MainWindow::A_to_B()
{
    move_disk('A', 'B');
}

void MainWindow::A_to_C()
{
    move_disk('A', 'C');
}

void MainWindow::B_to_A()
{
    move_disk('B', 'A');
}

void MainWindow::B_to_C()
{
    move_disk('B', 'C');
}

void MainWindow::C_to_A()
{
    move_disk('C', 'A');
}

void MainWindow::C_to_B()
{
    move_disk('C', 'B');
}

void MainWindow::time_elapsed()
{
    ++secs_;
    ui_->timeLCD->display(secs_);

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(not animate_timer_.isActive()){
        if(previous_event_ == -1){
            previous_event_ = event->key();
            return;
        }
        else if(previous_event_ == Qt::Key_A){
            if(event->key() == Qt::Key_B && ui_->AtoBbutton->isEnabled()){
                move_disk('A', 'B');
            }
            else if(event->key() == Qt::Key_C && ui_->AtoCbutton->isEnabled()){
                move_disk('A', 'C');
            }
        }
        else if(previous_event_ == Qt::Key_B){
            if(event->key() == Qt::Key_A && ui_->BtoAbutton->isEnabled()){
                move_disk('B', 'A');
            }
            else if(event->key() == Qt::Key_C && ui_->BtoCbutton->isEnabled()){
                move_disk('B', 'C');
            }
        }
        else if(previous_event_ == Qt::Key_C){
            if(event->key() == Qt::Key_A  && ui_->CtoAbutton->isEnabled()){
                move_disk('C', 'A');
            }
            else if(event->key() == Qt::Key_B && ui_->CtoBbutton->isEnabled()){
                move_disk('C', 'B');
            }
        }

        previous_event_ = -1;
    }
}
