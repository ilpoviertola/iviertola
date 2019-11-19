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

    // Getters.
    Book* get_book();
    Person* get_person();
    Date* get_date();    
    // Checks if the book is late. Returns true if the book is late.
    bool is_late(Date *today);
    // Renews the loan so moves due date forward one loan period,
    // if there is renewals left. Returns true if the renewal is succesful.
    bool renew_loan();

    ~Loan();

private:

    // Day when the book is loaned.
    Date* day_loaned_;
    // Day when the loan must be returned.
    Date* due_date_;
    // Information of the person who loaned the book.
    Person* loaned_by_;
    // Information of the book loaned.
    Book* loaned_book_;
    // Amount of renewals of the loan left. Starts with DEFAULT_RENEWAL_AMOUNT.
    int renewals_left;

};

#endif // LOAN_HH
