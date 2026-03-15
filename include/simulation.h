/**
 * @file simulation.h
 * @brief Simulation loop and step function interface.
 *
 * Declares functions for running the parking simulation, including
 * random arrival checks, and the main simulation loop.
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include "stats.h"

/**
 * @brief Decides random whether a car arrives or not
 *
 * 
 * @param[in]       config  Pointer to the SimConfig structure containing the number of stats
 *                          and configurations for the simulation
 * @return                  Returns 1 for arrival 0 for no arrival
 */
int rand_arrival(SimConfig *ptr_config);

/**
 * @brief Function to run the given number of simulation steps
 *
 * Calls all functions necessary for an simulation step, as often given in the config
 * 
 * @param[in]       ptr_config  Pointer to the SimConfig structure containing the number of stats
 *                              and configurations for the simulation
 * @param[in,out]   ptr_stats   Pointer to the stats struct to save the results of each step and 
 *                              the final stats.
 * @return                      Returns 1 for sucessful simulation or -1 for failure.
 */
int run_simulation(SimConfig *ptr_config, SimStats *ptr_stats);

#endif