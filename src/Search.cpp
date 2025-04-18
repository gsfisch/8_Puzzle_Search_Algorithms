#include "../include/Search.hpp"
#include <queue>
#include <unordered_map>
#include <string>

struct compare_nodes_bfs {
    bool operator()(Node node1, Node node2) {
        // Best G
        if(node1.get_g_value() != node2.get_g_value())
            return node1.get_g_value() > node2.get_g_value();

        if(node1.get_h_value() != node2.get_h_value())
            return node1.get_h_value() > node2.get_h_value();

        return node1.node_id > node2.node_id;
    }
};

struct compare_nodes_gbfs {
    bool operator()(Node node1, Node node2) {

        // Best H
        if(node1.get_h_value() != node2.get_h_value())
            return node1.get_h_value() > node2.get_h_value();

        // Best G
        if(node1.get_g_value() != node2.get_g_value())
            return node1.get_g_value() < node2.get_g_value();

        return node1.node_id < node2.node_id;
    }
};

struct compare_nodes_a_star {
    bool operator()(Node node1, Node node2) {

        // Best F
        if(node1.get_f_value() != node2.get_f_value())
            return node1.get_f_value() > node2.get_f_value();

        // Best H
        if(node1.get_h_value() != node2.get_h_value())
            return node1.get_h_value() > node2.get_h_value();

        return node1.node_id < node2.node_id;
    }
};

struct compare_nodes_a_star_15 {
    bool operator()(Node_15 node1, Node_15 node2) {

        // Best F
        if(node1.get_g_value() + node1.get_h_value() != node2.get_g_value() + node2.get_h_value())
            return node1.get_g_value() + node1.get_h_value() > node2.get_g_value() + node2.get_h_value();

        // Best H
        if(node1.get_h_value() != node2.get_h_value())
            return node1.get_h_value() > node2.get_h_value();

        return node1.node_id < node2.node_id;
    }
};

std::string state_to_string(unsigned short state[9])
{
    std::string result = "";

    for(int i = 0; i < 9; i++)
        result += state[i] + 48;

    return result;
}

/*
SEARCH_INFO bfs(Node root)
{
    std::priority_queue<Node, std::vector<Node>, compare_nodes_bfs> q;
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
        Node current_node = q.top();
        q.pop();

        if(closed[state_to_string(current_node.get_state())])
            continue;

        closed[state_to_string(current_node.get_state())] = true;
        return_info.number_of_expanded_nodes++;

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
*/

