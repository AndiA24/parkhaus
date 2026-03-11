#ifndef PARKING_H
#define PARKING_H

#include "vehicle.h"
#include "stats.h"
#include "config.h"

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
    unsigned int    occupied_count;  /**< Number of spots currently occupied. */
    ParkingSpot     *ptr_spots;  /**< Pointer to the array of parking spots on this deck. */
} ParkingDeck;

/**
 * @brief Represents the entire parking garage.
 */
typedef struct {
    unsigned int    total_capacity;  /**< Total number of parking spots across all decks. */
    unsigned int    decks;           /**< Total number of parking decks in the parking. */
    unsigned int    occupied_count;  /**< Number of spots currently occupied. */
    ParkingDeck     *ptr_decks;      /**< Pointer to the array of decks in the garage. */
} Parking;

/**
 * @brief Fills the parking structure with an initial set of vehicles.
 *
 * Populates the given parking structure with the number of vehicles specified
 * in @p ptr_config->initial_occupancy. If the operation fails (e.g. memory
 * allocation error), all previously allocated memory is freed and NULL is
 * returned.
 *
 * @param[in,out] ptr_parking Pointer to the Parking structure to be populated.
 * @param[in]     ptr_config  Pointer to the simulation configuration containing
 *                            the initial occupancy count.
 * @param[in,out] ptr_stats   Pointer to the Stats structure to get current Vehicle
 *                            ID and increment.
 * @return Pointer to the populated Parking structure, or NULL on failure.
 */
Parking *initial_occupancy(Parking *ptr_parking, SimConfig *ptr_config, SimStats *ptr_stats);

/**
 * @brief Create Parking Struct containing Parking decks and spots
 *  Creates Parking structure with all containing Deck and Spot structs
 *  and prefills the Parking with a given amount of vehicles.
 * 
 *
 * @param[in]       ptr_config  Pointer to Config struct containing number of decks and spots
 * @param[in,out]   ptr_stats   Pointer to Stats Struct to get and increment ID-count
 * @return          Pointer to the created parking structure
 */
Parking *init_parking(SimConfig *ptr_config, SimStats *ptr_stats);

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
 * @return 1 on success, 0 if vehicle cannot be assigned, -1 if any param is NULL
 */
int entry_parking(Parking *ptr_parking, Vehicle *ptr_vehicle, SimStats *ptr_simstats);

/**
 * @brief Checks all parking spots for vehicles that have exceeded their parking duration.
 *
 * Iterates over all decks and spots, and removes any vehicle whose
 * remaining parking duration has expired. Frees the corresponding
 * spot and updates the occupied count and simulation statistics accordingly.
 *
 * @param[in,out] parking  Pointer to the parking lot structure
 * @param[in,out] simstats Pointer to the current simulation statistics
 * @return 1 on success, -1 if any param is NULL
 */
int check_exit(Parking *ptr_parking, SimStats *ptr_simstats);


/**
 * @brief Returns the number of available parking spots.
 *
 * Iterates through the parking structure and counts all spots
 * that are currently free.
 *
 * @param[in] ptr_parking Pointer to the Parking structure
 * @return 1 on success, -1 if any param is NULL
 */
int get_free_spots(Parking *ptr_parking, SimStats *ptr_stats);

/**
 * @brief Frees all dynamically allocated memory associated with the Parking structure.
 *
 * Frees the Parking structure that was allocated by init_parking
 *
 * @param[in] ptr_parking Pointer to the Parking structure to be freed.
 * @return 1 on success, -1 if ptr_parking is NULL
 */
int free_parking(Parking *ptr_parking);

#endif