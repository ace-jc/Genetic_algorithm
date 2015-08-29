#include "Items.h"

// Item constructor
Items::Items(){
    state = 'e'; // is empty
}


// member functions
char Items::item_state(){
    return state;
}

void Items::create_can(){
    this->state = 'c';
}

void Items::create_wall(){
    this->state = 'w';
}

void Items::remove_can(){
    this->state = 'e';
}
