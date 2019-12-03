#include "disk.hh"

Disk::Disk(QGraphicsRectItem *disk, int width, int height, int x, int y):
    disk_(disk), width_(width), height_(height), x_(x), y_(y), peg_(0)
{}

QGraphicsRectItem* Disk::get_disk()
{
    return disk_;
}

int Disk::get_width()
{
    return width_;
}

int Disk::get_height()
{
    return height_;
}

int Disk::get_y()
{
    return y_;
}

int Disk::get_x()
{
    return x_;
}

void Disk::new_coords(int x, int y)
{
    x_ = x_ + x;
    y_ = y_ + y;
}

void Disk::change_peg(int peg)
{
    peg_ = peg;
}
