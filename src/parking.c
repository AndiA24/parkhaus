#include "../include/parking.h"
#include "../include/vehicle.h"
#include "../include/stats.h"

FUNCTION check_exit(ptr_parking, ptr_simstats)

    sim_step <- ptr_simstats->step_num

    FOR i <- 0 TO (ptr_parking->decks - 1) DO

        FOR j <- 0 TO (ptr_parking->ptr_decks[i].capacity - 1) DO

            IF ptr_parking->ptr_decks[i].ptr_spots[j].occupied == 1 THEN

                ptr_spot    <- Adresse von ptr_parking->ptr_decks[i].ptr_spots[j]
                ptr_vehicle <- ptr_spot->ptr_vehicle

                IF (sim_step - ptr_vehicle->entry_time) >= ptr_vehicle->parking_duration THEN

                    // Statistiken aktualisieren
                    ptr_simstats->temp_exits         <- ptr_simstats->temp_exits + 1
                    ptr_simstats->total_exits        <- ptr_simstats->total_exits + 1
                    ptr_simstats->total_queue_time   <- ptr_simstats->total_queue_time + ptr_vehicle->queue_time
                    ptr_simstats->total_parking_time <- ptr_simstats->total_parking_time + ptr_vehicle->parking_duration

                    // Fahrzeug freigeben und Stellplatz leeren
                    CALL free_vehicle(ptr_vehicle)
                    ptr_spot->ptr_vehicle <- NULL
                    ptr_spot->occupied    <- 0
                    ptr_parking->occupied_count <- ptr_parking->occupied_count - 1

                END IF

            END IF

        END FOR

    END FOR

END FUNCTION


/* 
FUNCTION entry_parking(ptr_parking : Parking*, ptr_vehicle : Vehicle*, ptr_simstats : SimStats*)
    IF !ptr_parking OR !ptr_parking->ptr_decks OR !ptr_vehicle THEN     // check for invalid input pointers
        RETURN                                                   
    ENDIF

    IF ptr_parking->occupied_count == ptr_parking->total_capacity THEN      // check if parking is full
        RETURN                                                   
    ENDIF

    FOR deck = 0 TO ptr_parking->deck_count - 1                // iterate over each deck
        FOR spot = 0 TO ptr_parking->ptr_decks[deck].capacity - 1       // iterate over each spot in current deck
            IF !ptr_parking->ptr_decks[deck].ptr_spots[spot].occupied THEN      // check if spot is occupied
                ptr_parking->ptr_decks[deck].ptr_spots[spot].ptr_vehicle = ptr_vehicle      // assign vehicle to free spot
                ptr_parking->ptr_decks[deck].ptr_spots[spot].occupied = 1       // set occupied flag
                ptr_parking->occupied_count = ptr_parking->occupied_count + 1       // increment occupied count

                // --- Update stats ---
                ptr_simstats->temp_entrys = ptr_simstats->temp_entrys + 1   // increment step entries
                ptr_simstats->total_entrys = ptr_simstats->total_entrys + 1 // increment total entries
                ptr_simstats->temp_rel_occupancy_precent = 
                    (ptr_parking->occupied_count / ptr_parking->total_capacity) * 100.0 // compute step occupancy %
                
                IF ptr_simstats->temp_rel_occupancy_precent > ptr_simstats->peak_rel_occupancy THEN
                    ptr_simstats->peak_rel_occupancy = ptr_simstats->temp_rel_occupancy_precent
                    ptr_simstats->step_highest_occupancy = ptr_simstats->step_num // update peak occupancy if new high
                ENDIF

                RETURN                                           // vehicle parked, exit
            ENDIF
        ENDFOR
    ENDFOR
ENDFUNCTION
*/
