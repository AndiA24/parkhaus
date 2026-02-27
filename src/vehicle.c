/*
FUNCTION create_vehicle(id : int, entry_time : int, duration : int) RETURNS Vehicle*

    ptr_vehicle : Vehicle*                          // declare pointer to Vehicle
    ptr_vehicle = malloc(sizeof(Vehicle))           // allocate memory for one Vehicle object

    IF ptr_vehicle == NULL                          // check if memory allocation failed
        RETURN NULL                                 
    ENDIF

    ptr_vehicle->id = id                            // assign unique vehicle ID
    ptr_vehicle->entry_time = entry_time            // set simulation entry time
    ptr_vehicle->parking_duration = duration        // set total parking duration
    ptr_vehicle->queue_time = 0                     // initialize queue time to zero

    RETURN ptr_vehicle                              // return pointer to newly created vehicle
END FUNCTION
*/


/*
FUNCTION free_vehicle(ptr_vehicle : Vehicle*)

    IF ptr_vehicle == NULL                          // check if pointer is NULL
        RETURN
    ENDIF

    free(ptr_vehicle)                               // release allocated memory
    
    // The caller shall set the pointer to NULL after calling this function

END FUNCTION
*/