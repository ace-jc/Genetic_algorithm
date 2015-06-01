#include <iostream>
#include <stdlib.h>

#define ARRAY_SQUARE_SIZE 10
#define GENE_LENGTH 243
#define ROBBY_AMT 2

using namespace std;

class Robby{
private:
    int genes[GENE_LENGTH]; // array containing the 243 genes
    int current_horizontal;
    int current_vertical;
    int gene_read_position;
    // genes are defined as follows:
    // 0 is move north
    // 1 is move south
    // 2 is move east
    // 3 is move west
    // 4 is choose random location to move in
    // 5 is stay put
    // 6 is bend down and get can

public:
    Robby(){
        initial_create_genes();
        current_horizontal = 0;
        current_vertical = 0;
        gene_read_position = 0;
    }

    int read_gene(){
        int temp = genes[gene_read_position];
        gene_read_position++; // increasing the position of the gene reader
        return temp;
    }

    int horizontal_position(){
        return current_horizontal;
    }

    int vertical_position(){
        return current_vertical;
    }

    void initial_create_genes(){
        for(int i=0; i<GENE_LENGTH; i++){
            int random_gene = rand()%7; // 0 - 6
            genes[i] = random_gene;
        }
    }

    //for diagnostics
    void print_genes(){
        cout << "Genes are: ";
        for(int i=0; i<GENE_LENGTH; i++){
            cout << genes[i];
        }
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

};

class World{
private:
    Items world_map_ptr[ARRAY_SQUARE_SIZE][ARRAY_SQUARE_SIZE];
    Robby list_of_robbies[ROBBY_AMT];

    void add_cans(int cans_to_add){
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
        add_cans(cans);
    }

    void print_world(){
        for(int i=0; i<ARRAY_SQUARE_SIZE; i++){
            for(int j=0; j<ARRAY_SQUARE_SIZE; j++){
                cout << world_map_ptr[i][j].item_state();
            }
            cout << endl;
        }
    }

    void tick_time(){
        // moving time forward
        int array_size = (sizeof(list_of_robbies)/ sizeof(list_of_robbies[0]));

        for(int i=0; i<array_size; i++){
            int hori = list_of_robbies[i].horizontal_position();
            int vert = list_of_robbies[i].vertical_position();
            int current_gene = list_of_robbies[i].read_gene();
        }
    }

};

int main()
{
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

    world_ptr->tick_time();


    delete world_ptr;
    return 0;
}
