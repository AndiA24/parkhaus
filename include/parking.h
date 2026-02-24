#include "vehicle.h"
#include "stats.h"

typedef struct {
    int      id;
    char     occupied;
    Vehicle *ptr_vehicle;
} ParkingSpot;

typedef struct {
    unsigned int  deck_id;
    unsigned int  capacity;
    ParkingSpot  *ptr_spots;
} ParkingDeck;

typedef struct {
    unsigned int  total_capacity;
    unsigned int  occupied_count;
    ParkingDeck  *ptr_decks;
} Parking;

/**
 * @brief Parks a vehicle in the first available spot in the parking lot.
 *
 * Searches all decks and spots for a free parking spot and assigns
 * the given vehicle to it. Updates the occupied count and records
 * the entry in the simulation statistics.
 *
 * @param[in,out] parking  Pointer to the parking lot structure
 * @param[in]     vehicle  Pointer to the vehicle entering the parking lot
 * @param[in,out] simstats Pointer to the current simulation statistics
 */
void entry_parking(Parking *ptr_parking, Vehicle *ptr_vehicle, SimStats *ptr_simstats) {}

/**
 * @brief Checks all parking spots for vehicles that have exceeded their parking duration.
 *
 * Iterates over all decks and spots, and removes any vehicle whose
 * remaining parking duration has expired. Frees the corresponding
 * spot and updates the occupied count and simulation statistics accordingly.
 *
 * @param[in,out] parking  Pointer to the parking lot structure
 * @param[in,out] simstats Pointer to the current simulation statistics
 */
void check_exit(Parking *ptr_parking, SimStats *ptr_simstats){}