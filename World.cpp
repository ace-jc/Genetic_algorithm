#include <stdlib.h>
#include <iostream>
#include "Items.h"
#include "Robby.h"
#include "World.h"

using namespace std;

// World constructor
World::World(int cans){
    add_cans_and_walls(cans); // creating world
}



// member functions
void World::add_cans_and_walls(int cans_to_add){
    // adding walls
    for(int i=0; i<ARRAY_SQUARE_SIZE; i++){
        for(int j=0; j<ARRAY_SQUARE_SIZE; j++){
            if(i==0 || i==ARRAY_SQUARE_SIZE-1 || j==0 || j==ARRAY_SQUARE_SIZE-1){
                world_map_ptr[i][j].create_wall();
            }
        }
    }
    // adding cans
    for(int can=0; can<cans_to_add; can++){
        // will create a can for each number of cans_to_add
        int horizontal = 0;
        int vertical = 0;
        do{
            horizontal = rand()%ARRAY_SQUARE_SIZE;
            vertical = rand()%ARRAY_SQUARE_SIZE;
        }while(world_map_ptr[horizontal][vertical].item_state() != 'e');
        world_map_ptr[horizontal][vertical].create_can();
    }
}




/* Will mix genes with the incoming new robby*/
void World::mate(World* survivor_world1, World* survivor_world2){
    for(int gene_position=0; gene_position<GENE_LENGTH; gene_position++){
        int random_num = 0;
        if(survivor_world1->robby_fitness() >= survivor_world2->robby_fitness()){
            random_num = rand()%10; // zero to four
            if(random_num == 1){// one in 20 chance of grabbing lower one
                this->inner_robby().gene_change(gene_position, survivor_world2->inner_robby().gene_from(gene_position));
            }
            else{
                // grabbing gene from survivor1
                this->inner_robby().gene_change(gene_position, survivor_world1->inner_robby().gene_from(gene_position));
            }
        }
        else if(survivor_world1->robby_fitness() < survivor_world2->robby_fitness()){
            random_num = rand()%10; // zero to four
            if(random_num == 1){// one in four chance of grabbing lower one
                this->inner_robby().gene_change(gene_position, survivor_world1->inner_robby().gene_from(gene_position));
            }
            else{
                // grabbing gene from survivor1
                this->inner_robby().gene_change(gene_position, survivor_world2->inner_robby().gene_from(gene_position));
            }
        }
    }
}

Robby World::inner_robby(){
    return this_robby;
}

void World::print_world(){
    for(int i=0; i<ARRAY_SQUARE_SIZE; i++){
        for(int j=0; j<ARRAY_SQUARE_SIZE; j++){
            cout << world_map_ptr[i][j].item_state();
        }
        cout << endl;
    }
    cout << endl;
}

void World::robby_step(){

    int rounds = ACTIONS_PER_SESSION;

    while(rounds){
        // moving time forward
        int horizontal = this_robby.horizontal_position();
        int vertical = this_robby.vertical_position();

        char north = world_map_ptr[horizontal][vertical-1].item_state();
        char south = world_map_ptr[horizontal][vertical+1].item_state();
        char east = world_map_ptr[horizontal+1][vertical].item_state();
        char west = world_map_ptr[horizontal-1][vertical].item_state();
        char current = world_map_ptr[horizontal][vertical].item_state();

        // returning action given the movement criteria
        int robby_action = this_robby.situation_table_lookup(north, south, east, west, current);

        if(robby_action == 6){
            robby_action = rand()%4;
        }

        // gene actions are defined as follows:
        // 0 is move north
        // 1 is move south
        // 2 is move east
        // 3 is move west
        // 4 is stay put
        // 5 is pickup
        // 6 is choose random move
        if(robby_action == 0){
            // will attempt to move north
            if(north == 'w'){
                //hit a wall and stays in current position
                this_robby.hit_wall();
            }
            else{
                // did not hit wall
                this_robby.move_north();
            }
        }
        else if(robby_action == 1){
            // will attempt to move south
            if(south == 'w'){
                //hit a wall and stays in current position
                this_robby.hit_wall();
            }
            else{
                // did not hit wall
                this_robby.move_south();
            }
        }
        else if(robby_action == 2){
            // will attempt to move east
            if(east == 'w'){
                //hit a wall and stays in current position
                this_robby.hit_wall();
            }
            else{
                // did not hit wall
                this_robby.move_east();
            }
        }
        else if(robby_action == 3){
            // will attempt to move west
            if(west == 'w'){
                //hit a wall and stays in current position
                this_robby.hit_wall();
            }
            else{
                // did not hit wall
                this_robby.move_west();
            }
        }
        else if(robby_action == 5){
            if(world_map_ptr[horizontal][vertical].item_state() == 'c'){
                // trying to pickup a can and it exists
                this_robby.found_can();
                world_map_ptr[horizontal][vertical].remove_can();
            }
            else{
                // can did not exist when trying to pick it up
                this_robby.can_does_not_exist();
            }
        }

        rounds--;
    }


}

int World::robby_fitness(){
    // returns this robby fitness level
    return this_robby.current_fitness();
}