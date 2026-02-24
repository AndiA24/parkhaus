#include "vehicle.h"

typedef struct {
    int      id;
    char     occupied;
    Vehicle *vehicle;
} ParkingSpot;

typedef struct {
    unsigned int  deck_id;
    unsigned int  capacity;
    ParkingSpot  *spots;
} ParkingDeck;

typedef struct {
    unsigned int  total_capacity;
    unsigned int  occupied_count;
    ParkingDeck  *decks;
} Parking;