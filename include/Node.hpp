class Node {
    public:

        // Constructors
        Node();
        Node(unsigned short state[9], double g_value, unsigned short parent_state[9]);

        // Getters
        unsigned short* get_state();
        unsigned short* get_parent_state();
        unsigned short get_number_of_succs();
        double get_f_value();
        double get_g_value();
        double get_h_value();
        unsigned short get_blank_index();

        // Setters
        void set_state(unsigned short state[9]);

        // Static Node ID
        static long global_node_id;

        void calculate_succs_states(unsigned short succs_states[4][9]);
        bool is_goal();
        static bool is_states_equal(unsigned short state1[9], unsigned short state2[9]);
        long node_id;

    private:
        unsigned short state[9];
        unsigned short parent_state[9];
        unsigned short number_of_succs;
        unsigned short blank_index;
        double f_value;
        double g_value;
        double h_value;
        
        double calculate_heuristic();
        void get_x_y_coords(int number, int coords[2]);
        unsigned short calculate_number_of_succs();
        unsigned short calculate_blank_index();
        void switch_blank_position(unsigned short new_state[], unsigned short new_blank_index);
};