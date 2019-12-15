/* Source file for disk class.
 *
 * Contains the functions to change or get the data stored in the Disk.
 *
 * Program author
 * Name: Ilpo Viertola
 * Student number: 272634
 * UserID: viertoli ( Necessary due to gitlab folder naming. )
 * E-Mail: ilpo.viertola@tuni.fi
 *
 *
 * ---------------
 * TIE-02201 S2019
 * */
#include "disk.hh"

Disk::Disk(QGraphicsRectItem *disk, int width, int height, int x, int y):
    disk_(disk), width_(width), height_(height), x_(x), y_(y), peg_(0)
{}

Disk::~Disk()
{

}

QGraphicsRectItem* Disk::get_disk() const
{
    return disk_;
}

int Disk::get_peg() const
{
    return peg_;
}

int Disk::get_width() const
{
    return width_;
}

int Disk::get_height() const
{
    return height_;
}

int Disk::get_y() const
{
    return y_;
}

int Disk::get_x() const
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
