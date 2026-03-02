#include "config.h"
#include "stats.h"

/**
 * @brief Function to run the given number of simulation steps
 *
 * Calls all functions necessary for an simulation step, as often given in the config
 * 
 * @param[in]       config  Pointer to the SimConfig structure containing the number of stats
 *                          and configurations for the simulation (number of spots, decks...)
 * @param[in, out]  stats   Pointer to the stats struct to save the results of each step and 
 *                          the final stats.
 * @return                  Returns 1 for sucessful simulation or -1 for failure.
 */
int run_simulation(SimConfig *ptr_config, SimStats *ptr_stats);

/**
 * @brief Decides random whether a car arrives or not
 *
 * Calls all functions necessary for an simulation step, as often given in the config
 * 
 * @param[in]       config  Pointer to the SimConfig structure containing the number of stats
 *                          and configurations for the simulation (number of spots, decks...)
 * @return                  Returns 1 for arrival 0 for no arrival
 */
int rand_arrival(SimConfig *ptr_config);