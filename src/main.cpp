#include <iostream>
#include "../include/Search.hpp"
//#include <vector>
//#include <algorithm>

void test1()
{
    unsigned short state[9] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8};

    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};

    unsigned short succ_states[4][9]; 
        
    Node node = Node(state, 0, parent_state);
    node.calculate_succs_states(succ_states);

    std::cout << "Heuristic: " << node.get_h_value() << std::endl;
    std::cout << "Succs: " << node.get_number_of_succs() << std::endl;
    std::cout << "Blank space index: " << node.get_blank_index() << std::endl;

    for(int i = 0; i < node.get_number_of_succs(); i++)
    {
        for(int j = 0; j < 9; j++)
            std::cout << succ_states[i][j] << " ";

        std::cout << std::endl;
    }
}

void bfs_test()
{
    unsigned short state[9] = {
        5, 0, 2,
        6, 4, 8,
        1, 7, 3};

    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};

    // 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
    SEARCH_INFO return_info;

    // BFS
    //auto start = std::chrono::high_resolution_clock::now();
    return_info = bfs(Node(state, 0, parent_state));
    //auto stop = std::chrono::high_resolution_clock::now();
    //return_info.time_elapsed = stop - start;
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Expanded nodes: " << return_info.number_of_expanded_nodes << std::endl;
    std::cout << "Cost: " << return_info.cost << std::endl;
    //std::cout << "Time elapsed: " << duration.count() << std::endl;
    std::cout << "Mean h value: " << return_info.mean_h_value << std::endl;
    std::cout << "Initial state h: " << return_info.initial_state_h << std::endl;
}

void gbfs_test()
{
    unsigned short state[9] = {
        0, 6, 1,
        7, 4, 2,
        3, 8, 5};

    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};

    // 0 6 1 7 4 2 3 8 5,           expandiu 17 ao inves de 16
    // 5 0 2 6 4 8 1 7 3, 
    // 2 4 7 0 3 6 8 1 5            Certo
    SEARCH_INFO return_info;

    // GBFS
    //auto start = std::chrono::high_resolution_clock::now();
    return_info = gbfs(Node(state, 0, parent_state));
    //auto stop = std::chrono::high_resolution_clock::now();
    //return_info.time_elapsed = stop - start;
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Expanded nodes: " << return_info.number_of_expanded_nodes << std::endl;
    std::cout << "Cost: " << return_info.cost << std::endl;
    //std::cout << "Time elapsed: " << duration.count() << std::endl;
    std::cout << "Mean h value: " << return_info.mean_h_value << std::endl;
    std::cout << "Initial state h: " << return_info.initial_state_h << std::endl;
}

int main(int argc, char *argv[])
{
    gbfs_test();
}