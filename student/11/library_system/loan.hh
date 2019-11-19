/* Module: Loan
 * ------------
 * This class and its bahaviour should be defined by the student.
 *
 * TIE-0220x S2019
 * */
#ifndef LOAN_HH
#define LOAN_HH
#include "book.hh"
#include "loan.hh"
#include "date.hh"

#include <vector>

class Book;
class Person;
class Date;

const int DEFAULT_RENEWAL_AMOUNT = 6;

class Loan
{
public:

    Loan(Date* day_loaned, Person* loaned_by, Book* loaned_book);
    ~Loan();

    Book* get_book();
    Person* get_person();
    Date* get_date();

private:

    Date* day_loaned_;
    Date* due_date_;
    Person* loaned_by_;
    Book* loaned_book_;
    int renewals_left;

};

#endif // LOAN_HH
