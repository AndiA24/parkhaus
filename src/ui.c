#include "../include/ui.h"
#include "../include/config.h"
#include "../include/stats.h"
#include "../include/utils.h"

/*

FUNCTION show_welcome(Struct *ptr_SimConfig)
    active <- true
    CALL render_welcome()

    WHILE active
        key <- CALL get_input()
        
        IF key = 'Q'
            CALL quit(ptr_SimConfig)
        ELSE IF key = 'S'
            CALL show_settings(ptr_SimConfig)
        ELSE IF key = 'Enter'
            active <- false //main will start simulation
        END IF
    END WHILE
END FUNCTION


FUNCTION show_settings(Struct *ptr_SimConfig)
    active <- true
    CALL render_settings(ptr_SimConfig)

    WHILE active
        key <- CALL get_input()
        
        IF key = '1'
            ptr_SimConfig->num_decks <- CALL prompt_input("Number of Decks", ptr_SimConfig->num_decks, 1, 99)
        ELSE IF key = '2'
            ptr_SimConfig->spots_per_deck <- CALL prompt_input("Spots per Deck", ptr_SimConfig->spots_per_deck, 1, 999)
        ELSE IF key = '3'
            ptr_SimConfig->initial_occupancy <- CALL prompt_input("Initial Occupancy", ptr_SimConfig->initial_occupancy, 0, 999)
        ELSE IF key = '4'
            ptr_SimConfig->max_parking_duration_steps <- CALL prompt_input("Max Parking Duration", ptr_SimConfig->max_parking_duration_steps, 1, 9999)
        ELSE IF key = '5'
            ptr_SimConfig->min_parking_duration_steps <- CALL prompt_input("Min Parking Duration", ptr_SimConfig->min_parking_duration_steps, 1, 9999)
        ELSE IF key = '6'
            ptr_SimConfig->sim_duration_steps <- CALL prompt_input("Simulation Duration", ptr_SimConfig->sim_duration_steps, 1, 9999)
        ELSE IF key = '7'
            ptr_SimConfig->arrival_probability_percent <- CALL prompt_input("Arrival Probability %", ptr_SimConfig->arrival_probability_percent, 0, 100)
        ELSE IF key = '8'
            ptr_SimConfig->seed <- CALL prompt_input("RNG Seed", ptr_SimConfig->seed, 0, 9999)
        ELSE IF key = '9'
            ptr_SimConfig->config_file_name <- CALL prompt_input("The file name to store the config inside of", ptr_SimConfig->config_file_name)
        ELSE IF key = 'ESC' || 'Enter' || 'Q'
            active <- false
        END IF
    END WHILE
END FUNCTION


FUNCTION prompt_input(name, current_value, min, max)

    valid <- false
    CALL render_prompt(name, current_value)

    WHILE NOT valid
        input <- CALL get_text_input()
        
        IF current_value is not config_file_name AND input is a valid number AND input >= min AND input <= max
            valid <- true
        ELSE IF current_value is config_file_name AND input is a valid string AND input length < array length
            valid <- true
        ELSE
            CALL print("Please enter a correct value between min and max")
        END IF
    END WHILE
    
    RETURN input
END FUNCTION

FUNCTION render_settings(Struct *ptr_SimConfig)
    CALL print("Number of Decks", SimConfig->num_decks)
    CALL print("Spots per Deck", SimConfig->spots_per_deck)
    CALL print("Initial Occupancy", SimConfig->initial_occupancy)
    CALL print("Max Parking Duration", SimConfig->max_parking_duration_steps)
    CALL print("Min Parking Duration", SimConfig->min_parking_duration_steps)
    CALL print("Simulation Duration", SimConfig->sim_duration_steps)
    CALL print("Arrival Probability %", SimConfig->arrival_probability_percent)
    CALL print("RNG Seed", SimConfig->seed)
END FUNCTION

FUNCTION show_running(Struct ptr_SimStats)
    CALL print("Exists this time step", ptr_SimStats->temp_exits)
    CALL print("Entrys this time step", ptr_SimStats->temp_entrys)
    CALL print("Relative Occupancy this time step", ptr_SimStats->temp_rel_occupancy_precent)
    CALL print("Current queue length", ptr_SimStats->temp_queue_length)
END FUNCTION

FUNCTION show_results(Struct ptr_SimStats)
    CALL print("Total cars that left the car park", ptr_SimStats->temp_exits)
    CALL print("Total cars that entered the car park", ptr_SimStats->total_entrys)
    CALL print("Total cars that had to wait in queue", ptr_SimStats->total_queued)
    CALL print("Sum of all queue steps", ptr_SimStats->total_queue_time)
    CALL print("Steps cars spent in the car park", ptr_SimStats->total_parking_time)
    CALL print("Steps the parking garage was full", ptr_SimStats->time_full_occupancy)
    CALL print("Peak queue length during the simulation", ptr_SimStats->peak_queue_length)
    CALL print("Step at which the queue was the longest", ptr_SimStats->step_longest_queue)
    CALL print("Peak relative occupany during the simulation", ptr_SimStats->peak_rel_occupancy)
    CALL print("Step at which the highest occupancy occured", ptr_SimStats->step_highest_occupancy)
END FUNCTION


*/