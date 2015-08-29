#include <stdlib.h>
#include <iostream>
#include "Robby.h"

using namespace std;


Robby::Robby(){
    current_horizontal = 1; // to avoid wall at 0
    current_vertical = 1; // to avoid wall at 0
    set_up_situation_table();
    fitness_level = 0;
}

bool set_w_current = false;
char west_setting = 'e'; // letter used to help set west column
char east_setting = 'e'; // letter used to help set west column
int east_w_count = 0;

char Robby::gene_from(int gene_to_return){
    char output;
    output = situation_table_and_genes[gene_to_return][5];

    int random_mutation = rand()%100 + 1; //1 in 100 chance of mutation
    if(random_mutation == 1){
        output = (char)((rand()%7)+48); //+48 due to ascii storage
    }

    return output;
}

void Robby::gene_change(int gene_location, char gene_to_insert){
    this->situation_table_and_genes[gene_location][5] = gene_to_insert;
}

void Robby::found_can(){
    // found can, worth 10 points
    this->fitness_level += 10;
}

void Robby::can_does_not_exist(){
    // tried to pickup a non-existent can
    this->fitness_level--;
}

void Robby::move_north(){
    this->current_vertical -= 1;
}

void Robby::move_south(){
    this->current_vertical += 1;
}

void Robby::move_east(){
    this->current_horizontal += 1;
}

void Robby::move_west(){
    this->current_horizontal -= 1;
}


void Robby::hit_wall(){
    this->fitness_level -= 5;
}

void Robby::reset_postion_to_home(){
    this->current_horizontal = 1;
    this->current_vertical = 1;
}

int Robby::current_fitness(){
    return this->fitness_level;
}

void Robby::set_up_situation_table(){
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

int Robby::horizontal_position(){
    return current_horizontal;
}

int Robby::vertical_position(){
    return current_vertical;
}

int Robby::situation_table_lookup(char north, char south, char east, char west, char current){
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

void Robby::print_situation_table(){
    for(int i=0; i<GENE_LENGTH; i++){
        for(int j=0; j<SITUATIONS_ACTIONS; j++){
            cout << situation_table_and_genes[i][j];
        }
        cout << endl;
    }
}