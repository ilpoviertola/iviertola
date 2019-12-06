#ifndef DISK_HH
#define DISK_HH

#include <QGraphicsRectItem>


class Disk
{
public:
    // Constructor.
    Disk(QGraphicsRectItem* disk, int width, int height, int x, int y);
    ~Disk();

    // Getters.
    QGraphicsRectItem* get_disk();
    int get_peg();
    int get_width();
    int get_height();
    int get_x();
    int get_y();

    // Changes the peg when disk is moved. A=0, B=1 and C=2.
    void change_peg(int peg);
    // Changes the coordinates of the disk when it's being moved.
    void new_coords(int x, int y);

private:
    // Pointer to the disk.
    QGraphicsRectItem* disk_;

    // Width of the disk.
    int width_;
    // Height of the disk.
    int height_;
    // Disk's left corner's x coordinate.
    int x_;
    // Disk's left corner's y coordinate.
    int y_;
    // Which peg the disk is at.
    int peg_;
};

#endif // DISK_HH
