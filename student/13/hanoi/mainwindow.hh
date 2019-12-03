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

private slots:
    void start_animation();
    void new_game();

private:
    Ui::MainWindow *ui_;

    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;

    std::vector<Disk*> disks_;
    std::vector<QGraphicsRectItem*> pegs_;

    QTimer timer_;
    QGraphicsScene* scene_;

    QGraphicsRectItem* firstPeg_;
    QGraphicsRectItem* middlePeg_;
    QGraphicsRectItem* thirdPeg_;
};

#endif // MAINWINDOW_HH
