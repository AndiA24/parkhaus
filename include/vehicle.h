#ifndef VEHICLE_H
#define VEHICLE_H

/**
 * @brief Represents a vehicle in the parking simulation.
 */
typedef struct {
    unsigned int id;               /**< Unique identifier of the vehicle. */
    unsigned int entry_time;       /**< Simulation step at which the vehicle entered the parking garage. */
    unsigned int parking_duration; /**< Number of the total of simulation steps the vehicle stays parked. */
    unsigned int queue_time;       /**< Number of simulation steps the vehicle spent waiting in the queue. */
} Vehicle;

/**
 * @brief Initializes a Vehicle with default values.
 *
 * @param ptr_stats     Pointer to Stats to get current ID-count.
 * @param ptr_config    Pointer to Config Struct to get max-parking-duration.
 * 
 * @return Pointer to new created vehicle.
 * 
 */
Vehicle *create_vehicle(SimStats *ptr_stats, SimConfig *ptr_config);

/**
 * @brief Frees the memory of a Vehicle struct after exit.
 *
 * @param ptr_vehicle Pointer to the Vehicle to free.
 */
void free_vehicle(Vehicle *ptr_vehicle);

#endif