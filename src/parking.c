#include "../include/parking.h"
/*
FUNCTION check_exit(ptr_parking, ptr_simstats)

    sim_step <- ptr_simstats->step_num // Get the current sim step / time

    // iterate through all parkingspots in the parking
    FOR i <- 0 TO (ptr_parking->decks - 1) DO // iterate through all decks

        FOR j <- 0 TO (ptr_parking->ptr_decks[i].capacity - 1) DO // iterate through all spots in the deck

            ptr_spot    <- Adresse von ptr_parking->ptr_decks[i].ptr_spots[j] // save the ptr of the current spot in a temp ptr
            ptr_vehicle <- ptr_spot->ptr_vehicle // save the ptr of vehicle in the current spot in a temp ptr

            IF ptr_spot->occupied == 1 THEN // check if the spot is occupied

                IF (sim_step - ptr_vehicle->entry_time) >= ptr_vehicle->parking_duration THEN // check if the parking duration is over

                    // save the values of the leaving car in the stats struct
                    ptr_simstats->temp_exits         <- ptr_simstats->temp_exits + 1
                    ptr_simstats->total_exits        <- ptr_simstats->total_exits + 1
                    ptr_simstats->total_queue_time   <- ptr_simstats->total_queue_time + ptr_vehicle->queue_time
                    ptr_simstats->total_parking_time <- ptr_simstats->total_parking_time + ptr_vehicle->parking_duration

                    CALL free_vehicle(ptr_vehicle) // free the memory of the vehicle
                    ptr_spot->ptr_vehicle <- NULL
                    // set the spot free
                    ptr_spot->occupied    <- 0
                    ptr_parking->occupied_count <- ptr_parking->occupied_count - 1
                    ptr_parking->ptr_decks[i].occupied <- ptr_parking->ptr_decks[i].occupied - 1 

                END IF

            END IF

            // set temp ptr to NULL to avoid accidents
            ptr_spot = NULL
            ptr_vehicle = NULL

        END FOR

    END FOR

END FUNCTION
*/