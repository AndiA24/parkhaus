/**
 * @file test_parking_check_exits.c
 * @brief Unit tests for check_exit() function, covering NULL guards
 *        correct vehicle after time expiry
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/parking.h"
#include "../include/vehicle.h"
#include "../include/stats.h"


static Parking *create_test_parking(unsigned int decks, unsigned int spots_per_deck){
    Parking *ptr_parking = malloc(sizeof(*ptr_parking));
    ptr_parking->total_capacity = decks * spots_per_deck;
    ptr_parking->occupied_count = 0;
    ptr_parking->decks = decks;
    ptr_parking->ptr_decks = calloc(decks, sizeof(*ptr_parking->ptr_decks));
    ptr_parking->ptr_occupied_spots = calloc(decks * spots_per_deck, sizeof(*ptr_parking->ptr_occupied_spots));

    for (int i = 0; i < (int)decks; i++){
        ParkingDeck *ptr_deck = ptr_parking->ptr_decks + i;
        ptr_deck->deck_id = i;
        ptr_deck->capacity = spots_per_deck;
        ptr_deck->occupied_count = 0;
        ptr_deck->free_spots = 0;
        ptr_deck->ptr_spots = calloc(spots_per_deck, sizeof(*ptr_deck->ptr_spots));
        ptr_deck->ptr_stack = calloc(spots_per_deck, sizeof(*ptr_deck->ptr_stack));

        for (int j = 0; j < (int)spots_per_deck; j++){
            ptr_deck->ptr_spots[j].id = (i * spots_per_deck) + j;
            ptr_deck->ptr_stack[ptr_deck->free_spots] = &ptr_deck->ptr_spots[j];
            ptr_deck->free_spots++;
        }
    }
    return ptr_parking;
}

static SimStats *create_test_stats(){
    SimStats *ptr_stats = calloc(1, sizeof(*ptr_stats));
    return ptr_stats;
}

static void place_vehicle(Parking *ptr_parking, int deck, int spot,
                          unsigned int entry_time, unsigned int parking_duration){
    Vehicle *ptr_vehicle = calloc(1, sizeof(*ptr_vehicle));
    ptr_vehicle->entry_time = entry_time;
    ptr_vehicle->parking_duration = parking_duration;

    ParkingSpot *ptr_spot = &ptr_parking->ptr_decks[deck].ptr_spots[spot];
    ptr_spot->ptr_vehicle = ptr_vehicle;
    ptr_spot->occupied = 1;
    ptr_parking->ptr_decks[deck].occupied_count++;
    ptr_parking->ptr_decks[deck].free_spots--;
    ptr_parking->ptr_occupied_spots[ptr_parking->occupied_count] = ptr_spot;
    ptr_parking->occupied_count++;
}


int main() {
    Parking  *ptr_parking = NULL;
    SimStats *ptr_stats   = NULL;

    // Test 1: NULL Guards
    printf("Test 1: NULL Guards: ");
    ptr_parking = create_test_parking(1, 5);
    ptr_stats = create_test_stats();
    assert(check_exit(NULL, NULL) == -1);
    assert(check_exit(NULL, ptr_stats) == -1);
    assert(check_exit(ptr_parking, NULL) == -1);
    free_parking(ptr_parking, ptr_stats);
    free(ptr_stats);
    ptr_parking = NULL; 
    ptr_stats = NULL;
    printf("OK\n");

    // Test 2: Remove Vehicle from parking
    //
    // Expected values after call:
    //   return value = 1
    //   parking->occupied_count = 0
    //   deck->occupied_count = 0
    //   deck->free_spots = 5
    //   spot->occupied = 0
    //   spot->ptr_vehicle = NULL
    //   stats->temp_exits = 1
    //   stats->total_exits = 1
    //   stats->total_parking_time = 5
    printf("Test 2: Remove Vehicle from Parking: ");
    ptr_parking = create_test_parking(1, 5);
    ptr_stats = create_test_stats();
    // vehicle entered in step 0, staying 5 steps, time is over now
    ptr_stats->step_num = 5;
    place_vehicle(ptr_parking, 0, 0, 0, 5);
    assert(check_exit(ptr_parking, ptr_stats) == 1);
    // check if all values ar set correct after exit
    assert(ptr_parking->occupied_count == 0);
    assert(ptr_parking->ptr_decks[0].occupied_count == 0);
    assert(ptr_parking->ptr_decks[0].free_spots == 5);
    assert(ptr_parking->ptr_decks[0].ptr_spots[0].occupied == 0);
    assert(ptr_parking->ptr_decks[0].ptr_spots[0].ptr_vehicle == NULL);
    // check if stats are updated
    assert(ptr_stats->temp_exits == 1);
    assert(ptr_stats->total_exits == 1);
    assert(ptr_stats->total_parking_time == 5);
    free_parking(ptr_parking, ptr_stats);
    free(ptr_stats);
    ptr_parking = NULL; 
    ptr_stats = NULL;
    printf("OK\n");

    // Test 4: Several Vehicles in Parking, one exits
    //
    // Expected values after call:
    //   return value = 1
    //   parking->occupied_count = 1
    //   stats->temp_exits = 1
    //   stats->total_exits = 1
    printf("Test 4: Mehrere Fahrzeuge, nur eines verlaesst: ");
    ptr_parking = create_test_parking(1, 5);
    ptr_stats   = create_test_stats();
    ptr_stats->step_num = 5;
    place_vehicle(ptr_parking, 0, 0, 0, 3);   // exits: (5-0) >= 3
    place_vehicle(ptr_parking, 0, 1, 0, 10);  // stays:   (5-0) < 10
    assert(check_exit(ptr_parking, ptr_stats) == 1);
    assert(ptr_parking->occupied_count == 1);
    assert(ptr_stats->temp_exits == 1);
    assert(ptr_stats->total_exits == 1);
    free_parking(ptr_parking, ptr_stats);
    free(ptr_stats);
    ptr_parking = NULL; ptr_stats = NULL;
    printf("OK\n");

    return 0;
}