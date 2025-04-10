#include "../include/Search.hpp"
#include <queue>
#include <string>
#include <unordered_map>

struct compare_nodes {
    bool operator()(Node node1, Node node2) {

        // Best H
        if(node1.get_h_value() != node2.get_h_value())
            return node1.get_h_value() > node2.get_h_value();

        // Best G
        if(node1.get_g_value() != node2.get_g_value())
            return node1.get_g_value() < node2.get_g_value();

        return true;
    }
};

std::string state_to_string(unsigned short state[9])
{
    std::string result = "";

    for(int i = 0; i < 9; i++)
        result += state[i] + 48;

    return result;
}

SEARCH_INFO bfs(Node root)
{
    std::queue<Node> q;
    std::unordered_map<std::string, bool> closed;
    unsigned short current_node_neighbors[4][9];
    SEARCH_INFO return_info;

    return_info.initial_state_h = root.get_h_value();
    return_info.mean_h_value = 0;
    return_info.cost = 0;
    return_info.number_of_expanded_nodes = 0;

    q.push(root);

    while(!q.empty())
    {
        // Expand next node
        Node current_node = q.front();
        q.pop();
        return_info.number_of_expanded_nodes++;

        //explored.push_back(current_node);

        // Check if it has been explored before
        //if(std::find(explored.begin(), explored.end(), current_node) != explored.end())
        //    continue;
        //if(closed.count(state_to_string(current_node.get_state())) == 0)
        if(closed[state_to_string(current_node.get_state())])
            continue;

        closed[state_to_string(current_node.get_state())] = true;

        // Check if it is goal
        if(current_node.is_goal())
        {
            return_info.cost = current_node.get_g_value();
            return return_info;
        }

        // Compute neighbors
        current_node.calculate_succs_states(current_node_neighbors);

        // Add neighbors to the queue
        for(int i = 0; i < current_node.get_number_of_succs(); i++)
        {
            // Add non parent state to the queue
            if(!Node::is_states_equal(current_node_neighbors[i], current_node.get_parent_state()))
                q.push(Node(current_node_neighbors[i], current_node.get_g_value() + 1, current_node.get_state()));
        }
    }

    return_info.cost = -1;
    return return_info;
}

SEARCH_INFO gbfs(Node root)
{
    std::priority_queue<Node, std::vector<Node>, compare_nodes> q;
    std::unordered_map<std::string, float> closed;
    unsigned short current_node_neighbors[4][9];
    SEARCH_INFO return_info;

    return_info.initial_state_h = root.get_h_value();
    return_info.mean_h_value = 0;
    return_info.cost = 0;
    return_info.number_of_expanded_nodes = 0;

    q.push(root);

    while(!q.empty())
    {
        // Expand next node
        Node current_node = q.top();
        q.pop();
        return_info.number_of_expanded_nodes++;

        //if(closed[state_to_string(current_node.get_state())])
        if(closed.count(state_to_string(current_node.get_state())) && 
        closed[state_to_string(current_node.get_state())] <= current_node.get_g_value())
            continue;

        //closed[state_to_string(current_node.get_state())] = true;
        closed[state_to_string(current_node.get_state())] = current_node.get_g_value();

        // Check if it is goal
        if(current_node.is_goal())
        {
            return_info.cost = current_node.get_g_value();
            return return_info;
        }

        // Compute neighbors
        current_node.calculate_succs_states(current_node_neighbors);

        // Add neighbors to the queue
        for(int i = 0; i < current_node.get_number_of_succs(); i++)
        {
            // Add non parent state to the queue
            if(!Node::is_states_equal(current_node_neighbors[i], current_node.get_parent_state()))
                q.push(Node(current_node_neighbors[i], current_node.get_g_value() + 1, current_node.get_state()));
        }
    }

    return_info.cost = -1;
    return return_info;
}
