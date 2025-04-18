#include "../include/Node_15.hpp"

long Node_15::global_node_id = 0;

// Constructors
Node_15::Node_15()
{

}

Node_15::Node_15(long long state, double g_value, long long parent_state)
{
    // Make Node state
    this->state = state;

    // Make Node parent state
    this->parent_state = parent_state;

    // Calculate number of successors
    this->number_of_succs = this->calculate_number_of_succs();

    // Calculate heuristic
    this->h_value = this->calculate_heuristic();

    // Sets the g value
    this->g_value = g_value;

    // Calculates blank space index
    this->blank_index = this->calculate_blank_index();

    this->node_id = global_node_id;
    global_node_id++;
}

// Getters
long long Node_15::get_state()
{
    return this->state;
}

long long Node_15::get_parent_state()
{
    return this->parent_state;
}

unsigned short Node_15::get_number_of_succs()
{
    return this->number_of_succs;
}

double Node_15::get_g_value()
{
    return this->g_value;
}

double Node_15::get_h_value()
{
    return this->h_value;
}

unsigned short Node_15::get_blank_index()
{
    return this->blank_index;
}

// Setters
void Node_15::set_state(long long state)
{
    this->state = state;
}

unsigned short Node_15::calculate_number_of_succs()
{
    int blank_index = -1;

    unsigned short state[16];
    get_array_from_long_long(this->get_state(), state);

    for(int i = 0; i < 16; i++)
    {
        if(state[i]== 0)
        {
            blank_index = i;
            break;
        }
    }

    switch(blank_index)
    {
        case 5:
        case 6:
        case 9:
        case 10:
            return 4;

        case 0:
        case 3:
        case 12:
        case 15:
            return 2;
        
        case 1:
        case 2:
        case 4:
        case 7:
        case 8:
        case 11:
        case 13:
        case 14:
            return 3;
    }

    return -1;
}

void Node_15::get_x_y_coords(int number, int coords[2])
{
    coords[0] = number / 4; // Calculates vertical coord
    coords[1] = number % 4; // Calculates horizontal coord
}

double Node_15::calculate_heuristic()
{
    int sum = 0;
    int difference;
    int vertical_moves;
    int horizontal_moves;

    int current_coords[2];
    int destination_coords[2];

    unsigned short state[16];
    get_array_from_long_long(this->get_state(), state);

    for(int i = 0; i < 16; i++)
    {
        // Dont count the blank space
        if (state[i] == 0)
            continue;

        Node_15::get_x_y_coords(i, current_coords);
        Node_15::get_x_y_coords(state[i], destination_coords);

        vertical_moves = current_coords[0] - destination_coords[0];
        horizontal_moves = current_coords[1] - destination_coords[1];

        if(vertical_moves < 0) vertical_moves*= (-1); // Make it positive
        if(horizontal_moves < 0) horizontal_moves*= (-1); // Make it positive

        sum += vertical_moves + horizontal_moves;
    }

    return sum;
}

void Node_15::calculate_succs_states(unsigned short succs_states[4][16])
{
    unsigned short succ_number = 0; // Store which succ we are computating
    int coords[2]; // Blank space's vertical and horizontal coords

    get_x_y_coords(this->blank_index, coords);

    // Attempt to generate 'upward blank movement' succ
    if(coords[0] > 0)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index - 4);
        succ_number++;
    }

    // Attempt to generate 'left blank movement' succ
    if(coords[1] > 0)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index - 1);
        succ_number++;
    }

    // Attempt to generate 'right blank movement' succ
    if(coords[1] < 3)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index + 1);
        succ_number++;
    }

    // Attempt to generate 'downward blank movement' succ
    if(coords[0] < 3)
    {
        this->switch_blank_position(succs_states[succ_number], blank_index + 4);
        succ_number++;
    }
}

unsigned short Node_15::calculate_blank_index()
{
    unsigned short state[16];
    get_array_from_long_long(this->get_state(), state);

    for(int i = 0; i < 16; i++)
        if(state[i] == 0)
            return i;

    return -1;
}

void Node_15::switch_blank_position(unsigned short new_state[16], unsigned short new_blank_index)
{
    unsigned short temp;
    unsigned short state[16];
    get_array_from_long_long(this->get_state(), state);

    // Copy state to new state variable
    for(int i = 0; i < 16; i++)
        new_state[i] = state[i];

    // Make the swap
    temp = state[new_blank_index];
    new_state[new_blank_index] = 0;
    new_state[this->blank_index] = temp;
}

bool Node_15::is_goal()
{
    return this->h_value == 0;
}

bool Node_15::is_states_equal(long long state1, long long state2)
{
    return state1 == state2;
}


unsigned short Node_15::get_index_from_long_long(long long state, unsigned short tile_number)
{
    long long mask;
    long long unformatted_result;

    mask = 0xF << (4*tile_number);

    unformatted_result = mask & state;

    for(int i = 0; i < 4*tile_number; i++)
        unformatted_result /= 2;

    return (unsigned short) unformatted_result;    
}

long long Node_15::get_long_long_from_array(unsigned short state[16])
{
    long long state_15 = 0;
    unsigned short tile_number;

    for(long long i = 0; i < 16; i++)
    {
        tile_number = state[i];

        state_15 |= i << (4*tile_number);
    }

    return state_15;
}

void Node_15::get_array_from_long_long(unsigned long long state_15, unsigned short state[16])
{

    unsigned long long index_of_i;
    unsigned long long mask;
    unsigned char bits = 15;

    for(int i = 0; i < 16; i++)
    {
        mask = (static_cast<unsigned long long>(bits) << (4*i));

        index_of_i = state_15 & mask;

        index_of_i = index_of_i >> (4*i);

        state[index_of_i] = i;
    }
}