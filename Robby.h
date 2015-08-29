#ifndef ROBBY_H
#define ROBBY_H

#define GENE_LENGTH 243
#define SITUATIONS_ACTIONS 6

class Robby
{
private:
    char situation_table_and_genes[GENE_LENGTH][SITUATIONS_ACTIONS]; // array containing the 243 situations and genes
    int current_horizontal;
    int current_vertical;
    int fitness_level;

public:
    Robby();

    bool set_w_current = false;
    char west_setting = 'e'; // letter used to help set west column
    char east_setting = 'e'; // letter used to help set west column
    int east_w_count = 0;

    char gene_from(int gene_to_return);
    void gene_change(int gene_location, char gene_to_insert);
    void found_can();
    void can_does_not_exist();
    void move_north();
    void move_south();
    void move_east();
    void move_west();
    void hit_wall();
    void reset_postion_to_home();
    int current_fitness();
    void set_up_situation_table();
    int horizontal_position();
    int vertical_position();
    int situation_table_lookup(char north, char south, char east, char west, char current);
    void print_situation_table();

};

#endif