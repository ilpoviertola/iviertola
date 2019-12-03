#include "disk.hh"

Disk::Disk(QGraphicsRectItem *disk, int width, int x, int y):
    disk_(disk), width_(width), x_(x), y_(y), peg_(0)
{}

QGraphicsRectItem* Disk::get_disk()
{
    return disk_;
}

int Disk::get_width()
{
    return width_;
}
