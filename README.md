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
- User Inputs
    - Zu simulierende Zeitschritte
    - Parkplätze pro Stockwerk
    - Anzahl der Stockwerke
    - Anzahl der Einfahrten
    - Ankunftswahrscheinlichkeit
    - Auflösung der Simulationsschritte
    - Mindest Parkdauer
    - Max Parkdauer

## Datenstruktur / Structs

### sim-config
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

### parking
```c
typedef struct {
    unsigned int  total_capacity;
    unsigned int  occupied_count;
    ParkingDeck  *decks;
} Parking;
```

### parking deck
```c
typedef struct {
    unsigned int  deck_id;
    unsigned int  capacity;
    ParkingSpot  *spots;
} ParkingDeck;
```

### parking-spot
```c
typedef struct {
    int      id;
    char     occupied;
    Vehicle *vehicle;
} ParkingSpot;
```

### vehicle
```c
typedef struct {
    int id;
    int entry_time;
    int remaining_duration; // alt: parking-duration
    int queue_time;
} Vehicle;
```

### queueNode
```c
typedef struct QueueNode {
    Vehicle          *vehicle;
    QueueNode        *previous;
    QueueNode        *next;
} QueueNode;
```

### queue
```c
typedef struct {
    QueueNode *head;
    QueueNode *tail;
    int        size;
} Queue;
```

### sim-stats (collect stats for current step before writing to disk)
```c
typedef struct {
    unsigned int step_num;
    // stats ...
} SimStats;
```