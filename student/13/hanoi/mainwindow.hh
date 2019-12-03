#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "disk.hh"

#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>

const int DISK_AMOUNT = 10;

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
    void start_clock();

private slots:
    void start_animation();
    void new_game();
    void A_to_B();

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

    QTimer timer_;
    QGraphicsScene* scene_;
};

#endif // MAINWINDOW_HH
