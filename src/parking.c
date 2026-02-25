#include "../include/parking.h"

FUNCTION check_exit(ptr_parking, ptr_simstats):
    sim_step = ptr_simstats->step_num

    FOR i <- 0 TO (ptr_parking->decks - 1):

        FOR j <- 0 TO (ptr_parking->ptr_decks[i].capacity - 1):

            IF ptr_parking->ptr_decks[i].ptr_spots[j].occupied == 1:
                ParkingSpot *ptr_spot = (ptr_parking->ptr_decks[i].ptr_spots + j)
                Vehicle *ptr_vehicle = ptr_spot->ptr_vehicle

                IF sim_step - ptr_vehicle->entry_time >= ptr_vehicle->parking_duration: 
                    
                    ptr_simstats->temp_exits         += 1
                    ptr_simstats->total_exits        += 1
                    ptr_simstats->total_queue_time   += ptr_vehicle->queue_time
                    ptr_simstats->total_parking_time += ptr_vehicle->parking_duration

                    free_vehicle(ptr_vehicle)
                    Setze ptr_spot->ptr_vehicle = NULL
                    Setze ptr_spot->occupied = 0

                    ptr_parking->occupied_count -= 1

                END IF

            END IF

        END FOR

    END FOR