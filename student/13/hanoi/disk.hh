/* Class: Disk
 * ----------------
 * Represents a single disk used in the game.
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
#ifndef DISK_HH
#define DISK_HH

#include <QGraphicsRectItem>


class Disk
{
public:
    // Constructor.
    Disk(QGraphicsRectItem* disk, int width, int height, int x, int y);
    // Destructor.
    ~Disk();

    // Getters.
    QGraphicsRectItem* get_disk() const;
    int get_peg() const;
    int get_width() const;
    int get_height() const;
    int get_x() const;
    int get_y() const;

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
