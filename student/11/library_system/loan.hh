/* Module: Loan
 * ------------
 *
 * Takes care of loaning. Each loan is it's own object with data when the loan
 * was taken, when it should be returned or renewed, who loaned it, what is the
 * book that was loaned and how many times the person who loaned it can renew
 * the loan.
 *
 * Program author
 * Name: Ilpo Viertola
 * Student number: 272634
 * UserID: viertoli ( Necessary due to gitlab folder naming. )
 * E-Mail: ilpo.viertola@tuni.fi
 *
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
