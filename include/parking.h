#include "vehicle.h"
#include "stats.h"

/**
 * @brief Represents a single parking spot within a deck.
 */
typedef struct {
    int         id;           /**< Unique identifier of the parking spot. */
    char        occupied;     /**< Flag indicating whether the spot is occupied (1) or free (0). */
    Vehicle     *ptr_vehicle;  /**< Pointer to the vehicle currently occupying the spot, or NULL if free. */
} ParkingSpot;

/**
 * @brief Represents one deck (floor) of the parking garage.
 */
typedef struct {
    unsigned int    deck_id;    /**< Unique identifier of this deck. */
    unsigned int    capacity;   /**< Total number of parking spots on this deck. */
    ParkingSpot     *ptr_spots;  /**< Pointer to the array of parking spots on this deck. */
} ParkingDeck;

/**
 * @brief Represents the entire parking garage.
 */
typedef struct {
    unsigned int    total_capacity;  /**< Total number of parking spots across all decks. */
    unsigned int    occupied_count;  /**< Number of spots currently occupied. */
    ParkingDeck     *ptr_decks;       /**< Pointer to the array of decks in the garage. */
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
void check_exit(Parking *ptr_parking, SimStats *ptr_simstats){
    
}