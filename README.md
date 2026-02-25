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
    unsigned int step_num;
    // stats ...
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