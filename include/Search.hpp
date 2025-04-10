#include "../include/Node.hpp"
//#include <chrono>
#include <string>

typedef struct search_return_info {
    int number_of_expanded_nodes;
    int cost;
    //std::chrono::duration<double> time_elapsed;
    float mean_h_value;
    float initial_state_h;
} SEARCH_INFO;

std::string state_to_string(unsigned short state[9]);
SEARCH_INFO bfs(Node root);
SEARCH_INFO gbfs(Node root);
