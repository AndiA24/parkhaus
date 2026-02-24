
typedef struct {
    unsigned int  num_decks;
    unsigned int  spots_per_deck;
    unsigned int  max_parking_duration_steps;
    unsigned int  min_parking_duration_steps;
    unsigned int  sim_duration_steps;
    unsigned char arrival_probability_percent;
    unsigned int  seed;
} SimConfig;

/**
 * @brief Creates a configuration file with default values.
 *
 * Initializes the SimConfig structure with predefined default values
 * and writes them to a configuration file. This function is called
 * by get_config if no existing configuration file is found.
 */
void create_config(){}

/**
 * @brief Reads simulation parameters from the configuration file.
 *
 * Opens the configuration file and parses its contents into the
 * given SimConfig structure. If the file does not exist, create_config
 * is called to generate one with default values first.
 *
 * @param[out] config Pointer to the SimConfig structure to be populated
 */
void get_config(SimConfig *ptr_config){}

/**
 * @brief Saves the current simulation configuration to a file.
 *
 * Writes all fields of the given SimConfig structure to a configuration
 * file under a defined name, overwriting any existing configuration.
 *
 * @param[in] config Pointer to the SimConfig structure to be saved
 */
void save_config(SimConfig *ptr_config){}