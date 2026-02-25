#include "../include/parking.h"

FUNCTION check_exit(ptr_parking, ptr_simstats):
    sim_step = ptr_simstats->step_num

    FOR i <- 0 TO (ptr_parking->decks - 1):

        FOR j <- 0 TO (ptr_parking->ptr_decks[i].capacity - 1):

            IF ptr_parking->ptr_decks[i].ptr_spots[j].occupied == 1:
                Vehicle *ptr_temp_vehicle = ptr_parking->ptr_decks[i].ptr_spots[j].ptr_vehicle

                IF sim_step - vehicle->entry_time >= vehicle->parking_duration: // check if parking duration is over
                    

                    // Stats aus dem Fahrzeug übertragen (BEVOR free())
                    ptr_simstats->exits_this_step    += 1
                    ptr_simstats->total_exits        += 1
                    ptr_simstats->total_queue_time   += vehicle->queue_time
                    ptr_simstats->total_parking_time += vehicle->parking_duration

                    // Spot freigeben
                    free_vehicle(ptr_temp_vehicle)
                    Setze spot.ptr_vehicle = NULL
                    Setze spot.occupied = 0

                    ptr_parking->occupied_count -= 1

                END IF

            END IF

        END FOR

    END FOR