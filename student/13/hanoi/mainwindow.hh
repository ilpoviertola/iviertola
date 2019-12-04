#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "disk.hh"

#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>

const int DISK_AMOUNT = 2;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setup_gameboard();
    void disable_moves(bool all);
    void enable_moves();
    void move_disk(char from, char to);
    bool has_won();

private slots:
    void start_animation();
    void new_game();
    void A_to_B();
    void A_to_C();
    void B_to_A();
    void B_to_C();
    void C_to_A();
    void C_to_B();

private:
    Ui::MainWindow *ui_;

    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;    
    const int STEP = 10;

    std::vector<Disk*> peg_A_;
    std::vector<Disk*> peg_B_;
    std::vector<Disk*> peg_C_;

    Disk* disk_to_move_;

    int x_left_;
    int y_left_;
    int rise_left_;

    QTimer animate_timer_;
    QGraphicsScene* scene_;
};

#endif // MAINWINDOW_HH
