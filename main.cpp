#include <iostream>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SQUARE_SIZE 12 // without walls it is -2 in size
#define GENE_LENGTH 243
#define ROBBY_AMT 1
#define CLEANING_SESSIONS 100 // per Robby
#define SITUATIONS_ACTIONS 6

using namespace std;

class Robby{
private:
    char situation_table_and_genes[GENE_LENGTH][SITUATIONS_ACTIONS]; // array containing the 243 situations and genes
    int current_horizontal;
    int current_vertical;

    // gene actions are defined as follows:
    // 0 is move north
    // 1 is move south
    // 2 is move east
    // 3 is move west
    // 4 is choose random location to move in
    // 5 is stay put
    // 6 is bend down and get can

public:
    Robby(){
        current_horizontal = 1; // to avoid wall at 0
        current_vertical = 1; // to avoid wall at 0
        set_up_situation_table();
    }

    void set_up_situation_table(){
        for(int i=0; i<GENE_LENGTH; i++){
            for(int j=0; j<SITUATIONS_ACTIONS; j++){
                situation_table_and_genes[1][1] = 'r';
            }
        }
    }

    void print_situation_table(){
        for(int i=0; i<GENE_LENGTH; i++){
            for(int j=0; j<SITUATIONS_ACTIONS; j++){
                cout << "HERE!!" << endl;
                cout << situation_table_and_genes[i][j];
            }
        }
        cout << endl;
    }

    int horizontal_position(){
        return current_horizontal;
    }

    int vertical_position(){
        return current_vertical;
    }

};

class Items{
private:
    char state;

public:
    Items(){
        state = '.'; // is empty
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
    Robby list_of_robbies[ROBBY_AMT];

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
            }while(world_map_ptr[horizontal][vertical].item_state() != '.');
            world_map_ptr[horizontal][vertical].create_can();
        }
    }

public:
    World(int cans){
        add_cans_and_walls(cans); // creating world
        setup_robbies_situation_table(); // setting up the situation table
    }

    void print_world(){
        for(int i=0; i<ARRAY_SQUARE_SIZE; i++){
            for(int j=0; j<ARRAY_SQUARE_SIZE; j++){
                cout << world_map_ptr[i][j].item_state();
            }
            cout << endl;
        }
    }

    void setup_robbies_situation_table(){
        for(int i=0; i<GENE_LENGTH; i++){
            list_of_robbies[i].set_up_situation_table();
        }
    }

    void print_robbies(){
        for(int i=0; i<ROBBY_AMT; i++){
            cout << "Robby num: " << i << endl;
            list_of_robbies[i].print_situation_table();
        }
    }

    void tick_time(){
        // moving time forward
        int array_size = (sizeof(list_of_robbies)/ sizeof(list_of_robbies[0]));

//        for(int i=0; i<array_size; i++){
//            // for each Robby position
//            for(int j=0; j<CLEANING_SESSIONS; j++){
//                // all of the cleaning sessions per Robby
//                int hori = list_of_robbies[i].horizontal_position();
//                int vert = list_of_robbies[i].vertical_position();
//                int current_gene = list_of_robbies[i].read_gene();
//
////                cout << "i: " << i << " current_gene: " << current_gene << endl;
//            }
//
//
//        }
    }

};


int main()
{
    srand(time(0));
    int can_num = 0;
    cout << "Array Square Size: " << ARRAY_SQUARE_SIZE << endl;
    do{
       cout << "Cans to add? (must be less than " << ARRAY_SQUARE_SIZE*ARRAY_SQUARE_SIZE+1
            << ")" << endl;
       cin >> can_num;
    }while(can_num > ARRAY_SQUARE_SIZE*ARRAY_SQUARE_SIZE);
    cout << endl;

    World *world_ptr = new World(can_num);
    world_ptr->print_world();
    world_ptr->print_robbies();

    for(int i=0; i<GENE_LENGTH; i++){
        world_ptr->tick_time();
    }



    delete world_ptr;
    return 0;
}
