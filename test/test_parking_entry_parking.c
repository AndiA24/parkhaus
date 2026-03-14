/**
 * @file test_parking_entry_parking.c
 * @brief Unit tests for the entry_parking() function.
 *        Run with `make test_parking_entry_parking`.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/parking.h"
#include "../include/vehicle.h"
#include "../include/stats.h"
#include "../include/config.h"

SimConfig *create_test_config(int num_decks, int spots_per_deck) {
    SimConfig *ptr_config = calloc(1, sizeof *ptr_config);
    if (ptr_config == NULL) {
        printf("Error: Failed to allocate test config.\n");
    }
    ptr_config->num_decks = num_decks;
    ptr_config->spots_per_deck = spots_per_deck;
    ptr_config->initial_occupancy = 0;
    ptr_config->min_parking_duration_steps = 1;
    ptr_config->max_parking_duration_steps = 10;
    ptr_config->sim_duration_steps = 100;
    ptr_config->arrival_probability_percent = 50;
    ptr_config->seed = 42;
    return ptr_config;
}

SimStats *create_test_stats() {
    SimStats *ptr_stats = calloc(1, sizeof *ptr_stats);
    if (ptr_stats == NULL) {
        printf("Error: Failed to allocate test stats.\n");
    }
    return ptr_stats;
}

Vehicle *create_test_vehicle() {
    Vehicle *ptr_vehicle = calloc(1, sizeof *ptr_vehicle);
    if (ptr_vehicle == NULL) {
        printf("Error: Failed to allocate test vehicle.\n");
    }
    return ptr_vehicle;
}

int main() {
    Parking *ptr_parking = NULL;
    Vehicle *ptr_vehicle = NULL;
    SimStats *ptr_stats = NULL;
    SimConfig *ptr_config = NULL;

    // Test 1: all args NULL → returns -1
    printf("Test 1: entry_parking(NULL, NULL, NULL)          → returns -1:  ");
    assert(entry_parking(NULL, NULL, NULL) == -1);
    printf("OK\n");

    // Test 2: parking NULL → returns -1
    printf("Test 2: entry_parking(NULL, valid, valid)        → returns -1:  ");
    ptr_vehicle = create_test_vehicle();
    ptr_stats = create_test_stats();
    assert(entry_parking(NULL, ptr_vehicle, ptr_stats) == -1);
    free(ptr_vehicle);   
    ptr_vehicle = NULL;
    free(ptr_stats);     
    ptr_stats = NULL;
    printf("OK\n");

    // Test 3: vehicle NULL → returns -1
    printf("Test 3: entry_parking(valid, NULL, valid)        → returns -1:  ");
    ptr_config = create_test_config(1, 2);
    ptr_stats = create_test_stats();
    ptr_parking = init_parking(ptr_config, ptr_stats);
    assert(entry_parking(ptr_parking, NULL, ptr_stats) == -1);
    free_parking(ptr_parking); 
    ptr_parking = NULL;
    free(ptr_stats);           
    ptr_stats = NULL;
    free_config(ptr_config);   
    ptr_config = NULL;
    printf("OK\n");

    // Test 4: stats NULL → returns -1
    printf("Test 4: entry_parking(valid, valid, NULL)        → returns -1:  ");
    ptr_config = create_test_config(1, 2);
    ptr_stats = create_test_stats();
    ptr_parking = init_parking(ptr_config, ptr_stats);
    ptr_vehicle = create_test_vehicle();
    assert(entry_parking(ptr_parking, ptr_vehicle, NULL) == -1);
    free(ptr_vehicle);         
    ptr_vehicle = NULL;
    free_parking(ptr_parking); 
    ptr_parking = NULL;
    free(ptr_stats);           
    ptr_stats = NULL;
    free_config(ptr_config);   
    ptr_config = NULL;
    printf("OK\n");

    // Test 5: park one vehicle → returns 1, occupied_count == 1
    printf("Test 5: park one vehicle                         → returns  1:  ");
    ptr_config = create_test_config(1, 2);
    ptr_stats = create_test_stats();
    ptr_parking = init_parking(ptr_config, ptr_stats);
    ptr_vehicle = create_test_vehicle();
    assert(entry_parking(ptr_parking, ptr_vehicle, ptr_stats) == 1);
    assert(ptr_parking->occupied_count == 1);
    assert(ptr_parking->ptr_decks[0].occupied_count == 1);
    assert(ptr_parking->ptr_decks[0].free_spots == 1);         // 2 spots - 1 = 1 free
    free_parking(ptr_parking); 
    ptr_parking = NULL;             
    free(ptr_stats);           
    ptr_stats = NULL;
    free_config(ptr_config);   
    ptr_config = NULL;
    printf("OK\n");

    // Test 6: stats updated after entry → temp_entries & total_entries == 1
    printf("Test 6: stats updated after entry                → entries +1:  ");
    ptr_config = create_test_config(1, 2);
    ptr_stats = create_test_stats();
    ptr_stats->step_num = 5;                                    // simulierter Zeitschritt
    ptr_parking = init_parking(ptr_config, ptr_stats);
    ptr_vehicle = create_test_vehicle();
    entry_parking(ptr_parking, ptr_vehicle, ptr_stats);
    assert(ptr_stats->temp_entries == 1);
    assert(ptr_stats->total_entries == 1);
    assert(ptr_vehicle->entry_time == 5);                      // entry_time == step_num
    free_parking(ptr_parking); 
    ptr_parking = NULL;
    free(ptr_stats);           
    ptr_stats = NULL;
    free_config(ptr_config);   
    ptr_config = NULL;
    printf("OK\n");

    // Test 7: fill all spots → occupied_count == total_capacity
    printf("Test 7: fill all spots (2 decks x 2 spots)       → full:  ");
    ptr_config = create_test_config(2, 2);                     // 4 spots total
    ptr_stats = create_test_stats();
    ptr_parking = init_parking(ptr_config, ptr_stats);
    for (int i = 0; i < 4; i++) {
        ptr_vehicle = create_test_vehicle();
        assert(entry_parking(ptr_parking, ptr_vehicle, ptr_stats) == 1);
    }
    assert(ptr_parking->occupied_count == 4);
    assert(ptr_parking->ptr_decks[0].free_spots == 0);
    assert(ptr_parking->ptr_decks[1].free_spots == 0);
    free_parking(ptr_parking); 
    ptr_parking = NULL;
    free(ptr_stats);           
    ptr_stats = NULL;
    free_config(ptr_config);   
    ptr_config = NULL;
    printf("OK\n");

    // Test 8: park on full parking → returns 0
    printf("Test 8: entry_parking on full parking            → returns  0:  ");
    ptr_config = create_test_config(1, 1);                     // nur 1 Spot
    ptr_stats = create_test_stats();
    ptr_parking = init_parking(ptr_config, ptr_stats);
    ptr_vehicle = create_test_vehicle();
    entry_parking(ptr_parking, ptr_vehicle, ptr_stats);         // Spot belegen
    Vehicle *ptr_vehicle2 = create_test_vehicle();
    assert(entry_parking(ptr_parking, ptr_vehicle2, ptr_stats) == 0);  
    free(ptr_vehicle2);        
    ptr_vehicle2 = NULL;
    free_parking(ptr_parking); 
    ptr_parking = NULL;
    free(ptr_stats);           
    ptr_stats = NULL;
    free_config(ptr_config);   
    ptr_config = NULL;
    printf("OK\n");

    return 0;
}