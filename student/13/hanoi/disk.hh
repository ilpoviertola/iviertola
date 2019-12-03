#ifndef DISK_HH
#define DISK_HH

#include <QGraphicsRectItem>


class Disk
{
public:
    Disk(QGraphicsRectItem* disk, int width, int height, int x, int y);

    // Getters.
    QGraphicsRectItem* get_disk();
    int get_peg();
    int get_width();
    int get_height();
    int get_x();
    int get_y();

    void change_peg(int peg);
    void new_coords(int x, int y);

private:
    QGraphicsRectItem* disk_;

    int width_;
    int height_;
    int x_;
    int y_;
    int peg_;
};

#endif // DISK_HH
