#include "../include/Node.hpp"
//#include <iostream>

long Node::global_node_id = 0;

// Constructors
Node::Node()
{

}

Node::Node(unsigned short state[9], double g_value, unsigned short parent_state[9])
{
    // Make Node state
    for(int i = 0; i < 9; i++)
        this->state[i] = state[i];

    // Make Node parent state
    for(int i = 0; i < 9; i++)
        this->parent_state[i] = parent_state[i];

    // Calculate number of successors
    this->number_of_succs = this->calculate_number_of_succs();

    // Calculate heuristic
    this->h_value = this->calculate_heuristic();

    // Sets the g value
    this->g_value = g_value;

    // Sets f value
    this->f_value = this->g_value + this->h_value;

    // Calculates blank space index
    this->blank_index = this->calculate_blank_index();

    this->node_id = global_node_id;
    global_node_id++;
}

// Getters
unsigned short* Node::get_state()
{
    return this->state;
}
unsigned short* Node::get_parent_state()
{
    return this->parent_state;
}

unsigned short Node::get_number_of_succs()
{
    return this->number_of_succs;
}

double Node::get_f_value()
{
    return this->f_value;
}

double Node::get_g_value()
{
    return this->g_value;
}

double Node::get_h_value()
{
    return this->h_value;
}

unsigned short Node::get_blank_index()
{
    return this->blank_index;
}

// Setters
void Node::set_state(unsigned short state[9])
{
    for(int i = 0; i < 9; i++)
        this->state[i] = state[i];
}

unsigned short Node::calculate_number_of_succs()
{
    int blank_index = -1;

    for(int i = 0; i < 9; i++)
    {
        if(this->state[i]== 0)
        {
            blank_index = i;
            break;
        }
    }

    switch(blank_index)
    {
        case 4:
            return 4;

        case 0:
        case 2:
        case 6:
        case 8:
            return 2;
        
        case 1:
        case 3:
        case 5:
        case 7:
            return 3;
    }

    return -1;
}

void Node::get_x_y_coords(int number, int coords[2])
{
    coords[0] = number / 3; // Calculates vertical coord
    coords[1] = number % 3; // Calculates horizontal coord
}

double Node::calculate_heuristic()
{
    int sum = 0;
    int difference;
    int vertical_moves;
    int horizontal_moves;

    int current_coords[2];
    int destination_coords[2];

    for(int i = 0; i < 9; i++)
    {
        // Dont count the blank space
        if (this->state[i] == 0)
            continue;

        Node::get_x_y_coords(i, current_coords);
        Node::get_x_y_coords(this->state[i], destination_coords);

        vertical_moves = current_coords[0] - destination_coords[0];
        horizontal_moves = current_coords[1] - destination_coords[1];

        if(vertical_moves < 0) vertical_moves*= (-1); // Make it positive
        if(horizontal_moves < 0) horizontal_moves*= (-1); // Make it positive

        sum += vertical_moves + horizontal_moves;
    }

    return sum;
}

void Node::calculate_succs_states(unsigned short succs_states[4][9])
{
    unsigned short succ_number = 0; // Store which succ we are computating
    int coords[2]; // Blank space's vertical and horizontal coords

    get_x_y_coords(this->blank_index, coords);

    // Attempt to generate 'upward blank movement' succ
    if(coords[0] > 0)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index - 3);
        succ_number++;
    }

    // Attempt to generate 'left blank movement' succ
    if(coords[1] > 0)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index - 1);
        succ_number++;
    }

    // Attempt to generate 'right blank movement' succ
    if(coords[1] < 2)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index + 1);
        succ_number++;
    }

    // Attempt to generate 'downward blank movement' succ
    if(coords[0] < 2)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index + 3);
        succ_number++;
    }
}

unsigned short Node::calculate_blank_index()
{
    for(int i = 0; i < 9; i++)
        if(this->state[i] == 0)
            return i;

    return -1;
}

void Node::switch_blank_position(unsigned short new_state[], unsigned short new_blank_index)
{
    unsigned short temp;

    // Copy state to new state variable
    for(int i = 0; i < 9; i++)
        new_state[i] = this->state[i];

    // Make the swap
    temp = this->state[new_blank_index];
    new_state[new_blank_index] = 0;
    new_state[this->blank_index] = temp;
}

bool Node::is_goal()
{
    return this->h_value == 0;
}

bool Node::is_states_equal(unsigned short state1[9], unsigned short state2[9])
{
    for(int i = 0; i < 9; i++)
        if(state1[i] != state2[i])
            return false;

    return true;
}
