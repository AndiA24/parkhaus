#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief Holds the configuration parameters for the parking simulation.
 *
 * This structure is populated from a configuration file or changed by user input and passed
 * throughout the simulation to control its behaviour. Later the updated configs are saved in the config file.
 */
typedef struct {
    unsigned int num_decks;                     /**< Number of decks (floors) in the parking garage. */
    unsigned int spots_per_deck;                /**< Number of parking spots on each deck. */
    unsigned int initial_occupancy;             /**< Number of vehicles in the parking at simulation start. */
    unsigned int max_parking_duration_steps;    /**< Maximum number of simulation steps a vehicle may stay parked. */
    unsigned int min_parking_duration_steps;    /**< Minimum number of simulation steps a vehicle must stay parked. */
    unsigned int sim_duration_steps;            /**< Total number of steps the simulation runs. */
    unsigned int arrival_probability_percent;  /**< Probability in percent (0–100) that a vehicle arrives in a given step. */
    char output_file_name[70];                  /**< Name of the Stats-output file */
    char config_file_name[70];                  /**< Name of the Config-output file */
    unsigned int seed;                          /**< Seed value for the random number generator. */
} SimConfig;                    

/**
 * @brief Creates a configuration file with default values.
 *
 * Initializes the SimConfig structure with empty values.
 *
 * @return Pointer to a newly allocated SimConfig with default values,
 *         or NULL on failure.
 */
SimConfig *create_config();

/**
 * @brief Reads simulation parameters from the configuration file.
 *
 * Opens the configuration file and parses its contents into the
 * given SimConfig structure. If the file does not exist, the struct
 * is filled with default values.
 *
 * @param[in,out] ptr_config Pointer to the SimConfig structure to be populated
 */
int get_config(SimConfig *ptr_config);

/**
 * @brief Saves the current simulation configuration to a file.
 *
 * Writes all fields of the given SimConfig structure to a configuration
 * file under a defined name, overwriting any existing configuration.
 *
 * @param[in] config Pointer to the SimConfig structure to be saved
 */
int save_config(SimConfig *ptr_config);

/**
 * @brief Frees all dynamically allocated memory associated with the config structure.
 *
 * Frees the SimConfig structure that was allocated by create_config
 *
 * @param[in] ptr_config Pointer to the SimConfig structure to be freed.
 */
int free_config(SimConfig *ptr_config);

#endif