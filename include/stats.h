#include "queue.h"
#include "parking.h"

typedef struct {
    unsigned int step_num;
    // stats ...
} SimStats;

/**
 * @brief Initializes the simulation statistics structure with default values.
 *
 * Sets all fields of the SimStats structure to zero before the
 * simulation starts. Must be called before any other stats function.
 *
 * @param[out] simstats Pointer to the SimStats structure to be initialized
 */
void init_simstats(SimStats *simstats){}

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
void update_simstats(SimStats *simstats, Parking *parking, Queue * queue,){}

/**
 * @brief Logs the statistics of the current time step to console and file.
 *
 * Outputs all metrics stored in the SimStats structure for the current
 * time step in a readable format to stdout and appends them to the
 * simulation log file.
 *
 * @param[in] simstats Pointer to the SimStats structure of the current step
 */
void log_step_stats(SimStats *simstats){}

/**
 * @brief Logs the overall simulation statistics to console and file.
 *
 * Outputs a final summary of all accumulated metrics after the simulation
 * has completed. Writes the summary to stdout and to the simulation log file.
 *
 * @param[in] simstats Pointer to the SimStats structure containing all data
 */
void log_final_stats(SimStats *simstats){}