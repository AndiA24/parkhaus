/**
 * @file vehicle.h
 * @brief Vehicle structure and interface.
 *
 * Declares the Vehicle struct and functions for creating and
 * freeing vehicle instances used during the parking simulation.
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include "config.h"
typedef struct SimStats SimStats;

/**
 * @brief Represents a vehicle in the parking simulation.
 */
typedef struct {
    unsigned int id;               /**< Unique identifier of the vehicle. */
    unsigned int entry_time;       /**< Simulation step at which the vehicle entered the parking garage. */
    unsigned int parking_duration; /**< Number of the total of simulation steps the vehicle stays parked. */
    unsigned int queue_time;       /**< Simulation step at which the vehicle entered the queue. */
} Vehicle;

/**
 * @brief Initializes a Vehicle with default values.
 *
 * @param[in,out] ptr_stats     Pointer to Stats to get current ID-count.
 * @param[in] ptr_config        Pointer to Config Struct to get max-parking-duration.
 * 
 * @return Pointer to new created vehicle or null if pointer allocation fails.
 * 
 */
Vehicle *create_vehicle(SimStats *ptr_stats, SimConfig *ptr_config);

/**
 * @brief Frees the memory of a Vehicle struct after exit.
 *
 * @param[in] ptr_vehicle Pointer to the Vehicle to free.
 * 
 * @return Int 0 for success; -1 for a failure.
 * 
 */
int free_vehicle(Vehicle *ptr_vehicle);

#endif