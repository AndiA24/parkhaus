/**
 * @file test_parking_init_parking.c
 * @brief Unit tests for the init_parking() function, covering NULL pointer
 *        inputs, correct struct initialization, and initial vehicle placement.
 *        Run with `make test_init_parking`.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/parking.h"
#include "../include/stats.h"
#include "../include/config.h"
#include "../include/vehicle.h"


SimConfig *create_test_config(){
    SimConfig *ptr_config = calloc(1, sizeof(*ptr_config));
    ptr_config->initial_occupancy = 50;
    ptr_config->num_decks = 10;
    ptr_config->spots_per_deck = 20;
    return ptr_config;
}

SimStats *create_test_stats(){
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    return ptr_stats;
}

void parking_cleanup(){

}

int main(){
    SimConfig *ptr_config = NULL;
    SimStats *ptr_stats = NULL;
    Parking *ptr_parking = NULL;

    // Test 1: Both Args are NULL
    printf("Test 1: Both Args are NULL:  ");
    assert( init_parking(NULL, NULL) == NULL);
    printf("OK\n\n");

    // Test 2: Stats Pointer is NULL
    printf("Test 2: Stats Argument is NULL:  ");
    ptr_config = create_test_config();
    assert(init_parking(ptr_config, NULL) == NULL);
    free(ptr_config);
    ptr_config = NULL;
    printf("OK\n\n");

    // Test 3: Config Pointer is NULL
    printf("Test 3: Config Argument is NULL:  ");
    ptr_stats = create_test_stats();
    assert(init_parking(NULL, ptr_stats) == NULL);
    free(ptr_stats);
    ptr_stats = NULL;
    printf("OK\n\n");

    // Test 4: Valid config, no initial occupancy: checks correct structure of the parking (decks / spots)
    printf("Test 4: Valid config without initial_occupancy: ");
    ptr_config = calloc(1, sizeof(*ptr_config));
    ptr_config->num_decks = 5;
    ptr_config->spots_per_deck = 10;
    ptr_config->initial_occupancy = 0;
    ptr_stats = create_test_stats();
    ptr_parking = init_parking(ptr_config, ptr_stats);
    assert(ptr_parking != NULL);
    assert(ptr_parking->total_capacity == 50);
    assert(ptr_parking->decks == 5);
    assert(ptr_parking->occupied_count == 0);
    for(int i = 0; i < (int)ptr_parking->decks; i++){
        assert((ptr_parking->ptr_decks + i)->deck_id == (unsigned int)i);
        assert((ptr_parking->ptr_decks + i)->capacity == 10);
        for(int j = 0; j < 10; j++){
            assert(((ptr_parking->ptr_decks + i)->ptr_spots + j)->id == (i * 10 + j));
            assert(((ptr_parking->ptr_decks + i)->ptr_spots + j)->occupied == 0);
            assert(((ptr_parking->ptr_decks + i)->ptr_spots + j)->ptr_vehicle == NULL);
        }
    }
    free_parking(ptr_parking, ptr_stats);
    free(ptr_config);
    free(ptr_stats);
    ptr_parking = NULL; ptr_config = NULL; ptr_stats = NULL;
    printf("\n");
    printf("OK\n\n");

    // Test 5: Valid config with initial occupancy: checks correct amount of vehicles are placed
    printf("Test 5: Valid config with initial_occupancy: ");
    ptr_config = calloc(1, sizeof(*ptr_config));
    ptr_config->num_decks = 5;
    ptr_config->spots_per_deck = 10;
    ptr_config->initial_occupancy = 20;
    ptr_stats = create_test_stats();
    ptr_parking = init_parking(ptr_config, ptr_stats);
    assert(ptr_parking != NULL);
    assert(ptr_parking->occupied_count == 20);
    free_parking(ptr_parking, ptr_stats);
    free(ptr_config);
    free(ptr_stats);
    ptr_parking = NULL; ptr_config = NULL; ptr_stats = NULL;
    printf("\n");
    printf("OK\n\n");

    return 0;
}