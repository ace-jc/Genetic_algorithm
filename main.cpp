#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Items.h"
#include "Robby.h"
#include "World.h"


#define WORLDS_ROBBY_COMBINATIONS 100 // needs to be divisible by KEEP_TOP evenly
#define CANS_COUNT 50
#define LOOPS 1000
#define KEEP_TOP 20

using namespace std;


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