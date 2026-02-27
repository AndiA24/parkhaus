/*
FUNCTION create_vehicle(id : int, entry_time : int, duration : int) RETURNS Vehicle*

    ptr_vehicle : Vehicle*
    ptr_vehicle = malloc(sizeof(Vehicle))

    IF ptr_vehicle == NULL
        RETURN NULL
    ENDIF

    ptr_vehicle->id = id
    ptr_vehicle->entry_time = entry_time
    ptr_vehicle->parking_duration = duration
    ptr_vehicle->queue_time = 0

    RETURN ptr_vehicle
END FUNCTION
*/