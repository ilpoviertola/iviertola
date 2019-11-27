#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer;

private slots:
    // Add your slots here
    void start_timer();
    void start_clock();
    void stop_clock();
    void reset_clock();

private:
    Ui::MainWindow *ui;
    // Add other necessary members here
    int mins_;
    int secs_;
};

#endif // MAINWINDOW_HH
