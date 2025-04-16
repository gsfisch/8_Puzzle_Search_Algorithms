#include <iostream>
#include <chrono>
#include <string.h>
#include "../include/Search.hpp"

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
        0, 6, 1,
        7, 4, 2,
        3, 8, 5};

    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};

    // 0 6 1 7 4 2 3 8 5, 
    //5 0 2 6 4 8 1 7 3, 
    //2 4 7 0 3 6 8 1 5
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

void a_star_test()
{
    unsigned short state[9] = {
        5, 0, 2,
        6, 4, 8,
        1, 7, 3};

    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};

    // 0 6 1 7 4 2 3 8 5, 
    // 5 0 2 6 4 8 1 7 3, 
    // 2 4 7 0 3 6 8 1 5 
    SEARCH_INFO return_info;

    // GBFS
    //auto start = std::chrono::high_resolution_clock::now();
    return_info = a_star(Node(state, 0, parent_state));
    //auto stop = std::chrono::high_resolution_clock::now();
    //return_info.time_elapsed = stop - start;
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Expanded nodes: " << return_info.number_of_expanded_nodes << std::endl;
    std::cout << "Cost: " << return_info.cost << std::endl;
    //std::cout << "Time elapsed: " << duration.count() << std::endl;
    std::cout << "Mean h value: " << return_info.mean_h_value << std::endl;
    std::cout << "Initial state h: " << return_info.initial_state_h << std::endl;
}

void ida_star_test()
{
    unsigned short state[9] = {
        0, 6, 1,
        7, 4, 2,
        3, 8, 5};

    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};

    // 0 6 1 7 4 2 3 8 5, 
    // 5 0 2 6 4 8 1 7 3, 
    // 2 4 7 0 3 6 8 1 5 
    SEARCH_INFO return_info;

    // GBFS
    //auto start = std::chrono::high_resolution_clock::now();
    return_info = ida_star(Node(state, 0, parent_state));
    //auto stop = std::chrono::high_resolution_clock::now();
    //return_info.time_elapsed = stop - start;
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Expanded nodes: " << return_info.number_of_expanded_nodes << std::endl;
    std::cout << "Cost: " << return_info.cost << std::endl;
    //std::cout << "Time elapsed: " << duration.count() << std::endl;
    std::cout << "Mean h value: " << return_info.mean_h_value << std::endl;
    std::cout << "Initial state h: " << return_info.initial_state_h << std::endl;
}

void idfs_test()
{
    unsigned short state[9] = {
        0, 6, 1,
        7, 4, 2,
        3, 8, 5};

    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};

    // 0 6 1 7 4 2 3 8 5, 
    // 5 0 2 6 4 8 1 7 3, 
    // 2 4 7 0 3 6 8 1 5 
    SEARCH_INFO return_info;

    // GBFS
    //auto start = std::chrono::high_resolution_clock::now();
    return_info = idfs(Node(state, 0, parent_state));
    //auto stop = std::chrono::high_resolution_clock::now();
    //return_info.time_elapsed = stop - start;
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Expanded nodes: " << return_info.number_of_expanded_nodes << std::endl;
    std::cout << "Cost: " << return_info.cost << std::endl;
    //std::cout << "Time elapsed: " << duration.count() << std::endl;
    std::cout << "Mean h value: " << return_info.mean_h_value << std::endl;
    std::cout << "Initial state h: " << return_info.initial_state_h << std::endl;
}

int find_puzzle_type(int argc, char *argv[])
{
    int puzzle;

    for(int i = 0; i < argc; i++)
    {
        std::string str(argv[i]);

        if (str.find("10") != std::string::npos)
        {
            puzzle = 15;
            break;
        }
        
        puzzle = 8;
    }

    return puzzle;
}

