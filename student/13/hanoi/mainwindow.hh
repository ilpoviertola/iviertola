#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "disk.hh"

#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>

// Amount of disks used in the game.
const int DISK_AMOUNT = 3;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor.
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Setups the gameboard with wanted amount of disks.
    void setup_gameboard();

    // Disables all moving buttons and new game button when bool is true.
    // Checks for banned moves also when bool is false.
    void disable_moves(bool all);

    // Enables all the buttons that can be disabled.
    void enable_moves();

    // Function moves the disk from given peg to the given destination peg.
    void move_disk(char from, char to);

    // Function checks after moving the disk that has the user won the game.
    bool has_won();

private slots:
    // Slot for the timer in the ui.
    void time_elapsed();

    // Animation happens in this slot.
    void start_animation();

    // Zeros every value that needs it and starts the timer in the ui again.
    // Clears the scene_, text browser, move counter, and
    // calls for the setup_gameboard function.
    void new_game();

    // Slots call the move_disk function with different parameters.
    // Parameters are in the function name.
    void A_to_B();
    void A_to_C();
    void B_to_A();
    void B_to_C();
    void C_to_A();
    void C_to_B();

private:
    Ui::MainWindow *ui_;

    // Constants to make the scene right size.
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;

    // How much the disk moves at a time.
    const int STEP = 10;

    // Each peg is a vector containing the disks in it.
    // Disk on the top is located at the back of the vector.
    std::vector<Disk*> peg_A_;
    std::vector<Disk*> peg_B_;
    std::vector<Disk*> peg_C_;

    // This is the disk that user has chosen to move.
    Disk* disk_to_move_;

    // How much is left to the next peg horizontally.
    int x_left_;
    // How much is left to on top of the disk in the target peg.
    int y_left_;
    // How much is left to the top border of the gameboard.
    int rise_left_;

    // Seconds in the timer on the ui.
    int secs_;
    // How many moves has the user used.
    int moves_;

    // Timer that initiates the animation.
    QTimer animate_timer_;
    // Timer used in the timer in the ui.
    QTimer clock_timer_;
    // A surface to build the gameboard on.
    QGraphicsScene* scene_;
};

#endif // MAINWINDOW_HH