SEARCH_INFO bfs(Node root)
{
    std::priority_queue<Node, std::vector<Node>, compare_nodes_bfs> q;
    std::unordered_map<std::string, float> distance;
    unsigned short current_node_neighbors[4][9];
    SEARCH_INFO return_info;

    return_info.initial_state_h = root.get_h_value();
    return_info.mean_h_value = 0;
    return_info.cost = 0;
    return_info.number_of_expanded_nodes = 0;

    if(root.get_h_value() <= 32)
        q.push(root);

    while(!q.empty())
    {
        // Expand next node
        Node current_node = q.top();
        q.pop();
        
        if(distance.count(state_to_string(current_node.get_state()))
        && distance[state_to_string(current_node.get_state())] <= current_node.get_g_value())
            continue;

        
        distance[state_to_string(current_node.get_state())] = current_node.get_g_value();
        
        // Check if it is goal
        if(current_node.is_goal())
        {
            return_info.cost = current_node.get_g_value();
            return return_info;
        }
        
        return_info.number_of_expanded_nodes++;

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
    std::priority_queue<Node, std::vector<Node>, compare_nodes_gbfs> q;
    std::unordered_map<std::string, float> distance;
    unsigned short current_node_neighbors[4][9];
    SEARCH_INFO return_info;

    return_info.initial_state_h = root.get_h_value();
    return_info.mean_h_value = 0;
    return_info.cost = 0;
    return_info.number_of_expanded_nodes = 0;

    if(root.get_h_value() <= 32)
        q.push(root);

    while(!q.empty())
    {
        // Expand next node
        Node current_node = q.top();
        q.pop();
        
        if(distance.count(state_to_string(current_node.get_state())))
            continue;

        //&& distance[state_to_string(current_node.get_state())] <= current_node.get_g_value())
        
        distance[state_to_string(current_node.get_state())] = current_node.get_g_value();
        
        // Check if it is goal
        if(current_node.is_goal())
        {
            return_info.cost = current_node.get_g_value();
            return_info.mean_h_value = (double) (return_info.mean_h_value / return_info.number_of_expanded_nodes);
            return return_info;
        }
        
        return_info.mean_h_value += current_node.get_h_value();
        return_info.number_of_expanded_nodes++;

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

SEARCH_INFO a_star(Node root)
{
    std::priority_queue<Node, std::vector<Node>, compare_nodes_a_star> q;
    std::unordered_map<std::string, float> distance;
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
        
        // If better distance has been found, continue
        if(distance.count(state_to_string(current_node.get_state()))  && 
        distance[state_to_string(current_node.get_state())] <= current_node.get_g_value())
            continue;

        // Update distance
        distance[state_to_string(current_node.get_state())] = current_node.get_g_value();
        
        return_info.mean_h_value += (double) current_node.get_h_value();
        // Check if it is goal
        if(current_node.is_goal())
        {
            return_info.cost = current_node.get_g_value();
            return_info.mean_h_value /= (double) return_info.number_of_expanded_nodes;
            return return_info;
        }
        
        return_info.number_of_expanded_nodes++;
        //std::cout << current_node.get_h_value() << std::endl;
        //std::cout << return_info.mean_h_value << std::endl;

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

SEARCH_INFO ida_star(Node root)
{
    SEARCH_INFO return_info;

    return_info.initial_state_h = root.get_h_value();
    return_info.mean_h_value = 0;
    return_info.cost = 0;
    return_info.number_of_expanded_nodes = 0;
    return_info.f_limit = root.get_h_value();

    while(return_info.f_limit < 1000000000.f)
    {
        recursive_search(root, return_info.f_limit, &return_info);

        if(return_info.cost != -1)
            return return_info;
    }

    return_info.cost = -1;
    return return_info;
}

void recursive_search(Node root, float f_limit, SEARCH_INFO *return_info)
{
    unsigned short current_node_neighbors[4][9];
    float next_limit = 1000000000.f;
    
    if(root.get_f_value() > f_limit)
    {
        return_info->f_limit = root.get_f_value();
        return_info->cost = -1;
        return; 
    }
    
    if(root.is_goal())
    {
        return_info->cost = root.get_g_value();
        return_info->mean_h_value /= return_info->number_of_expanded_nodes;
        return;
    }

    root.calculate_succs_states(current_node_neighbors);
    return_info->number_of_expanded_nodes++;
    return_info->mean_h_value += root.get_h_value();

    // For each neighbor
    for(int i = 0; i < root.get_number_of_succs(); i++)
    {
        // Add non parent state to the queue
        if(!Node::is_states_equal(current_node_neighbors[i], root.get_parent_state()))
        {
            Node neighbor_node = Node(current_node_neighbors[i], root.get_g_value() + 1, root.get_state());
            recursive_search(neighbor_node, f_limit, return_info);

            if(return_info->cost != -1)
            {
                return;
            }
            if(next_limit > return_info->f_limit)
                next_limit = return_info->f_limit;
        }
    }

    return_info->cost = -1;
    return_info->f_limit = next_limit;
    return;
}

SEARCH_INFO idfs(Node root)
{
    SEARCH_INFO return_info;

    return_info.initial_state_h = root.get_h_value();
    return_info.mean_h_value = 0;
    return_info.cost = 0;
    return_info.number_of_expanded_nodes = 0;

    for(int i = 0; i < 1000000; i++)
    {
        depth_limited_search(root, i, &return_info);

        if(return_info.cost != -1)
            return return_info;
    }

    return return_info;
}

void depth_limited_search(Node root, int depth_limit, SEARCH_INFO *return_info)
{
    unsigned short current_node_neighbors[4][9];

    if(root.is_goal())
    {
        return_info->cost = root.get_g_value();
        return;
    }

    if(depth_limit > 0)
    {
        root.calculate_succs_states(current_node_neighbors);
        return_info->number_of_expanded_nodes++;

        for(int i = 0; i < root.get_number_of_succs(); i++)
        {
            if(!Node::is_states_equal(current_node_neighbors[i], root.get_parent_state()))
                depth_limited_search(Node(current_node_neighbors[i], root.get_g_value() + 1, root.get_state()), depth_limit - 1, return_info);

            if(return_info->cost != -1)
                return;
        }
    }
    
    return_info->cost = -1;

    return;
}

SEARCH_INFO a_star_15(Node_15 root)
{
    std::priority_queue<Node, std::vector<Node_15>, compare_nodes_a_star_15> q;
    std::unordered_map<std::string, float> distance;
    unsigned short current_node_neighbors[4][16];
    SEARCH_INFO return_info;

    return_info.initial_state_h = root.get_h_value();
    return_info.mean_h_value = 0;
    return_info.cost = 0;
    return_info.number_of_expanded_nodes = 0;

    //std::cout << "Dentro do a* 15" << std::endl;

    q.push(root);

    while(!q.empty())
    {
        // Expand next node
        Node_15 current_node = q.top();
        q.pop();
        
        // If better distance has been found, continue
        if(distance.count(state_to_string_15(current_node.get_state()))  && 
        distance[state_to_string_15(current_node.get_state())] <= current_node.get_g_value())
            continue;

        // Update distance
        distance[state_to_string_15(current_node.get_state())] = current_node.get_g_value();
        
        return_info.mean_h_value += (double) current_node.get_h_value();

        //std::cout << "1" << std::endl;

        // Check if it is goal
        if(current_node.is_goal())
        {
            return_info.cost = current_node.get_g_value();
            return_info.mean_h_value /= (double) return_info.number_of_expanded_nodes;
            return return_info;
        }
        
        return_info.number_of_expanded_nodes++;
        //std::cout << current_node.get_h_value() << std::endl;
        //std::cout << return_info.mean_h_value << std::endl;
        //std::cout << "2" << std::endl;
        // Compute neighbors
        current_node.calculate_succs_states(current_node_neighbors);

        //std::cout << "3" << std::endl;

        // Add neighbors to the queue
        for(int i = 0; i < current_node.get_number_of_succs(); i++)
        {
            // Add non parent state to the queue
            if(!Node_15::is_states_equal(Node_15::get_long_long_from_array(current_node_neighbors[i]), current_node.get_parent_state()))
                q.push(Node_15(Node_15::get_long_long_from_array(current_node_neighbors[i]), current_node.get_g_value() + 1, current_node.get_state()));
        }                   
    }

    return_info.cost = -1;
    return return_info;
}

std::string state_to_string_15(long long state_15)
{
    std::string result = "";
    unsigned short state[16];

    Node_15::get_array_from_long_long(state_15, state);

    for(int i = 0; i < 16; i++)
    {
        result += state[i] + 48;

    }

    return result;
}