#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Items.h"
#include "Robby.h"

#define ARRAY_SQUARE_SIZE 12 // without walls it is -2 in size
#define WORLDS_ROBBY_COMBINATIONS 100 // needs to be divisible by KEEP_TOP evenly
#define ACTIONS_PER_SESSION 200
#define CANS_COUNT 50
#define LOOPS 1000
#define KEEP_TOP 20

using namespace std;


class World
{
private:
    Items world_map_ptr[ARRAY_SQUARE_SIZE][ARRAY_SQUARE_SIZE];
    Robby this_robby;

    void add_cans_and_walls(int cans_to_add){
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

public:
    World(int cans){
        add_cans_and_walls(cans); // creating world

    }

    /* Will mix genes with the incoming new robby*/
    void mate(World* survivor_world1, World* survivor_world2){
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

    Robby inner_robby(){
        return this_robby;
    }

    void print_world(){
        for(int i=0; i<ARRAY_SQUARE_SIZE; i++){
            for(int j=0; j<ARRAY_SQUARE_SIZE; j++){
                cout << world_map_ptr[i][j].item_state();
            }
            cout << endl;
        }
        cout << endl;
    }

    void robby_step(){

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

    int robby_fitness(){
        // returns this robby fitness level
        return this_robby.current_fitness();
    }
};


void erase_world_robby_bottom(vector<World*>* world_array){
    /* erasing the bottom 50% of the world array*/
    int amt_keep = WORLDS_ROBBY_COMBINATIONS/5;
    world_array->erase(world_array->begin()+amt_keep, world_array->end());

}


int main()
{
    srand(time(0));
    int can_num = CANS_COUNT;
    vector<World*> world_array;
    vector<World*>::iterator it = world_array.begin();
    int position = 0;
    vector<World*>::iterator iter = world_array.begin();

    /*creating amount of world and robby combinations*/
    for(int i=0; i<WORLDS_ROBBY_COMBINATIONS; i++){
        world_array.push_back(new World(can_num));
    }

    /* iterating over all world robby combinations and creating fitness level
         using robby_step method*/
    for(it = world_array.begin(); it != world_array.end(); it++){
        (*it)->robby_step();
    }


    /* Sorting world/robby combinations to have the highest first*/
    int counter = WORLDS_ROBBY_COMBINATIONS;
    while(counter){
        for(it = world_array.begin(),(iter = world_array.begin())++; iter != world_array.end() || it != world_array.end(); it++, iter++){
            // move over all of the items in the array and the one after it for comparison
            if(iter == world_array.end()){
                break;
            }
            if((*it)->robby_fitness() < (*iter)->robby_fitness()){
                World* temp = (*it);
                (*it) = (*iter);
                (*iter) = temp;
            }
        }
        counter--;
    }

    /* print world sample after*/
    cout << endl << endl << "check world sample" << endl;
    for(it = world_array.begin(); it != world_array.end(); it++){
        cout << "fitness: " << (*it)->robby_fitness() << endl;
    }


    erase_world_robby_bottom(&world_array);

    /* will loop over the 20 fittest items and will mate will a random 5 robbies*/
    for(int i=0; i<WORLDS_ROBBY_COMBINATIONS/2; i++){
        /* removing bottom 50%*/
        erase_world_robby_bottom(&world_array);

        /* will loop over the 20 fittest items and will mate will a random 5 robbies*/
        for(int i=0; i<KEEP_TOP; i++){
    //        cout << "i value: " << i << endl;
            for(int j=0; j<WORLDS_ROBBY_COMBINATIONS/KEEP_TOP; j++){
                // mating with random robbies
                int robby_num = 0;
                do{
                    robby_num = rand()%KEEP_TOP; // selecting a mate from the top 20(0-19 in array)
                }while(robby_num == i); // can't be itself

                // robby at i and robby_num are different here
                World* new_world_robby = new World(can_num);
                world_array.push_back(new_world_robby); // adding one world/robby to the world_array
                world_array.back()->mate(world_array.at(i), world_array.at(robby_num)); // mating new_world_robby(which is at the end) with robby at i and robby_num.
            }
        }
    }

    /* iterating over all world robby combinations and creating fitness level
     using robby_step method*/
    for(it = world_array.begin(); it != world_array.end(); it++){
        (*it)->robby_step();
    }

    /* Sorting world/robby combinations to have the highest first*/
    counter = WORLDS_ROBBY_COMBINATIONS;
    while(counter){
        for(it = world_array.begin(),(iter = world_array.begin())++; iter != world_array.end() || it != world_array.end(); it++, iter++){
            // move over all of the items in the array and the one after it for comparison
            if(iter == world_array.end()){
                break;
            }
            if((*it)->robby_fitness() < (*iter)->robby_fitness()){
                World* temp = (*it);
                (*it) = (*iter);
                (*iter) = temp;
            }
        }
        counter--;
    }

    for(int i=0; i<LOOPS; i++){
        /* removing bottom 50%*/
        erase_world_robby_bottom(&world_array);

        /* will loop over the 20 fittest items and will mate will a random 5 robbies*/
        for(int i=0; i<KEEP_TOP; i++){
    //        cout << "i value: " << i << endl;
            for(int j=0; j<WORLDS_ROBBY_COMBINATIONS/KEEP_TOP; j++){
                // mating with random robbies
                int robby_num = 0;
                do{
                    robby_num = rand()%KEEP_TOP; // selecting a mate from the top 50(0-49 in array)
                }while(robby_num == i); // can't be itself

                // robby at i and robby_num are different here
                World* new_world_robby = new World(can_num);
                world_array.push_back(new_world_robby); // adding one world/robby to the world_array
                world_array.back()->mate(world_array.at(i), world_array.at(robby_num)); // mating new_world_robby(which is at the end) with robby at i and robby_num.
            }
        }

        /* iterating over all world robby combinations and creating fitness level
         using robby_step method*/
        for(it = world_array.begin(); it != world_array.end(); it++){
            (*it)->robby_step();
        }

        /* Sorting world/robby combinations to have the highest first*/
        counter = WORLDS_ROBBY_COMBINATIONS;
        while(counter){
            for(it = world_array.begin(),(iter = world_array.begin())++; iter != world_array.end() || it != world_array.end(); it++, iter++){
                // move over all of the items in the array and the one after it for comparison
                if(iter == world_array.end()){
                    break;
                }
                if((*it)->robby_fitness() < (*iter)->robby_fitness()){
                    World* temp = (*it);
                    (*it) = (*iter);
                    (*iter) = temp;
                }
            }
            counter--;
        }
    }

    cout << endl << endl << "final end check world sample" << endl;
    for(it = world_array.begin(); it != world_array.end(); it++){
        cout << " fitness: " << (*it)->robby_fitness() << endl;
    }

    return 0;
}