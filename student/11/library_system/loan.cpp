/* Source file for loan module.
 *
 * Contains little functions that help handling the loan
 * in the library.cpp file.
 *
 * Program author
 * Name: Ilpo Viertola
 * Student number: 272634
 * UserID: viertoli ( Necessary due to gitlab folder naming. )
 * E-Mail: ilpo.viertola@tuni.fi
 *
 * */

#include "loan.hh"

#include <iostream>

Loan::Loan(Date* day_loaned, Person* loaned_by, Book* loaned_book):
    day_loaned_(new Date(day_loaned->getDay(), day_loaned->getMonth(), day_loaned->getYear())),
    due_date_(new Date(day_loaned->getDay(), day_loaned->getMonth(), day_loaned->getYear())),
    loaned_by_(loaned_by), loaned_book_(loaned_book),
    renewals_left(DEFAULT_RENEWAL_AMOUNT)
{
    // due_date_ one loaning period away from current day when book is loaned.
    due_date_->advance_by_loan_length();
}

Loan::~Loan()
{
    delete day_loaned_;
    day_loaned_ = nullptr;
    delete due_date_;
    due_date_ = nullptr;
}

Book* Loan::get_book()
{
    return loaned_book_;
}

Person* Loan::get_person()
{
    return loaned_by_;
}

Date* Loan::get_date()
{
    return due_date_;
}

bool Loan::renew_loan()
{
    if( renewals_left > 0 ){
        due_date_->advance_by_loan_length();
        --renewals_left;
        return true;
    } else {
        return false;
    }
}
