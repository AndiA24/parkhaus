/**
 * @file test_parking_entry_parking.c
 * @brief Unit tests for entry_parking() function, covering NULL guards
 *        correct vehicle placement and stat updates.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/parking.h"
#include "../include/vehicle.h"
#include "../include/stats.h"

static Parking *create_test_parking(unsigned int decks, unsigned int spots_per_deck) {
    Parking *ptr_parking = malloc(sizeof(*ptr_parking));
    ptr_parking->total_capacity = decks * spots_per_deck;
    ptr_parking->occupied_count = 0;
    ptr_parking->decks = decks;
    ptr_parking->ptr_decks = calloc(decks, sizeof(*ptr_parking->ptr_decks));
    ptr_parking->ptr_occupied_spots = calloc(decks * spots_per_deck, sizeof(*ptr_parking->ptr_occupied_spots));

    for (int i = 0; i < (int)decks; i++) {
        ParkingDeck *ptr_deck = ptr_parking->ptr_decks + i;
        ptr_deck->deck_id = i;
        ptr_deck->capacity = spots_per_deck;
        ptr_deck->occupied_count = 0;
        ptr_deck->free_spots = 0;
        ptr_deck->ptr_spots = calloc(spots_per_deck, sizeof(*ptr_deck->ptr_spots));
        ptr_deck->ptr_stack = calloc(spots_per_deck, sizeof(*ptr_deck->ptr_stack));

        for (int j = 0; j < (int)spots_per_deck; j++) {
            ptr_deck->ptr_spots[j].id = (i * spots_per_deck) + j;
            ptr_deck->ptr_stack[ptr_deck->free_spots] = &ptr_deck->ptr_spots[j];
            ptr_deck->free_spots++;
        }
    }
    return ptr_parking;
}

static Vehicle *create_test_vehicle() {
    Vehicle *ptr_vehicle = calloc(1, sizeof(*ptr_vehicle));
    return ptr_vehicle;
}

static SimStats *create_test_stats() {
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    return ptr_stats;
}


int main() {
    Parking  *ptr_parking = NULL;
    Vehicle  *ptr_vehicle = NULL;
    SimStats *ptr_stats = NULL;

    // Test 1: NULL Guards
    printf("Test 1: NULL Guards: ");
    ptr_parking = create_test_parking(1, 5);
    ptr_vehicle = create_test_vehicle();
    ptr_stats = create_test_stats();
    assert(entry_parking(NULL, NULL, NULL) == -1);
    assert(entry_parking(NULL, ptr_vehicle, ptr_stats) == -1);
    assert(entry_parking(ptr_parking, NULL, ptr_stats) == -1);
    assert(entry_parking(ptr_parking, ptr_vehicle, NULL) == -1);
    free_parking(ptr_parking);
    free(ptr_vehicle);
    free(ptr_stats);
    ptr_parking = NULL; 
    ptr_vehicle = NULL; 
    ptr_stats = NULL;
    printf("OK\n");

    // Test 2: correct placment of the car 
    //
    // Expected values after call:
    //   return value = 1
    //   spot->occupied = 1
    //   spot->ptr_vehicle = ptr_vehicle
    //   parking->occupied_count = 1
    //   deck->occupied_count = 1
    //   simstats->temp_entries = 1
    //   simstats->total_entries = 1
    //   vehicle->entry_time = 42
    printf("Test 2: Correct Parking: ");
    ptr_parking = create_test_parking(1, 5);
    ptr_vehicle = create_test_vehicle();
    ptr_stats   = create_test_stats();
    ptr_stats->step_num = 42;
    assert(entry_parking(ptr_parking, ptr_vehicle, ptr_stats) == 1);
    assert(ptr_parking->occupied_count == 1);
    assert(ptr_parking->ptr_decks[0].occupied_count == 1);
    assert(ptr_parking->ptr_occupied_spots[0]->occupied == 1);
    assert(ptr_parking->ptr_occupied_spots[0]->ptr_vehicle == ptr_vehicle);
    assert(ptr_stats->temp_entries == 1);
    assert(ptr_stats->total_entries == 1);
    assert(ptr_vehicle->entry_time == 42);
    free_parking(ptr_parking);
    free(ptr_stats);
    ptr_parking = NULL; 
    ptr_vehicle = NULL; 
    ptr_stats = NULL;
    printf("OK\n");


    return 0;
}
