#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>

#define ARRAY_SQUARE_SIZE 12 // without walls it is -2 in size
#define GENE_LENGTH 243
#define WORLDS_ROBBY_COMBINATIONS 100 // needs to be divisible by KEEP_TOP evenly
#define ACTIONS_PER_SESSION 200
#define SITUATIONS_ACTIONS 6
#define CANS_COUNT 50
#define LOOPS 1000
#define KEEP_TOP 20

using namespace std;


class Robby{
private:
    char situation_table_and_genes[GENE_LENGTH][SITUATIONS_ACTIONS]; // array containing the 243 situations and genes
    int current_horizontal;
    int current_vertical;
    int fitness_level;

public:
    Robby(){
        current_horizontal = 1; // to avoid wall at 0
        current_vertical = 1; // to avoid wall at 0
        set_up_situation_table();
        fitness_level = 0;
    }

    bool set_w_current = false;
    char west_setting = 'e'; // letter used to help set west column
    char east_setting = 'e'; // letter used to help set west column
    int east_w_count = 0;

    char gene_from(int gene_to_return){
        char output;
        output = situation_table_and_genes[gene_to_return][5];

        int random_mutation = rand()%100 + 1; //1 in 100 chance of mutation
        if(random_mutation == 1){
            output = (char)((rand()%7)+48); //+48 due to ascii storage
        }

        return output;
    }

    void gene_change(int gene_location, char gene_to_insert){
        this->situation_table_and_genes[gene_location][5] = gene_to_insert;
    }

    void found_can(){
        // found can, worth 10 points
        this->fitness_level += 10;
    }

    void can_does_not_exist(){
        // tried to pickup a non-existent can
        this->fitness_level--;
    }

    void move_north(){
        this->current_vertical -= 1;
    }

    void move_south(){
        this->current_vertical += 1;
    }

    void move_east(){
        this->current_horizontal += 1;
    }

    void move_west(){
        this->current_horizontal -= 1;
    }


    void hit_wall(){
        this->fitness_level -= 5;
    }

    void reset_postion_to_home(){
        this->current_horizontal = 1;
        this->current_vertical = 1;
    }

    int current_fitness(){
        return this->fitness_level;
    }

    void set_up_situation_table(){
        for(int i=0; i<GENE_LENGTH; i++){
            for(int j=0; j<SITUATIONS_ACTIONS; j++){
                if(j==5){
                    // random gene area
                    // setting 0-6 in ascii char
                    situation_table_and_genes[i][j] = (char)((rand()%7)+48); //+48 due to ascii storage
                    // gene actions are defined as follows:
                    // 0 is move north
                    // 1 is move south
                    // 2 is move east
                    // 3 is move west
                    // 4 is stay put
                    // 5 is pickup
                    // 6 is choose random move
                }
                if(j==4){
                    // setting all values in column current
                    if(i%3 == 0){
                        situation_table_and_genes[i][j] = 'e';
                    }
                    else if(i%3 == 1){
                        situation_table_and_genes[i][j] = 'c';
                    }
                    else if(i%3 == 2){
                        situation_table_and_genes[i][j] = 'w';
                        set_w_current = true;
                    }
                }
                if(j==3){
                    // setting all values in West
                    if(set_w_current){
                        if(west_setting == 'e'){
                            west_setting = 'c';
                        }
                        else if(west_setting == 'c'){
                            west_setting = 'w';
                        }
                        else if(west_setting == 'w'){
                            west_setting = 'e';
                        }
                        set_w_current = false;
                    }
                    situation_table_and_genes[i][j] = west_setting;
                    if(west_setting == 'w'){
                        east_w_count++; // helping east calculate three total w's in west
                    }
                }
                if(j==2){
                    // setting all values in East
                    if(east_w_count == 3){
                        if(east_setting == 'e'){
                            east_setting = 'c';
                        }
                        else if(east_setting == 'c'){
                            east_setting = 'w';
                        }
                        else if(east_setting == 'w'){
                            east_setting = 'e';
                        }
                        east_w_count = 0;
                    }
                    situation_table_and_genes[i][j] = east_setting;
                }
                if(j==1){
                    // setting all values in South
                    if(i<27){
                        situation_table_and_genes[i][j] = 'e';
                    }
                    else if(i>=27 && i<54){
                        situation_table_and_genes[i][j] = 'c';
                    }
                    else if(i>=54 && i<81){
                        situation_table_and_genes[i][j] = 'w';
                    }
                    else if(i>=81 && i<108){
                        situation_table_and_genes[i][j] = 'e';
                    }
                    else if(i>=108 && i<135){
                        situation_table_and_genes[i][j] = 'c';
                    }
                    else if(i>=135 && i<162){
                        situation_table_and_genes[i][j] = 'w';
                    }
                    else if(i>=162 && i<189){
                        situation_table_and_genes[i][j] = 'e';
                    }
                    else if(i>=189 && i<216){
                        situation_table_and_genes[i][j] = 'c';
                    }
                    else if(i>=216 && i<243){
                        situation_table_and_genes[i][j] = 'w';
                    }
                }
                if(j==0){
                    // setting all values in North
                    if(i<81){
                        situation_table_and_genes[i][j] = 'e';
                    }
                    else if(i>=81 && i<162){
                        situation_table_and_genes[i][j] = 'c';
                    }
                    else if(i>=162 && i<243){
                        situation_table_and_genes[i][j] = 'w';
                    }
                }
            }
        }
    }

    int horizontal_position(){
        return current_horizontal;
    }

    int vertical_position(){
        return current_vertical;
    }

    int situation_table_lookup(char north, char south, char east, char west, char current){
        // Using situation table to return the associated action
        for(int i=0; i<GENE_LENGTH; i++){

            if(situation_table_and_genes[i][0] == north &&
               situation_table_and_genes[i][1] == south &&
               situation_table_and_genes[i][2] == east &&
               situation_table_and_genes[i][3] == west &&
               situation_table_and_genes[i][4] == current){
                return (int)(situation_table_and_genes[i][5] - 48); // converting char to int
            }
        }
    }

    void print_situation_table(){
        for(int i=0; i<GENE_LENGTH; i++){
            for(int j=0; j<SITUATIONS_ACTIONS; j++){
                cout << situation_table_and_genes[i][j];
            }
            cout << endl;
        }
    }

};

class Items{
private:
    char state;

public:
    Items(){
        state = 'e'; // is empty
    }

    char item_state(){
        return state;
    }

    void create_can(){
        this->state = 'c';
    }

    void create_wall(){
        this->state = 'w';
    }

    void remove_can(){
        this->state = 'e';
    }
};

class World{
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


