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
 * @brief Initializes a Vehicle struct with default values.
 *
 * @param ptr_vehicle Pointer to the Vehicle to initialize.
 */
void init_vehicle(Vehicle *ptr_vehicle) {}

/**
 * @brief Frees Memory of a Vehicle after the exit.
 *
 * @param ptr_vehicle Pointer to the Vehicle to free.
 */
void free_vehicle(Vehicle *ptr_vehicle) {}