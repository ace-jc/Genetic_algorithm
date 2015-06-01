#include <iostream>

#define array_square_size 10

using namespace std;

class Items{
    char state;

public:
    Items(){
        state = '.'; // is empty
    }

    char print_item(){
        return state;
    }

};

class World{
    Items world_map_ptr[array_square_size][array_square_size];

public:
    World(){
        create_world();
    }

    void create_world(){
        for(int i=0; i<array_square_size; i++){
            for(int j=0; j<array_square_size; j++){
                cout << world_map_ptr[i][j].print_item();
            }
            cout << endl;
        }


    }

};

int main()
{
    cout << "Array Square Size: " << array_square_size << endl;

    World *world_ptr = new World();

    delete world_ptr;


    return 0;
}
