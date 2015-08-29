#ifndef ITEMS_H
#define ITEMS_H

class Items
{
private:
    char state;

public:
    Items();

    char item_state();

    void create_can();

    void create_wall();

    void remove_can();
};

#endif