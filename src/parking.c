#include "../include/parking.h"
#include "../include/vehicle.h"
#include "../include/stats.h"
#include "../include/config.h"


Parking *init_parking(SimConfig *ptr_config, SimStats *ptr_stats) {}

void check_exit(Parking *ptr_parking, SimStats *ptr_simstats)
{
    int sim_step = ptr_simstats->step_num;

    for (int i = 0; i < ptr_parking->decks; i++)
    {
        for (int j = 0; j < ptr_parking->ptr_decks[i].capacity; j++)
        {
            ParkingSpot *ptr_spot = &ptr_parking->ptr_decks[i].ptr_spots[j];
            Vehicle *ptr_vehicle = ptr_spot->ptr_vehicle;

            if (ptr_spot->occupied == 1 && ptr_vehicle != NULL)
            {
                if ((sim_step - ptr_vehicle->entry_time) >= ptr_vehicle->parking_duration)
                {
                    ptr_simstats->temp_exits++;
                    ptr_simstats->total_exits++;
                    ptr_simstats->total_parking_time += ptr_vehicle->parking_duration;

                    //free_vehicle(ptr_vehicle);
                    ptr_spot->occupied = 0;
                    ptr_spot->ptr_vehicle = NULL;
                    ptr_parking->occupied_count--;
                    ptr_parking->ptr_decks[i].occupied_count--;
                }
            }
        }
    }
}

