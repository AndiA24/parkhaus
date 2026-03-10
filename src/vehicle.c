#include <stdio.h>
#include <stdlib.h>

#include "../include/vehicle.h"
#include "../include/stats.h"

Vehicle *create_vehicle(SimStats *ptr_stats, SimConfig *ptr_config){
    Vehicle *ptr_vehicle = malloc(sizeof(*ptr_vehicle));
    if(ptr_vehicle == NULL){
        printf("Error: Failed to allocate memory to generate vehicle. Invalid argument.\n");
        return NULL;
    }
    
    // set the ID of the vehicle to an unique ongoing number
    ptr_vehicle->id = ptr_stats->id_count;
    ptr_stats->id_count ++;

    // set vehicles parking-duration to a random time between min and max
    ptr_vehicle->parking_duration = rand() % (ptr_config->max_parking_duration_steps -ptr_config->min_parking_duration_steps + 1) 
        + ptr_config->min_parking_duration_steps;

    ptr_vehicle->queue_time = 0;
    ptr_vehicle->entry_time = 0;

    return ptr_vehicle;
}

int free_vehicle(Vehicle *ptr_vehicle){
    if(ptr_vehicle == NULL){
        printf("Error: Failed to free memory allocated for Vehicle. Invalid argument.\n");
        return -1;
    }
    free(ptr_vehicle);
    return 1;
}

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