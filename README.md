# Parking-simulation in C
Team-Repository für den Programmentwurf "Parkhaus" zur Vorlesung Programmieren I an der DHBW Friedrichshafen

## Requirements

- Simulation eines Parkhauses 
- Ein und ausparkende Autos
- begrenzte Parkplätze
- Warteschlange bei vollem Parkhaus
- Zusammenfassung und Darstellung von Statistiken mind. 5 (z.B. durchschnittliche Parkdauer, Auslastung, Wartedauer)
- Empfehlungen zur Erweiterung
- Seed für reproduzierbare Ergebnisse
- Seed als Textdatei speichern
- Pro Zeitschritte ein Auto rein aber unbegrenzt Autos raus
- Parkkosten pro Stunde
- Code must run under Codespaces / Run-File for Codespaces
- User Inputs
    - Zu simulierende Zeitschritte
    - Parkplätze pro Stockwerk
    - Anzahl der Stockwerke
    - Anzahl der Einfahrten
    - Ankunftswahrscheinlichkeit
    - Auflösung der Simulationsschritte
    - Mindest Parkdauer
    - Max Parkdauer
- Output / Stats
    - Per Step
        - rel occupancy
		- cars in queue
		- exits
		- new arrivals
    - End: 
		- rel occupancy
		- average waiting time
        - average staying duration
		- step longest queue
		- step highest occupancy
		- time full occupancy (sum of steps with total occupancy)
		- (revenue)
		- peak queue lenght
		- cars queued percent

## Datastructure / Structs

### SimConfig
```c
typedef struct {
    unsigned int  num_decks;
    unsigned int  spots_per_deck;
    unsigned int  max_parking_duration_steps;
    unsigned int  min_parking_duration_steps;
    unsigned int  sim_duration_steps;
    unsigned char arrival_probability_percent;
    unsigned int  seed;
} SimConfig;
```

### Parking
```c
typedef struct {
    unsigned int  total_capacity;
    unsigned int  occupied_count;
    ParkingDeck  *decks;
} Parking;
```

### ParkingDeck
```c
typedef struct {
    unsigned int  deck_id;
    unsigned int  capacity;
    ParkingSpot  *spots;
} ParkingDeck;
```

### ParkingSpot
```c
typedef struct {
    int      id;
    char     occupied;
    Vehicle *vehicle;
} ParkingSpot;
```

### Vehicle
```c
typedef struct {
    int id;
    int entry_time;
    int remaining_duration; // alt: parking-duration
    int queue_time;
} Vehicle;
```

### QueueNode
```c
typedef struct QueueNode {
    Vehicle          *vehicle;
    QueueNode        *previous;
    QueueNode        *next;
} QueueNode;
```

### Queue

```c
typedef struct {
    QueueNode *head;
    QueueNode *tail;
    int        size;
} Queue;
```

### SimStats
Collect stats for current step before writing to disk.
```c
typedef struct {
    unsigned int step_num;               /**< Current simulation step number. */

    /* --- Per-step stats (overwritten each step) --- */
    unsigned int temp_exits;                    /**< Cars that exited this step. */
    unsigned int temp_entrys;                   /**< New arrivals this step. */
    float        temp_rel_occupancy_precent;    /**< Relative occupancy this step (0.0–100.0). */
    unsigned int temp_queue_length;             /**< Cars in queue at end of this step. */

    /* --- Cumulative stats (accumulated until end) --- */
    unsigned int total_exits;                   /**< Total cars exited over all steps. */
    unsigned int total_entrys;                  /**< Total cars arrived over all steps. */
    unsigned int total_queued;                  /**< Total cars that had to wait in queue. */
    unsigned int total_queue_time;              /**< Sum of all queue waiting times (in steps). */
    unsigned int total_parking_time;            /**< Sum of all parking durations (in steps). */
    unsigned int time_full_occupancy;           /**< Steps where parking was at full capacity. */

    /* --- Tracked extremes for final report --- */
    unsigned int peak_queue_length;             /**< Peak queue length observed. */
    unsigned int step_longest_queue;            /**< Step at which peak queue length occurred. */
    float        peak_rel_occupancy;            /**< Peak relative occupancy observed (0.0–100.0). */
    unsigned int step_highest_occupancy;        /**< Step at which peak occupancy occurred. */
} SimStats;
```

## Functions

### load_config
Function to load simulation params from .json / .txt or generate if missed.
```c

```

### load_seed
```c

```

### write_stats
```c

```