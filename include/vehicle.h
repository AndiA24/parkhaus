/**
 * @brief Represents a vehicle in the parking simulation.
 */
typedef struct {
    unsigned int id;               /**< Unique identifier of the vehicle. */
    unsigned int entry_time;       /**< Simulation step at which the vehicle entered the parking garage. */
    unsigned int parking_duration; /**< Number of the total of simulation steps the vehicle stays parked. */
    unsigned int queue_time;       /**< Number of simulation steps the vehicle spent waiting in the queue. */
} Vehicle;

void init_vehicle(Vehicle *ptr_vehicle);