/* 
PSEUDOCODE

FUNCTION init_parking(SimConfig *ptr_config, SimStats *ptr_stats)
    ptr_parking = allocate memory for (size)Parking and set all fields to 0
    IF ptr_parking == NULL THEN
        OUTPUT Error cannot allocate memory
        return NULL
    END IF
    
    ptr_parking->total_capacity = ptr_config->num_decks * ptr_config->spots_per_deck
    ptr_parking->decks = ptr_config->num_decks
    ptr_parking->occupied_count = 0
    ptr_parking->ptr_decks = (Adress)allocate memory for (ptr_parking->decks) * (size)ParkingDeck (calloc)
    IF ptr_parking->ptr_decks == NULL THEN
        OUTPUT Error cannot allocate memory
        free memory allocated for ptr_parking
        return NULL
    END IF

    i = 0
    FOR i < ptr_parking->decks DO
        ((ptr_parking->ptr_decks) + i)->deck_id = i
        ((ptr_parking->ptr_decks) + i)->capacity = ptr_config->spots_per_deck
        ((ptr_parking->ptr_decks) + i)->occupied_count = 0
        ((ptr_parking->ptr_decks) + i)->ptr_spots = (Adress)allocate memory for (ptr_config->spots_per_deck) * (size)ParkingSpot (calloc) and fill all fields with 0
            IF ((ptr_parking->ptr_decks) + i)->ptr_spots == NULL THEN
                OUTPUT Error cannot allocate memory
                // the memeory for all spots that were already created must be freed
                j = 0
                FOR j < i DO
                    free memory allocated for ((ptr_parking->ptr_decks) + j)->ptr_spots
                    j = j + 1
                END FOR
                free memory allocated for ptr_decks
                free memory allocated for ptr_parking
                return NULL
            END IF
        k = 0
        FOR k < ptr_config->spots_per_deck Do
            // Global spot ID: deck index * spots per deck + local spot index 
            // this way every spot got an unique ID across als decks
            (((ptr_parking->ptr_decks) + i)->ptr_spots + k)->id = (i * ptr_config->spots_per_deck) + k
            (((ptr_parking->ptr_decks) + i)->ptr_spots + k)->occupied = 0
            (((ptr_parking->ptr_decks) + i)->ptr_spots + k)->ptr_vehicle = NULL
            k = k + 1
        END FOR
        i = i + 1
    END FOR

    IF ptr_config->initial_occupancy THEN // prefill parking with given amount of vehicles
        // check if initial_occupancy exceeds cpacity to avoid segmentation fault
        // if this is the case the error is consciously handled by not filling the parking at all
        // another option could to fill the parking with total_capacity amount of cars
        IF ptr_config->initial_occupancy > ptr_parking->total_capacity THEN
            OUTPUT Error initial_occupancy exceeds total_capacity: Parking is now empty without initial_occupancy
            return ptr_parking
        END IF
        i = 0
        FOR i < ptr_config->initial_occupancy DO
            // fill spots one by one across all decks: floor(i / spots_per_deck) gives the deck index
            // i % spots_per_deck gives the position within that deck
            (((ptr_parking->ptr_decks) + floor(i / ptr_config->spots_per_deck))->ptr_spots + (i % ptr_config->spots_per_deck))->ptr_vehicle = create_vehicle(ptr_stats, ptr_config)
            IF (((ptr_parking->ptr_decks) + floor(i / ptr_config->spots_per_deck))->ptr_spots + (i % ptr_config->spots_per_deck))->ptr_vehicle == NULL THEN
                OUTPUT Failed to create vehicle
                // if something went wrong during filling, free all already created vehicles and other structures
                i = 0
                FOR i < ptr_parking->decks DO
                    k = 0
                    FOR k < ptr_config->spots_per_deck DO
                        // only free spots that actually got a vehicle assigned
                        IF (((ptr_parking->ptr_decks) + i)->ptr_spots + k)->ptr_vehicle != NULL THEN
                            free_vehicle((((ptr_parking->ptr_decks) + i)->ptr_spots + k)->ptr_vehicle)
                        END IF
                        k = k + 1
                    END FOR
                    free memory allocated for (((ptr_parking->ptr_decks) + i)->ptr_spots)
                    i = i + 1
                END FOR
                free memory allocated for ptr_decks
                free memory allocated for ptr_parking
                return NULL
            END IF

            // set the spot to occupied and increment the occupied_count of the deck and the parking
            (((ptr_parking->ptr_decks) + floor(i / ptr_config->spots_per_deck))->ptr_spots + (i % ptr_config->spots_per_deck))->occupied = 1
            ((ptr_parking->ptr_decks) + floor(i / ptr_config->spots_per_deck))->occupied_count = ((ptr_parking->ptr_decks) + floor(i / ptr_config->spots_per_deck))->occupied_count + 1
            ptr_parking->occupied_count = ptr_parking->occupied_count + 1
            i = i + 1
        END FOR
    END IF

    return ptr_parking
END FUNCTION

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


FUNCTION entry_parking(ptr_parking : Parking*, ptr_vehicle : Vehicle*, ptr_simstats : SimStats*)
    IF !ptr_parking OR !ptr_parking->ptr_decks OR !ptr_vehicle OR !ptr_simstats THEN        // check for invalid input pointers
        RETURN                                                   
    ENDIF

    FOR deck = 0 TO ptr_parking->deck_count - 1                                             // iterate over each deck
        FOR spot = 0 TO ptr_parking->ptr_decks[deck].capacity - 1                           // iterate over each spot in current deck
            IF !ptr_parking->ptr_decks[deck].ptr_spots[spot].occupied THEN                  // check if spot is occupied
                ptr_parking->ptr_decks[deck].ptr_spots[spot].ptr_vehicle = ptr_vehicle      // assign vehicle to free spot
                ptr_parking->ptr_decks[deck].ptr_spots[spot].occupied = 1                   // set occupied flag
                ptr_parking->occupied_count = ptr_parking->occupied_count + 1               // increment occupied count
                ptr_parking->ptr_decks[deck].occupied_count = ptr_parking->ptr_decks[deck].occupied_count + 1
                ptr_vehicle->entry_time = ptr_stats->step_num

                // --- Update stats ---
                ptr_simstats->temp_entries = ptr_simstats->temp_entries + 1                 // increment step entries
                ptr_simstats->total_entries = ptr_simstats->total_entries + 1               // increment total entries
                ptr_simstats->temp_time_left += ptr_vehicle->parking_duration               // update avg time left    

                RETURN                                                                      // vehicle parked, exit
            ENDIF
        ENDFOR
    ENDFOR
ENDFUNCTION

FUNCTION get_free_spots(ptr_parking : Parking*, ptr_simstats : SimStats*) 
    ptr_simstats->temp_free_spots = ptr_parking->total_capacity - ptr_parking->occupied_count   // save free spots in stats param
END FUNCTION

FUNCTION free_parking(Parking ptr_parking)
    CALL free(ptr_parking)  //free all memory inside this struct for reference look at init_parking for walking through all things inside
END FUNCTION
*/
