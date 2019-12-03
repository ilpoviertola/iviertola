#ifndef DISK_HH
#define DISK_HH

#include <QGraphicsRectItem>


class Disk
{
public:
    Disk(QGraphicsRectItem* disk, int width, int x, int y);

    // Getters.
    QGraphicsRectItem* get_disk();
    int get_peg();
    int get_width();
    int get_x();
    int get_y();

    int change_peg();

private:
    QGraphicsRectItem* disk_;

    int width_;
    int x_;
    int y_;
    int peg_;
};

#endif // DISK_HH
