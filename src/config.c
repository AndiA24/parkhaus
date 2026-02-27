#include "../include/config.h"

/*

FUNCTION show_welcome(settings)
    active <- true
    render_welcome()

    WHILE active
        key <- get_input()
        
        IF key = 'Q'
            RETURN quit
        ELSE IF key = 'S'
            show_settings(settings)
        ELSE IF key = 'Enter'
            RETURN simulation_go
        END IF
    END WHILE
END FUNCTION


FUNCTION show_settings(struct settings)
    active <- true
    render_settings(settings)

    WHILE active
        key <- get_input()
        
        IF key = '1'
            settings.num_decks <- prompt_input("Number of Decks", settings.num_decks, 1, 99)
        ELSE IF key = '2'
            settings.spots_per_deck <- prompt_input("Spots per Deck", settings.spots_per_deck, 1, 999)
        ELSE IF key = '3'
            settings.initial_occupancy <- prompt_input("Initial Occupancy", settings.initial_occupancy, 0, 999)
        ELSE IF key = '4'
            settings.max_parking_duration_steps <- prompt_input("Max Parking Duration", settings.max_parking_duration_steps, 1, 9999)
        ELSE IF key = '5'
            settings.min_parking_duration_steps <- prompt_input("Min Parking Duration", settings.min_parking_duration_steps, 1, 9999)
        ELSE IF key = '6'
            settings.sim_duration_steps <- prompt_input("Simulation Duration", settings.sim_duration_steps, 1, 9999)
        ELSE IF key = '7'
            settings.arrival_probability_percent <- prompt_input("Arrival Probability %", settings.arrival_probability_percent, 0, 100)
        ELSE IF key = '8'
            settings.seed <- prompt_input("RNG Seed", settings.seed, 0, 9999)
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

FUNCTION render_settings(struct settings)
    print(""Number of Decks", settings.num_decks)
    print("Spots per Deck", settings.spots_per_deck)
    print("Initial Occupancy", settings.initial_occupancy)
    print("Max Parking Duration", settings.max_parking_duration_steps)
    print("Min Parking Duration", settings.min_parking_duration_steps)
    print("Simulation Duration", settings.sim_duration_steps)
    print("Arrival Probability %", settings.arrival_probability_percent)
    print("RNG Seed", settings.seed)
END FUNCTION

FUNCTION show_running()
        render_running_screen()
END FUNCTION


FUNCTION show_results(*result)
        render_results(*result)
END FUNCTION

*/