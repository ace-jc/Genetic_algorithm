#include <iostream>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SQUARE_SIZE 12 // without walls it is -2 in size
#define GENE_LENGTH 243
#define ROBBY_AMT 1
#define CLEANING_SESSIONS 100 // per Robby
#define SITUATIONS_ACTIONS 6
#define CANS_COUNT 50

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
//        situation_table_and_genes[1][1] = 'e';
    }

    bool set_w_current = false;
    char west_setting = 'e'; // letter used to help set west column
    char east_setting = 'e'; // letter used to help set west column
    int east_w_count = 0;

    void reset_postion_to_home(){
        this->current_horizontal = 1;
        this->current_vertical = 1;
    }

    void set_up_situation_table(){
        for(int i=0; i<GENE_LENGTH; i++){
            for(int j=0; j<SITUATIONS_ACTIONS; j++){
                if(j==5){
                    // random gene area
                    // setting 0-6 in ascii char
                    situation_table_and_genes[i][j] = (char)((rand()%7)+48);
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
//            cout << "north: " << north << endl;
//            cout << "south: " << south << endl;
//            cout << "east: " << east << endl;
//            cout << "west: " << west << endl;
//            cout << "current: " << current << endl;

            if(situation_table_and_genes[i][0] == north &&
               situation_table_and_genes[i][1] == south &&
               situation_table_and_genes[i][2] == east &&
               situation_table_and_genes[i][3] == west &&
               situation_table_and_genes[i][4] == current){

//                cout << "situation_table_and_genes[i][0]:" << situation_table_and_genes[i][0] << endl;
//                cout << "situation_table_and_genes[i][1]:" << situation_table_and_genes[i][1] << endl;
//                cout << "situation_table_and_genes[i][2]:" << situation_table_and_genes[i][2] << endl;
//                cout << "situation_table_and_genes[i][3]:" << situation_table_and_genes[i][3] << endl;
//                cout << "situation_table_and_genes[i][4]:" << situation_table_and_genes[i][4] << endl;
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

    void print_world(){
        for(int i=0; i<ARRAY_SQUARE_SIZE; i++){
            for(int j=0; j<ARRAY_SQUARE_SIZE; j++){
                cout << world_map_ptr[i][j].item_state();
            }
            cout << endl;
        }
        cout << endl;
    }

    void print_robby(){
        for(int i=0; i<ROBBY_AMT; i++){
            cout << "Robby num: " << i << endl;
            this_robby.print_situation_table();
        }
        cout << endl;
    }

    void robby_step(){
        // moving time forward
        int horizontal = this_robby.horizontal_position();
        int vertical = this_robby.vertical_position();

        char north = world_map_ptr[horizontal][vertical-1].item_state();
        char south = world_map_ptr[horizontal][vertical+1].item_state();
        char east = world_map_ptr[horizontal+1][vertical].item_state();
        char west = world_map_ptr[horizontal-1][vertical].item_state();
        char current = world_map_ptr[horizontal][vertical].item_state();

        int robby_action = this_robby.situation_table_lookup(north, south, east, west, current);


    }

};


int main()
{
    srand(time(0));
    int can_num = CANS_COUNT;
    World *world_ptr = new World(can_num);

    world_ptr->print_world();
    world_ptr->print_robby();

    world_ptr->robby_step();

    // later size of worlds
//    int array_size = (sizeof(list_of_robbies)/ sizeof(list_of_robbies[0]));

    delete world_ptr;
    return 0;
}
