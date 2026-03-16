/**
 * @file stats.h
 * @brief Simulation statistics structure stats processing.
 *
 * Declares the SimStats struct and functions for initialising, updating,
 * processinf, printing, and freeing simulation statistics.
 */

#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include "queue.h"
#include "config.h"

typedef struct Queue Queue;
typedef struct Parking Parking;

/**
 * @brief Holds the statistics collected during the simulation / one simulation step.
 *
 * Updated at each simulation step and used for writing the statistics of the simulation 
 * step into the output File after each step / to create the final report at the end.
 */
typedef struct SimStats{
    unsigned int step_num;                      /**< Current simulation step number. */
    unsigned int id_count;                      /**< Counter for the current Car ID */

    /* --- Per-step stats (overwritten each step) --- */
    unsigned int temp_exits;                    /**< Cars that exited this step. */
    unsigned int temp_entries;                   /**< New arrivals this step. */
    float        temp_rel_occupancy_percent;    /**< Relative occupancy this step (0.0–100.0). */
    unsigned int temp_queue_length;             /**< Cars in queue at end of this step. */
    unsigned int temp_free_spots;               /**< Free spots after this step. */
    unsigned int temp_time_left;                /**< Average time left for cars in the car park */

    /* --- Cumulative stats (accumulated until end) --- */
    unsigned int total_exits;                   /**< Total cars exited over all steps. */
    unsigned int total_entries;                  /**< Total cars arrived over all steps. */
    unsigned int total_queued;                  /**< Total cars that had to wait in queue. */
    unsigned int total_queue_time;              /**< Sum of all queue waiting times (in steps). */
    unsigned int total_parking_time;            /**< Sum of all parking durations (in steps). */
    unsigned int time_full_occupancy;           /**< Steps where parking was at full capacity. */
    float        avg_rel_occupancy;             /**< Average relative occupancy over all steps. */

    /* --- Tracked extremes for final report --- */
    unsigned int peak_queue_length;             /**< Peak queue length observed. */
    unsigned int step_longest_queue;            /**< Step at which peak queue length occurred. */
    float        peak_rel_occupancy;            /**< Peak relative occupancy observed (0.0–100.0). */
    unsigned int step_highest_occupancy;        /**< Step at which peak occupancy occurred. */
} SimStats;

/**
 * @brief Allocates and initializes the simulation statistics structure.
 *
 * Allocates memory for a SimStats structure and sets all fields to zero
 * before the simulation starts. 
 *
 * @return Pointer to the newly allocated and initialized SimStats structure,
 *         or NULL if memory allocation fails.
 */
SimStats *init_simstats(SimConfig *ptr_config);

/**
 * @brief Creates the CSV output file using the filename specified in the config.
 *
 * Opens (or creates) a CSV file whose name is taken from SimConfig struct. If a file
 * with that name already exists, the user is prompted to either supply an
 * alternative filename or confirm overwriting the existing file. Once the file
 * is successfully created, the simulation configuration is written
 * at the top of the CSV so that every output file is self-documenting.
 *
 * @param[in,out] ptr_config Pointer to the SimConfig structure containing the output
 *                   filename and all configuration values written to the header.
 * @return pointer to output file.
 */
FILE *create_output_file(SimConfig *ptr_config);

/**
 * @brief Updates the simulation statistics for the current time step.
 *
 * Collects and calculates all relevant metrics for the current time
 * step and writes them into the SimStats structure.
 *
 * @param[in,out] ptr_stats   Pointer to the SimStats structure to be updated
 * @param[in]     ptr_parking Pointer to the current parking lot state
 * @param[in]     ptr_queue   Pointer to the current waiting queue state
 * @return 0 on success, -1 if any argument is NULL.
 */
int update_simstats(SimStats *ptr_stats, Parking *ptr_parking, Queue *ptr_queue);

/**
 * @brief Checks temporary values against current peaks and updates them if exceeded.
 *
 * Compares temp_queue_length and temp_rel_occupancy_percent in the SimStats
 * structure against the stored peak values. If a new maximum is detected, the
 * corresponding peak field is overwritten and the current step_num is saved
 * in the matching step-tracking field step_longest_queue or
 * step_highest_occupancy.
 *
 * @param[in,out] ptr_stats Pointer to the SimStats structure whose peak fields
 *                             and step markers may be updated.
 * @return 0 on success, -1 if ptr_stats is NULL.
 */
int update_peak(SimStats *ptr_stats);

/**
 * @brief Logs the statistics of the current time step to console and file.
 *
 * Appends all metrics stored in the SimStats structure for the current
 * time step to the simulation log file.
 *
 * @param[in] ptr_stats Pointer to the SimStats structure of the current step
 * @param[in] ptr_output_file Pointer to the output file
 * @return 1 on success, -1 if any argument is NULL.
 */
int save_temp_dataset(SimStats *ptr_stats, FILE *ptr_output_file);

/**
 * @brief Resets all per-step (temporary) fields in the SimStats structure to zero.
 *
 * Clears all temp stats so they are ready to be filled in the next
 * simulation step.
 *
 * @param[in,out] ptr_stats Pointer to the SimStats structure whose temporary
 *                             fields are to be reset.
 * @return 0 on success, -1 if ptr_stats is NULL.
 */
int reset_temp_stats(SimStats *ptr_stats);

/**
 * @brief Logs the overall simulation statistics to console and file.
 *
 * Outputs a final summary of all accumulated metrics after the simulation
 * has completed. Writes the summary to stdout and to the simulation log file.
 * Closes the output File after writing the final data.
 *
 * @param[in] ptr_stats Pointer to the SimStats structure containing all data.
 * @param[in] ptr_output_file  Pointer to the output file.
 * @return 1 on success, -1 if any argument is NULL.
 */
int save_final_dataset(SimStats *ptr_stats, FILE *ptr_output_file);

/**
 * @brief Closes the open Output-File 
 *
 * Closes the open Output-File after succesful finish of the simulation and writing
 * final dataset or after an abort of simulation.
 *
 * @param[in] ptr_output_file Pointer to the opened Report / Output-File
 * 
 * @return Returns 1 for success or -1 for fail
 */
int close_output_file(FILE *ptr_output_file, SimConfig *ptr_config);

/**
 * @brief Resets all fields in the SimStats structure to zero.
 *
 * Clears every field.
 *
 * @param[in,out] ptr_stats Pointer to the SimStats structure to be fully reset.
 * @return 0 on success, -1 if ptr_stats is NULL.
 */
int reset_all_stats(SimStats *ptr_stats);

/**
 * @brief Frees all dynamically allocated memory associated with a SimStats structure.
 *
 * Frees the SimStats structure that was allocated by init_simstats
 *
 * @param[in] ptr_stats Pointer to the SimStats structure to be freed.
 * @return 0 on success, -1 if ptr_stats is NULL.
 */
int free_stats(SimStats *ptr_stats);

#endif // STATS_H