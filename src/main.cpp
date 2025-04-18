#include <iostream>
#include <chrono>
#include <string.h>
#include "../include/Search.hpp"
#include <fstream>

/* 
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
    unsigned short state_15[16];
    unsigned short parent_state_15[16] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0};
    SEARCH_INFO return_info;
    std::chrono::microseconds duration;
    std::chrono::microseconds duration_15;
    std::chrono::seconds duration_sec;

    // Calculate puzzle type and puzzle amount from input
    puzzle_type = find_puzzle_type(argc, argv);
    puzzle_amount =  ((argc - 2) / (puzzle_type + 1));

    // 8 Puzzle
    if(puzzle_type == 8)
    {
        // For each game...
        for(int i = 0; i < puzzle_amount; i++)
        {
            // Get state from input
            for (int j = 0; j < 9; j++)
            {
                state[j] = *argv[i*9 + j + 2] - 48;
            }

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
    }
   
    // 15 Puzzle
    else
    {
        // For each game...
        for(int i = 0; i < puzzle_amount; i++)
        {
            // Get state from input
            for (int j = 0; j < 16; j++)
            {
                state_15[j] = std::stoi(argv[i*16 + j + 2]); 
            }
            
            auto start = std::chrono::high_resolution_clock::now();
            return_info = a_star_15(Node_15(Node_15::get_long_long_from_array(state_15), 0, Node_15::get_long_long_from_array(parent_state_15))); 
            auto stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            
            // Show results
            std::cout << return_info.number_of_expanded_nodes << " ";
            std::cout << return_info.cost << " ";
            std::cout << duration.count() << " ";
            std::cout << return_info.mean_h_value << " ";
            std::cout << return_info.initial_state_h << std::endl;
        }
    }

    return 0;
}


// Driver for  8 Puzzle with instances in file
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

// Driver for  8 Puzzle with instances in file
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

