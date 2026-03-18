[← README](../README.md)

# Architektur & Datenstrukturen

## Inhalt
- [Projektstruktur](#projektstruktur)
- [Code-Konventionen](#code-konventionen)
- [Fehlerbehandlung](#fehlerbehandlung)
- [Module](#module)
- [Datenstrukturen](#datenstrukturen)
  - [SimConfig](#simconfig)
  - [Parking](#parking)
  - [ParkingDeck](#parkingdeck)
  - [ParkingSpot](#parkingspot)
  - [Vehicle](#vehicle)
  - [QueueNode](#queuenode)
  - [Queue](#queue)
  - [SimStats](#simstats)

---

## Projektstruktur

```
parkhaus/
├── src/
│   ├── main.c          # Einstiegspunkt
│   ├── config.c
│   ├── vehicle.c
│   ├── parking.c
│   ├── queue.c
│   ├── simulation.c
│   ├── stats.c
│   ├── ui.c
│   └── utils.c
├── include/
│   ├── config.h
│   ├── vehicle.h
│   ├── parking.h
│   ├── queue.h
│   ├── simulation.h
│   ├── stats.h
│   ├── ui.h
│   └── utils.h
├── test/
│   └── test_*.c        # Unit-Tests je Funktion
├── docs/
│   └── *.md            # Projektdokumentation
├── pdcurses/           # PDCurses-Bibliothek (Windows)
├── build/              # CMake-Build-Ausgabe (nach cmake -B build)
├── parkhaus_config.csv # Gespeicherte Simulationskonfiguration (im Arbeitsverzeichnis)
└── <name>.csv          # Generierte Statistik-Ausgabedatei (im Arbeitsverzeichnis)
```

---

## Code-Konventionen

Der Code folgt den projekteigenen [C Coding Conventions](assignments/c_coding_conventions_for_embedded_systems.md).

**Benennung**
- Variablen, Funktionen, Dateien: `snake_case`
- Konstanten und Makros: `UPPER_CASE`
- Pointer-Variablen tragen das Präfix `ptr_` (z. B. `ptr_config`, `ptr_vehicle`)

**Dokumentation**
- Jede `.c`- und `.h`-Datei beginnt mit einem Doxygen-Dateiheader (`@file`, `@brief`)
- Jede Funktion hat einen Doxygen-Kommentar mit `@brief`, `@param` und `@return` direkt in der zugehörigen `.h`-Datei
- Struct-Felder sind mit Inline-Doxygen (`/**< ... */`) kommentiert

**Struktur**
- Ein Modul = eine `.c`-Datei + eine `.h`-Datei mit klar abgegrenzter Zuständigkeit
- Jede Header-Datei ist durch Include-Guards (`#ifndef`/`#define`/`#endif`) geschützt
- Keine Magic Numbers – alle Konstanten sind per `#define` benannt

**Formatierung**
- 4 Leerzeichen Einrückung, keine Tabs
- Geschweifte Klammern immer gesetzt, auch bei einzeiligen Blöcken

---

## Fehlerbehandlung

Fehlerbehandlung wird konsequent im gesamten Projekt berücksichtigt. Alle Funktionen prüfen ihre Eingabeparameter und geben bei ungültigen oder NULL-Zeigern definierte Fehlercodes zurück (in der Regel `-1`).

### Nicht-fatale Fehler – Programm läuft weiter

Bei nicht-fatalen Fehlern wird die fehlerhafte Operation übersprungen und die Simulation fortgesetzt. Ein Beispiel ist `initial_occupancy()`: Wenn die gewünschte Startbelegung die Kapazität des Parkhauses überschreitet, wird die Funktion mit `-2` abgebrochen, aber das Programm läuft weiter – mit einem leeren Parkhaus statt einer ungültigen Belegung.

### Fatale Fehler – Abbruch mit vollständiger Speicherfreigabe

Bei schwerwiegenden Fehlern (z. B. fehlgeschlagene Speicherallokation mit `malloc`) wird die Simulation abgebrochen. In diesem Fall werden alle bis dahin allokierten Ressourcen explizit freigegeben, bevor das Programm beendet wird. Es entstehen keine Memory Leaks.

### Programmabbruch via `exit()`

In einigen Fehlerpfaden wird `exit()` verwendet, anstatt `free()` explizit aufzurufen. Das ist bewusst so gestaltet: `exit()` beendet den Prozess und gibt dabei den gesamten Heap frei, sodass kein manuelles Aufräumen notwendig ist. Diese Stellen sind im Code klar erkennbar und stellen keine Memory Leaks dar.

---

## Module

| Modul | Beschreibung |
|---|---|
| `main` | Einstiegspunkt — initialisiert alle Komponenten, startet UI und gibt Ressourcen nach Beenden frei |
| `config` | Lesen, Schreiben und Verwalten der Simulationskonfiguration (`SimConfig`) |
| `vehicle` | Erstellen und Freigeben einzelner Fahrzeuge (`Vehicle`) |
| `parking` | Verwaltung des Parkhauses mit Stockwerken und Stellplätzen — Ein-/Ausparken |
| `queue` | Verkettete FiFo-Warteschlange für wartende Fahrzeuge |
| `simulation` | Hauptschleife der Simulation führt vorgegeben Anzahl an Simulationsschritten aus |
| `stats` | Erfassen, Berechnen und Ausgeben aller Statistiken, erstellen der Ausgabedatei |
| `ui` | Terminal-Oberfläche — Willkommensscreen, Einstellungsmenü, Live-Anzeige und Ergebnisausgabe |
| `utils` | Hilfsfunktionen (sauberes Beenden) |

---

## Datenstrukturen

### SimConfig
Enthält die Konfigurationsparameter für die Parksimulation. Wird aus einer Konfigurationsdatei oder durch Benutzereingaben gefüllt und während der gesamten Simulation weitergegeben. Aktualisierte Konfigurationen werden wieder in der Konfigurationsdatei gespeichert.

Für alle Ganzzahlen, die keine negativen Werte annehmen können, werden unsigned Integer verwendet, um bei gleichem Speicherverbrauch einen größeren Wertebereich im Positiven zu erhalten. Auch wenn das bei einigen Parametern nicht notwendig ist, da sie keine so großen Werte annehmen werden, wird das der Ordnung halber bei allen Parametern gemacht.

Durch bearbeiten des Parameters output_file_name kann der nutzer ein namen für das File angeben und somit die Ergebnisse von meherern Simulationen speichern, ohne dass die Alten überschriben werden. Dafür wird ein char Array verwende, um einen String zu speichern.
```c
typedef struct {
    unsigned int num_decks;                     /**< Number of decks (floors) in the parking garage. */
    unsigned int spots_per_deck;                /**< Number of parking spots on each deck. */
    unsigned int initial_occupancy;             /**< Number of vehicles in the parking at simulation start. */
    unsigned int max_parking_duration_steps;    /**< Maximum number of simulation steps a vehicle may stay parked. */
    unsigned int min_parking_duration_steps;    /**< Minimum number of simulation steps a vehicle must stay parked. */
    unsigned int sim_duration_steps;            /**< Total number of steps the simulation runs. */
    unsigned int arrival_probability_percent;   /**< Probability in percent (0–100) that a vehicle arrives in a given step. */
    char         output_file_name[70];          /**< Name of the Stats-output file. */
    char         config_file_name[70];          /**< Name of the config file (fixed, not user-configurable). */
    unsigned int seed;                          /**< Seed value for the random number generator. */
} SimConfig;
```

---

### Parking
Diese Struct repräsentiert das Parkhaus, `total_capacity` und `decks` können zwar der Config Struct entnommen werden allerdings können sie so zum Beispiel bei dem Itterieren durch das Struct verwendet werden, ohne zusätlich auf die Config zugreifen zu müssen.<br>
`occupied_count` wird bei allen Ein-/ und Ausfahrten aktuell gehalten und somit muss bei dem prüfen auf freie Parkplätze nicht durch das gesamte Parkhaus itteriert werden.

`*ptr_decks` ist ein Pointer auf ein Array meherer ParkingDeck Structs. Das Array hat so viele Elemente, wie das Pakhaus Etagen haben soll.

`**ptr_occupied_spots` ist ein Array von Zeigern auf alle aktuell belegten Parkplätze. Ermöglicht das effiziente Iterieren über belegte Spots bei der Ausfahrtsprüfung, ohne das gesamte Parkhaus zu durchsuchen.
```c
typedef struct {
    unsigned int    total_capacity;         /**< Total number of parking spots across all decks. */
    unsigned int    decks;                  /**< Total number of parking decks in the parking. */
    unsigned int    occupied_count;         /**< Number of spots currently occupied. */
    ParkingSpot     **ptr_occupied_spots;   /**< Array of pointers to all currently occupied spots. */
    ParkingDeck     *ptr_decks;             /**< Pointer to the array of decks in the garage. */
} Parking;
```

---

### ParkingDeck
Dieses Struct stellt eine Etage in dem Parkhaus dar. `deck_id` vergibt jedem Deck eine einzigartige ID, anhand der auch die IDs für die Spots vergeben werden. `capacity`und `occupied_count` dienen genauso wie `total_capacity` und `decks` in dem Parking Struct der einfacheren Behandlung in Funktionen.

`*ptr_spots`ist ein Pointer auf ein Array mit mehrerern ParkingSpot Structs. Das Array hat so viele Elemente, wie die Etage Parkplätze hat.

`free_spots` speichert die Anzahl aktuell freier Plätze pro Etage und wird bei jeder Ein-/Ausfahrt aktualisiert.

`**ptr_stack` ist ein Stack (Array von Zeigern auf freie ParkingSpots), über den der nächste freie Platz in O(1) gefunden werden kann, ohne die Etage iterieren zu müssen.
```c
typedef struct {
    unsigned int    deck_id;         /**< Unique identifier of this deck. */
    unsigned int    capacity;        /**< Total number of parking spots on this deck. */
    unsigned int    occupied_count;  /**< Number of spots currently occupied. */
    ParkingSpot     *ptr_spots;      /**< Pointer to the array of parking spots on this deck. */
    unsigned int    free_spots;      /**< Number of free spots on this deck. */
    ParkingSpot     **ptr_stack;     /**< Stack of pointers to free ParkingSpots for O(1) allocation. */
} ParkingDeck;
```

---

### ParkingSpot
Dieses Struct repräsentiert einen einzelnen Parkplatz `id`ist eine einzigartige ID, die dabei hilft, den Parkplatz in Itterationen in For-Schleifen durch mehrere Etagen und Parkplätze anschaulich zu erkennen z.B. in dem prefill in der init_parking() Funktion.

`occupied`ist eine Flag, die anzeigt ob der Parkplatz belegt ist, dadurch muss nicht der Pointer überprüft werden. Da diese Flag nur 0 oder 1 annimmt wird ein char verwendet, ein Integer wäre unnötiger Speicherverbrauch.

`*ptr_vehicle` ist ein Pointer auf das Fahrzeug, das in diesem Parkplatz geparkkt ist, ist der Parkplatz leer, so ist der Pointer NULL.
```c
typedef struct {
    int         id;           /**< Unique identifier of the parking spot. */
    char        occupied;     /**< Flag indicating whether the spot is occupied (1) or free (0). */
    Vehicle     *ptr_vehicle; /**< Pointer to the vehicle currently occupying the spot, or NULL if free. */
} ParkingSpot;
```

---

### Vehicle
Diese Struct stellt ein einzelnes Fahrzeug dar. Jedes Fahrzeug erhält eine fortlaufende ID, damit es einzigarteig zugeordnet werden kann.

`entry_time` enthält die Nummer des Steps, in dem das Fahrzeug das Parkhaus befahren hat. Zusammen mit `parking_duration` lässt sich feststellen, wann das Fahrzeug das Parkhaus wieder verlassen muss.

`queue_time` speichert den Simulationsschritt, in dem das Fahrzeug in die Warteschlange eingereiht wurde. Verlässt das Fahrzeug die Warteschlange, wird die tatsächliche Wartezeit als Differenz zwischen dem aktuellen Schritt und dem gespeicherten Einreihungsschritt berechnet.
```c
typedef struct {
    unsigned int id;               /**< Unique identifier of the vehicle. */
    unsigned int entry_time;       /**< Simulation step at which the vehicle entered the parking garage. */
    unsigned int parking_duration; /**< Total number of simulation steps the vehicle stays parked. */
    unsigned int queue_time;       /**< Simulation step at which the vehicle entered the queue. */
} Vehicle;
```

---

### QueueNode
Dieses Struct ist ein Element (Knoten) in der FiFo Double Linked-List Queue, jeder Knoten enhält einen Pointer `*ptr_previous` auf den Knoten vor ihm (ist bei dem ersten Element in der Queue NULL) und ein Pointer `*ptr_next` auf den nachfolgenden Knoten (ist bei dem letzten Element in der Queue NULL), was das Durchitterieren vereinfacht.

Der Pointer `*ptr_vehicle` zeigt auf das Fahrzeug, das an dieser Stelle der Schlange steht / in diesem Knoten vorhanden ist.
```c
typedef struct QueueNode {
    Vehicle             *ptr_vehicle;  /**< Pointer to the vehicle held by this node. */
    struct QueueNode    *ptr_previous; /**< Pointer to the previous node in the queue, or NULL if this is the head. */
    struct QueueNode    *ptr_next;     /**< Pointer to the next node in the queue, or NULL if this is the tail. */
} QueueNode;
```

---

### Queue
Dieses Struct ist eine FiFo Double Linked-List.

Der Pointer `*ptr_head` zeit auf den ersten Knoten in der Schlange und ermöglicht das erste Fahrzeug zu entnehmen und in das Parkhaus zu setzen, der Pointer `*ptr_tail` zeigt auf den letzten Knoten der Schlange und ermöglicht ohne Durchitterieren ein neuen Knoten hinter dem aktuell letzten anzufügen.

Der Parameter `size` kann für das Erheben der Statistik verwendet werden, ohne dass die Knoten der Liste durchgezählt werden müssen.
```c
typedef struct {
    QueueNode *ptr_head; /**< Pointer to the first node in the queue, or NULL if empty. */
    QueueNode *ptr_tail; /**< Pointer to the last node in the queue, or NULL if empty. */
    int        size;     /**< Current number of nodes (vehicles) in the queue. */
} Queue;
```

---

### SimStats
Dieses Struct wird bei dem Ausführen der Simulation einmalig erstellt und an alle Funktionen, die Statistiken erheben übergeben.

Die Parameter `step_num` und `id_count` werden verwendet um die Nummer des aktuellen Steps zu sichern und die ID, die an die Autos fortlaufend vergeben werden zu tracken.

Die Parameter per step `temp_exits`, `temp_entries`, `temp_rel_occupancy_percent`, `temp_queue_length`, `temp_free_spots` und `temp_time_left` werden im Lauf von einem Simulationsschritt beschrieben und am Ende eines Schrittes in dem output File gespeichert, soweit notwendig auf die Cumulative stats angewendet und danach zurückgesetzt.

Die Cumulative stats `total_exits`, `total_entries`, `total_queued`, `total_queue_time`, `total_parking_time`, `time_full_occupancy` und `avg_rel_occupancy` werden ebenfalls während der Laufzeit bei den entsprechenden Aktionen befüllt. Sie werden am Ende der Simulation in die final stats übernommen oder verwendet um diese zu errechnen.

Die Tracked extremes `peak_queue_length`, `step_longest_queue`, `peak_rel_occupancy` und `step_highest_occupancy` werden in jedem Schritt mit dem aktuellen Wert verglichen und, sollte der Aktuelle größer sein, wird der peak Wert zu dem aktuellen Wert angepasst und der entsprechende Step wird auf den aktuellen gestezt.

Für alle Ganzzahlen, die keine negativen Werte annehmen können werden unsigned Interger verwendet, um den positiven Zahlenraum zu vergrößern. Dort wo genauere Werte benötigt werden, werden floats verwendet.
```c
typedef struct {
    unsigned int step_num;                      /**< Current simulation step number. */
    unsigned int id_count;                      /**< Counter for the current Car ID. */

    /* --- Per-step stats (overwritten each step) --- */
    unsigned int temp_exits;                    /**< Cars that exited this step. */
    unsigned int temp_entries;                  /**< New arrivals this step. */
    float        temp_rel_occupancy_percent;    /**< Relative occupancy this step (0.0–100.0). */
    unsigned int temp_queue_length;             /**< Cars in queue at end of this step. */
    unsigned int temp_free_spots;               /**< Free spots after this step. */
    unsigned int temp_time_left;                /**< Average time left for cars in the car park. */

    /* --- Cumulative stats (accumulated until end) --- */
    unsigned int total_exits;                   /**< Total cars exited over all steps. */
    unsigned int total_entries;                 /**< Total cars arrived over all steps. */
    unsigned int total_queued;                  /**< Total cars that had to wait in queue. */
    uint64_t     total_queue_time;              /**< Sum of all queue waiting times (in steps). */
    uint64_t     total_parking_time;            /**< Sum of all parking durations (in steps). */
    unsigned int time_full_occupancy;           /**< Steps where parking was at full capacity. */
    float        avg_rel_occupancy;             /**< Average relative occupancy over all steps. */

    /* --- Tracked extremes for final report --- */
    unsigned int peak_queue_length;             /**< Peak queue length observed. */
    unsigned int step_longest_queue;            /**< Step at which peak queue length occurred. */
    float        peak_rel_occupancy;            /**< Peak relative occupancy observed (0.0–100.0). */
    unsigned int step_highest_occupancy;        /**< Step at which peak occupancy occurred. */
} SimStats;
```
