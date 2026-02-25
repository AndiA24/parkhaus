#ifndef STATS_H
#define STATS_H

#include "queue.h"

typedef struct Parking Parking;

/**
 * @brief Holds the statistics collected during the simulation / one simulation step.
 *
 * Updated at each simulation step and used for writing the statistics of the simulation 
 * step into the output File after each step / to create the final report at the end.
 */
typedef struct {
    unsigned int step_num;               /**< Current simulation step number. */

    /* --- Per-step stats (overwritten each step) --- */
    unsigned int temp_exits;             /**< Cars that exited this step. */
    unsigned int temp_entrys;            /**< New arrivals this step. */
    float        temp_rel_occupancy;     /**< Relative occupancy this step (0.0–1.0). */
    unsigned int temp_queue_length;      /**< Cars in queue at end of this step. */

    /* --- Cumulative stats (accumulated until end) --- */
    unsigned int total_exits;            /**< Total cars exited over all steps. */
    unsigned int total_entrys;           /**< Total cars arrived over all steps. */
    unsigned int total_queued;           /**< Total cars that had to wait in queue. */
    unsigned int total_queue_time;       /**< Sum of all queue waiting times (in steps). */
    unsigned int total_parking_time;     /**< Sum of all parking durations (in steps). */
    unsigned int time_full_occupancy;    /**< Steps where parking was at full capacity. */
    float        total_revenue;          /**< Total revenue earned over all steps. */

    /* --- Tracked extremes for final report --- */
    unsigned int peak_queue_length;      /**< Peak queue length observed. */
    unsigned int step_longest_queue;     /**< Step at which peak queue length occurred. */
    float        peak_rel_occupancy;     /**< Peak relative occupancy observed (0.0–1.0). */
    unsigned int step_highest_occupancy; /**< Step at which peak occupancy occurred. */
} SimStats;

/**
 * @brief Initializes the simulation statistics structure with default values.
 *
 * Sets all fields of the SimStats structure to zero before the
 * simulation starts. Must be called before any other stats function.
 *
 * @param[out] simstats Pointer to the SimStats structure to be initialized
 */
void init_simstats(SimStats *ptr_simstats);

/**
 * @brief Updates the simulation statistics for the current time step.
 *
 * Collects and calculates all relevant metrics for the current time
 * step and writes them into the SimStats structure.
 *
 * @param[in,out] simstats Pointer to the SimStats structure to be updated
 * @param[in]     parking  Pointer to the current parking lot state
 * @param[in]     queue    Pointer to the current waiting queue state
 */
void update_simstats(SimStats *ptr_simstats, Parking *ptr_parking, Queue *ptr_queue);

/**
 * @brief Logs the statistics of the current time step to console and file.
 *
 * Outputs all metrics stored in the SimStats structure for the current
 * time step in a readable format to stdout and appends them to the
 * simulation log file.
 *
 * @param[in] simstats Pointer to the SimStats structure of the current step
 */
void log_step_stats(SimStats *ptr_simstats);

/**
 * @brief Logs the overall simulation statistics to console and file.
 *
 * Outputs a final summary of all accumulated metrics after the simulation
 * has completed. Writes the summary to stdout and to the simulation log file.
 *
 * @param[in] simstats Pointer to the SimStats structure containing all data
 */
void log_final_stats(SimStats *ptr_simstats);

#endif // STATS_H