#include "queue.hh" 
#include <string>
#include <iostream>

using namespace std;

// Implement the membqer functions of Queue here

Queue::Queue(unsigned int cycle):
    cycle_(cycle){    
}

Queue::~Queue(){
    while( first_ != nullptr ){
        Vehicle* to_delete = first_;
        first_ = first_->next;
        
        delete to_delete;
    }
}

void Queue::enqueue(string reg){
    Vehicle* new_car = new Vehicle{reg, nullptr};

    if(! is_green_ ){
        if( first_ == nullptr ){
            first_ = new_car;
            last_ = new_car;
        } else {
            Vehicle* old_last = last_;
            old_last->next = new_car;
            last_ = new_car;
        }
    } else {
        first_ = new_car;
        last_ = new_car;
        cout << "GREEN: The vehicle ";
        dequeue();
        cout << "need not stop to wait\n";
    }
}

void Queue::print(){
    Vehicle* to_print = first_;

    if(! is_green_ ){

        if( to_print != nullptr ){
            cout << "RED: Vehicle(s) ";
            while( to_print != nullptr ){
                cout << to_print->reg_num << " ";
                to_print = to_print->next;
            }
            cout << "waiting in traffic lights\n";
        } else { cout << "RED: No vehicles waiting in traffic lights\n"; }

    } else {

        if( to_print != nullptr){
            cout << "GREEN: Vehicle(s) ";
            while( to_print != nullptr ){
                cout << to_print->reg_num << " ";
                to_print = to_print->next;
            }
            cout << "waiting in traffic lights\n";
        } else { cout << "GREEN: No vehicles waiting in traffic lights\n"; }
    }
}

void Queue::dequeue(){
    unsigned int round = 0;

    while( round < cycle_ && first_ != nullptr ){
        Vehicle* to_delete = first_;
        first_ = first_->next;
        cout << to_delete->reg_num << " ";
        delete to_delete;
        ++round;
    }
}

void Queue::switch_light(){
    if( is_green_ ){
        if( first_ != nullptr ){
            is_green_ = false;
            cout << "RED: Vehicle(s) ";
            Vehicle* to_print = first_;
            while( to_print != nullptr ){
                cout << to_print->reg_num << " ";
                to_print = to_print->next;
            }
            cout << "waiting in traffic lights\n";
        } else {
            is_green_ = false;
            cout << "RED: No vehicles waiting in traffic lights\n";
        }

    } else {
        if( first_ != nullptr ){
            is_green_ = true;
            cout << "GREEN: Vehicle(s) ";
            dequeue();
            cout << "can go on\n";
            is_green_ = false;
        } else {
            is_green_ = true;
            cout << "GREEN: No vehicles waiting in traffic lights\n";
        }
    }
}

void Queue::reset_cycle(unsigned int cycle){
    cycle_ = cycle;
}
                 
