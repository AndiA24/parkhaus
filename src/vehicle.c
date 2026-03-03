#include "../include/vehicle.h"

/*
FUNCTION create_vehicle(SimStats *ptr_stats, SimConfig *ptr_config) RETURNS Vehicle*

    ptr_vehicle : Vehicle*                          // declare pointer to Vehicle
    ptr_vehicle = malloc(sizeof(Vehicle))           // allocate memory for one Vehicle object

    IF ptr_vehicle == NULL                          // check if memory allocation failed
        RETURN NULL                                 
    ENDIF

    ptr_vehicle->id = ptr_stats->id_count                                                       // assign unique vehicle ID
    ptr_stats->id_count = ptr_stats->id_count + 1
    
    This next calculation determines a random parking duration value between the minimum and maximum
    parking duration set in the config struct.

    ptr_vehicle->parking_duration = CALL rand() % (ptr_config->max_parking_duration_steps - 
    ptr_config->min_parking_duration_steps + 1) + ptr_config->min_parking_duration_steps    // set total parking duration
    
    ptr_vehicle->queue_time = 0                                                                 // initialize queue time to zero

    RETURN ptr_vehicle                                                                          // return pointer to newly created vehicle
END FUNCTION
*/


/*
FUNCTION free_vehicle(ptr_vehicle : Vehicle*)

    IF ptr_vehicle == NULL                          // check if pointer is NULL
        RETURN
    ENDIF

    CALL free(ptr_vehicle)                          // release allocated memory
    
    // The caller shall set the pointer to NULL after calling this function

END FUNCTION
*/