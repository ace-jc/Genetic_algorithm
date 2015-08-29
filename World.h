#ifndef WORLD_H
#define WORLD_H

#define ARRAY_SQUARE_SIZE 12 // without walls it is -2 in size
#define ACTIONS_PER_SESSION 200

class World
{
private:
    Items world_map_ptr[ARRAY_SQUARE_SIZE][ARRAY_SQUARE_SIZE];
    Robby this_robby;

    void add_cans_and_walls(int cans_to_add);

public:
    // World Constructor
    World(int cans);

    /* Will mix genes with the incoming new robby*/
    void mate(World* survivor_world1, World* survivor_world2);

    Robby inner_robby();
    void print_world();
    void robby_step();
    int robby_fitness();
};

#endif