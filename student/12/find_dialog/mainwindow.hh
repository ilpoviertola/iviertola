#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void split (const std::string& line, std::vector<std::string>& result,
               char separator);

private slots:
    void read_file();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HH
