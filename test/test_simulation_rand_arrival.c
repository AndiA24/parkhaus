/**
 * @file test_simulation_rand_arrival.c
 * @brief Unit tests for the rand_arrival() function, covering NULL
 *        guards, behaviour at edge cases and and seeded random behaviour.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/simulation.h"
#include "../include/config.h"

// helper function to create a SimConfig struct for testing
// static to avoid collisions with similar functions in the main code
static SimConfig *create_test_config() {
    SimConfig *ptr_config = calloc(1, sizeof(*ptr_config));
    if (ptr_config == NULL) {
        printf("Error: Failed to allocate memory for the testing config struct.\n");
    }
    return ptr_config;
}

int main() {
    SimConfig *ptr_config = NULL;

    // Test 1: ptr_config is NULL
    printf("Test 1: ptr_config is NULL: ");
    assert(rand_arrival(NULL) == 0);
    printf("OK\n");

    // Test 2: arrival_probability_percent = 0
    //
    // Expected values after call:
    //   return value = 0 for every run
    printf("Test 2: arrival_probability_percent = 0, never arrives: ");
    ptr_config = create_test_config();
    ptr_config->arrival_probability_percent = 0;
    assert(rand_arrival(ptr_config) == 0);
    assert(rand_arrival(ptr_config) == 0);
    assert(rand_arrival(ptr_config) == 0);
    free(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    // Test 3: arrival_probability_percent = 100
    //
    // Expected values after call:
    //   return value = 1 for every run
    printf("Test 3: arrival_probability_percent = 100, always arrives: ");
    ptr_config = create_test_config();
    ptr_config->arrival_probability_percent = 100;
    assert(rand_arrival(ptr_config) == 1);
    assert(rand_arrival(ptr_config) == 1);
    assert(rand_arrival(ptr_config) == 1);
    free(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    // Test 4: Known seed
    printf("Test 4: Known seed: ");
    ptr_config = create_test_config();
    ptr_config->arrival_probability_percent = 10;
    ptr_config->seed = 546373;
    int expect_rand = 0;
    int arrival = 0;
    int rand_return = 0;
    // check for every step aup to the nth if return of rand arrvival
    // matches the expected value generating a rand unsing the same seed
    for(int i = 0; i < 100; i++){
        // to get the expected return set srand, take the nth return of rand
        // and compare with the arrival probability
        srand(ptr_config->seed);
        for(int j = 0; j <= i; j++){
            expect_rand = rand();
        }
        if((expect_rand % 100) + 1 <= (int)ptr_config->arrival_probability_percent){
            arrival = 1;
        }
        else{
            arrival = 0;
        }

        // to get the associated return call rand arrival n times and compar value
        srand(ptr_config->seed);
        for(int k = 0; k <= i; k++){
            rand_return = rand_arrival(ptr_config);
        }
        assert(rand_return == arrival);
    }

    free(ptr_config);
    ptr_config = NULL;
    printf("OK\n");

    return 0;
}
