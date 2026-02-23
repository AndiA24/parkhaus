
typedef struct {
    unsigned int  num_decks;
    unsigned int  spots_per_deck;
    unsigned int  max_parking_duration_steps;
    unsigned int  min_parking_duration_steps;
    unsigned int  sim_duration_steps;
    unsigned char arrival_probability_percent;
    unsigned int  seed;
} SimConfig;