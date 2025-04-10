class Node {
    public:

        // Constructors
        Node();
        Node(unsigned short state[9], float g_value, unsigned short parent_state[9]);

        // Getters
        unsigned short* get_state();
        unsigned short* get_parent_state();
        unsigned short get_number_of_succs();
        float get_f_value();
        float get_g_value();
        float get_h_value();
        unsigned short get_blank_index();

        // Setters
        void set_state(unsigned short state[9]);

        void calculate_succs_states(unsigned short succs_states[4][9]);
        bool is_goal();
        static bool is_states_equal(unsigned short state1[9], unsigned short state2[9]);
        //static string state_to_string();

    private:
        unsigned short state[9];
        unsigned short parent_state[9];
        unsigned short number_of_succs;
        unsigned short blank_index;
        float f_value;
        float g_value;
        float h_value;
        
        int calculate_heuristic();
        void get_x_y_coords(int number, int coords[2]);
        unsigned short calculate_number_of_succs();
        unsigned short calculate_blank_index();
        void switch_blank_position(unsigned short new_state[], unsigned short new_blank_index);
};