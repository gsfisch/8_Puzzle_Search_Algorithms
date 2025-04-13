#include "../include/Node.hpp"
#include <chrono>
#include <string>

typedef struct search_return_info {
    int number_of_expanded_nodes;
    int cost;
    std::chrono::duration<double> time_elapsed;
    float mean_h_value;
    float initial_state_h;
    float f_limit;
} SEARCH_INFO;

std::string state_to_string(unsigned short state[9]);
SEARCH_INFO bfs(Node root);
SEARCH_INFO gbfs(Node root);
SEARCH_INFO a_star(Node root);
SEARCH_INFO ida_star(Node root);
void recursive_search(Node root, float f_limit, SEARCH_INFO *return_info);
SEARCH_INFO idfs(Node root);
void depth_limited_search(Node root, int i, SEARCH_INFO *return_info);
