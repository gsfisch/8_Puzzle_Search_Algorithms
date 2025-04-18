class Node_15 {
    public:

        // Constructors
        Node_15();
        Node_15(long long state, double g_value, long long parent_state);

        // Getters
        long long get_state();
        long long get_parent_state();
        unsigned short get_number_of_succs();
        double get_g_value();
        double get_h_value();
        unsigned short get_blank_index();

        // Setters
        void set_state(long long state);

        // Static Node ID
        static long global_node_id;

        void calculate_succs_states(unsigned short succs_states[4][16]);
        bool is_goal();
        static bool is_states_equal(long long state1, long long state2);
        long node_id;
        long long array_to_long_long();

        static unsigned short get_index_from_long_long(long long state, unsigned short tile_number);
        static long long get_long_long_from_array(unsigned short state[16]);
        static void get_array_from_long_long(unsigned long long state_15, unsigned short state[16]);

    private:
        long long state;
        long long parent_state;
        unsigned short number_of_succs;
        unsigned short blank_index;
        double g_value;
        double h_value;
        
        double calculate_heuristic();
        void get_x_y_coords(int number, int coords[2]);
        unsigned short calculate_number_of_succs();
        unsigned short calculate_blank_index();
        void switch_blank_position(unsigned short new_state[16], unsigned short new_blank_index);
};