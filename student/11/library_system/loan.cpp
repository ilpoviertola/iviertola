#include "loan.hh"

#include <iostream>
#include <memory>

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
