#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here

using namespace std;

Cards::Cards(): top_(nullptr), bottom_(nullptr){
}

Cards::~Cards(){
    while( top_ != nullptr ){
        Card_data* cardToDelete = top_;
        top_ = top_->next;

        delete cardToDelete;
    }
}

void Cards::add(int id){
    Card_data* new_card = new Card_data{id, nullptr};

    if(top_ == nullptr){
        top_ = new_card;
        bottom_ = new_card;
    } else {
        Card_data* toBeNext = top_;
        top_ = new_card;
        top_->next = toBeNext;
    }
}

void Cards::print_from_top_to_bottom(ostream &s){
    Card_data* cardToPrint = top_;
    int number = 1;

    while(cardToPrint != nullptr){
        s << number << ": " << cardToPrint->data << "\n";
        ++number;
        cardToPrint = cardToPrint->next;
    }
}

bool Cards::bottom_to_top(){
    if( top_ != bottom_ ){
        Card_data* oldTop = top_;
        Card_data* oldBottom = bottom_;
        Card_data* search = top_;

        while( search->next->next != nullptr ){
            search = search->next;
        }

        bottom_ = search;

        bottom_->next = nullptr;

        top_ = oldBottom;
        top_->next = oldTop;

        return true;
    }

    else{ return false; }
}

bool Cards::top_to_bottom(){
    if( top_ != bottom_ ){
        Card_data* newTop = top_->next;
        Card_data* oldTop = top_;

        top_ = newTop;
        bottom_->next = oldTop;
        bottom_ = oldTop;
        bottom_->next = nullptr;

        return true;

    } else { return false; }
}

bool Cards::remove(int &id){
    if( top_ != nullptr ){
        Card_data* toRemove = top_;

        id = toRemove->data;

        if( top_ == bottom_ ){
            top_ = nullptr;
            bottom_ = nullptr;
        } else {
            top_ = top_->next;
        }

        delete toRemove;

        return true;
    } else { return false; }
}

void Cards::print_from_bottom_to_top(ostream &s){
    s << "moro";
}
