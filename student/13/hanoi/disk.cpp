#include "disk.hh"

Disk::Disk(QGraphicsRectItem *disk, int width, int x, int y):
    disk_(disk), width_(width), x_(x), y_(y), peg_(0)
{}