int main(int argc, char *argv[])
{
    int puzzle_type;
    int puzzle_amount;
    unsigned short state[9];
    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};
    SEARCH_INFO return_info;
    std::chrono::microseconds duration;
    std::chrono::seconds duration_sec;

    // Calculate puzzle type and puzzle amount from input
    puzzle_type = find_puzzle_type(argc, argv);
    puzzle_amount =  ((argc - 2) / (puzzle_type + 1));

    //std::cout << puzzle_type << std::endl;
    //std::cout << puzzle_amount << std::endl;

    // For each game...
    for(int i = 0; i < puzzle_amount; i++)
    {
        // Get state from input
        for (int j = 0; j < 9; j++)
        {
            state[j] = *argv[i*9 + j + 2] - 48;
        }

        // 8 Puzzle
        if(puzzle_type == 8)
        {
            // Select Search Algorithm
            // BFS
            if(!strcmp(argv[1], "-bfs"))
            {
                auto start = std::chrono::high_resolution_clock::now();
                return_info = bfs(Node(state, 0, parent_state));
                auto stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            }

            // GBFS
            else if(!strcmp(argv[1], "-gbfs"))
            {
                auto start = std::chrono::high_resolution_clock::now();
                return_info = gbfs(Node(state, 0, parent_state));
                auto stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            }

            // A*
            else if(!strcmp(argv[1], "-astar"))
            {
                auto start = std::chrono::high_resolution_clock::now();
                return_info = a_star(Node(state, 0, parent_state));
                auto stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            }

            // IDA*
            else if(!strcmp(argv[1], "-idastar"))
            {
                auto start = std::chrono::high_resolution_clock::now();
                return_info = ida_star(Node(state, 0, parent_state));
                auto stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            }

            // IDFS
            else if(!strcmp(argv[1], "-idfs"))
            {
                auto start = std::chrono::high_resolution_clock::now();
                return_info = idfs(Node(state, 0, parent_state));
                auto stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            }

            // Show results
            std::cout << return_info.number_of_expanded_nodes << " ";
            std::cout << return_info.cost << " ";
            std::cout << duration.count() << " ";
            std::cout << return_info.mean_h_value << " ";
            std::cout << return_info.initial_state_h << std::endl;
        }

        // A* for 15 Puzzle
        else
        {
            // TODO
        }
    }

    return 0;
}

/* 
// Driver for instances file
// Example call:
// ./main -bfs
int main(int argc, char *argv[])
{
    std::ifstream input("instances/8puzzle_instances.txt");
    unsigned short state[9];
    unsigned short parent_state[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0};
    SEARCH_INFO return_info;
    std::chrono::microseconds duration;
    std::chrono::seconds duration_sec;

    // Read each line's first element
    while(input >> state[0])
    {
        // Fill the last elements
        for(int i = 1; i < 9; i++)
            input >> state[i];

        // BFS
        if(!strcmp(argv[1], "-bfs"))
        {
            auto start = std::chrono::high_resolution_clock::now();
            return_info = bfs(Node(state, 0, parent_state));
            auto stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }

        // GBFS
        else if(!strcmp(argv[1], "-gbfs"))
        {
            auto start = std::chrono::high_resolution_clock::now();
            return_info = gbfs(Node(state, 0, parent_state));
            auto stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }

        // A*
        else if(!strcmp(argv[1], "-astar"))
        {
            auto start = std::chrono::high_resolution_clock::now();
            return_info = a_star(Node(state, 0, parent_state));
            auto stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }

        // IDA*
        else if(!strcmp(argv[1], "-idastar"))
        {
            auto start = std::chrono::high_resolution_clock::now();
            return_info = ida_star(Node(state, 0, parent_state));
            auto stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }

        // IDFS
        else if(!strcmp(argv[1], "-idfs"))
        {
            auto start = std::chrono::high_resolution_clock::now();
            return_info = idfs(Node(state, 0, parent_state));
            auto stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        }

        std::cout << return_info.number_of_expanded_nodes << " ";
        std::cout << return_info.cost << " ";
        std::cout << duration.count() << " ";
        std::cout << return_info.mean_h_value << " ";
        std::cout << return_info.initial_state_h << std::endl;
    }

    return 0;
}
*/