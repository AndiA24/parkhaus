/**
 * @file test_parking_init_occ.c
 * @brief Unit tests for the initial_occupancy() function, covering NULL pointer
 *        inputs, insufficient capacity, and correct vehicle placement.
 *        test using `make test_init_occ`
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/parking.h"
#include "../include/config.h"
#include "../include/stats.h"
#include "../include/vehicle.h"
#include "../src/parking.c"
#include "../src/config.c"
#include "../src/stats.c"
#include "../src/vehicle.c"

Parking *create_test_parking(unsigned int decks, unsigned int spots_per_deck){
    Parking *ptr_parking = malloc(sizeof(*ptr_parking));

    ptr_parking->total_capacity = (decks * spots_per_deck);
    ptr_parking->occupied_count = 0;
    ptr_parking->decks = decks;
    ptr_parking->ptr_decks = NULL;

    ptr_parking->ptr_decks = calloc(decks, sizeof(ParkingDeck));

    for(int i = 0; i < (int)decks; i++){
        (ptr_parking->ptr_decks + i)->deck_id = i;
        (ptr_parking->ptr_decks + i)->capacity = spots_per_deck;
        (ptr_parking->ptr_decks + i)->occupied_count = 0;
        (ptr_parking->ptr_decks + i)->ptr_spots = calloc(spots_per_deck, sizeof(ParkingSpot));
    }
    return ptr_parking;
}

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


int main(){
    // Unit-test for initial_occupancy
    SimConfig *ptr_config = NULL;
    SimStats *ptr_stats = NULL;
    Parking *ptr_parking = NULL;

    // Test 1: all args NULL
    printf("Test 1: All args NULL:  ");
    assert(initial_occupancy(NULL, NULL, NULL) == -1);
    printf("OK\n");

    // Test 2: parking pointer NULL
    printf("Test 2: Parking Pointer is NULL: ");
    ptr_config = create_test_config();
    ptr_stats = create_test_stats();
    assert(initial_occupancy(NULL, ptr_config, ptr_stats) == -1);
    free(ptr_config);
    free(ptr_stats);
    ptr_config = NULL;
    ptr_stats = NULL;
    printf("OK\n");

    // Test 3: stats pointer NULL
    printf("Test 3: Stats Pointer is NULL: ");
    ptr_parking= create_test_parking(10,20);
    ptr_config = create_test_config();
    assert(initial_occupancy(ptr_parking, ptr_config, NULL) == -1);
    free_parking(ptr_parking);
    free(ptr_config);
    ptr_parking = NULL;
    ptr_config = NULL;
    printf("OK\n");

    // Test 4: config Pointer NULL
    printf("Test 4: Config Ponter is NULL: ");
    ptr_parking = create_test_parking(10, 20);
    ptr_stats = create_test_stats();
    assert(initial_occupancy(ptr_parking, NULL, ptr_stats) == -1);
    free_parking(ptr_parking);
    free(ptr_stats);
    ptr_parking = NULL;
    ptr_stats = NULL;
    printf("OK\n");

    // Test 5: higher occupancy then spots
    printf("Test 5: Initial Occ is higher then free spots: ");
    ptr_parking = create_test_parking(4, 10);
    ptr_config = create_test_config();
    ptr_stats = create_test_stats();
    assert(initial_occupancy(ptr_parking, ptr_config, ptr_stats) == -2);
    free_parking(ptr_parking);
    free(ptr_config);
    free(ptr_stats);
    ptr_parking = NULL;
    ptr_config = NULL;
    ptr_stats = NULL;
    printf("OK\n");


    // Test 6: correct Inputs
    printf("Test 6: All inputs correct: ");
    ptr_parking = create_test_parking(10, 20);
    ptr_config = create_test_config();
    ptr_stats = create_test_stats();
    assert(initial_occupancy(ptr_parking, ptr_config, ptr_stats) == 0);
    int vehicle_count = 0;
    for(int i = 0; i < (int)ptr_parking->decks; i++){
        for(int j = 0; j < (int)(ptr_parking->total_capacity / ptr_parking->decks); j++){
            if(((ptr_parking->ptr_decks + i)->ptr_spots + j)->ptr_vehicle != NULL && ((ptr_parking->ptr_decks + i)->ptr_spots + j)->occupied == 1){
                vehicle_count++;
            }
        }
    }
    assert(vehicle_count == (int)ptr_config->initial_occupancy);
    printf("OK\n");
    free_parking(ptr_parking);
    free(ptr_config);
    free(ptr_stats);
}