#include "../include/config.h"

/*

FUNCTION show_welcome(Struct SimConfig)
    active <- true
    render_welcome()

    WHILE active
        key <- get_input()
        
        IF key = 'Q'
            RETURN quit
        ELSE IF key = 'S'
            show_settings(SimConfig)
        ELSE IF key = 'Enter'
            RETURN simulation_go
        END IF
    END WHILE
END FUNCTION


FUNCTION show_settings(Struct SimConfig)
    active <- true
    render_settings(SimConfig)

    WHILE active
        key <- get_input()
        
        IF key = '1'
            SimConfig.num_decks <- prompt_input("Number of Decks", SimConfig.num_decks, 1, 99)
        ELSE IF key = '2'
            SimConfig.spots_per_deck <- prompt_input("Spots per Deck", SimConfig.spots_per_deck, 1, 999)
        ELSE IF key = '3'
            SimConfig.initial_occupancy <- prompt_input("Initial Occupancy", SimConfig.initial_occupancy, 0, 999)
        ELSE IF key = '4'
            SimConfig.max_parking_duration_steps <- prompt_input("Max Parking Duration", SimConfig.max_parking_duration_steps, 1, 9999)
        ELSE IF key = '5'
            SimConfig.min_parking_duration_steps <- prompt_input("Min Parking Duration", SimConfig.min_parking_duration_steps, 1, 9999)
        ELSE IF key = '6'
            SimConfig.sim_duration_steps <- prompt_input("Simulation Duration", SimConfig.sim_duration_steps, 1, 9999)
        ELSE IF key = '7'
            SimConfig.arrival_probability_percent <- prompt_input("Arrival Probability %", SimConfig.arrival_probability_percent, 0, 100)
        ELSE IF key = '8'
            SimConfig.seed <- prompt_input("RNG Seed", SimConfig.seed, 0, 9999)
        ELSE IF key = 'ESC' || 'Enter' || 'Q'
            active <- false
        END IF
    END WHILE
END FUNCTION


FUNCTION prompt_input(name, current_value, min, max)

    valid <- false
    render_prompt(name, current_value)

    WHILE NOT valid
        input <- get_text_input()
        
        IF input is a valid number AND input >= min AND input <= max
            valid <- true
        ELSE
            render_error("Please enter a correct value between min and max")
        END IF
    END WHILE
    
    RETURN input
END FUNCTION

FUNCTION render_settings(Struct SimConfig)
    print("Number of Decks", SimConfig.num_decks)
    print("Spots per Deck", SimConfig.spots_per_deck)
    print("Initial Occupancy", SimConfig.initial_occupancy)
    print("Max Parking Duration", SimConfig.max_parking_duration_steps)
    print("Min Parking Duration", SimConfig.min_parking_duration_steps)
    print("Simulation Duration", SimConfig.sim_duration_steps)
    print("Arrival Probability %", SimConfig.arrival_probability_percent)
    print("RNG Seed", SimConfig.seed)
END FUNCTION

FUNCTION show_running(Struct ptr_SimStats)
    print("Exists this time step", ptr_SimStats-> temp_exits)
    print("Entrys this time step", ptr_SimStats-> temp_entrys)
    print("Relative Occupancy this time step", ptr_SimStats-> temp_rel_occupancy_precent)
    print("Current queue length", ptr_SimStats-> temp_queue_length)
END FUNCTION

FUNCTION show_results(Struct ptr_SimStats)
    print("Total cars that left the car park", ptr_SimStats->temp_exits)
    print("Total cars that entered the car park", ptr_SimStats->total_entrys)
    print("Total cars that had to wait in queue", ptr_SimStats->total_queued)
    print("Sum of all queue steps", ptr_SimStats->total_queue_time)
    print("Steps cars spent in the car park", ptr_SimStats->total_parking_time)
    print("Steps the parking garage was full", ptr_SimStats->time_full_occupancy)
    print("Peak queue length during the simulation", ptr_SimStats->peak_queue_length)
    print("Step at which the queue was the longest", ptr_SimStats->step_longest_queue)
    print("Peak relative occupany during the simulation", ptr_SimStats->peak_rel_occupancy)
    print("Step at which the highest occupancy occured", ptr_SimStats->step_highest_occupancy)
END FUNCTION


*/