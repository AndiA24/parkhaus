# Parking-simulation in C
Team-Repository für den Programmentwurf "Parkhaus" zur Vorlesung Programmieren I an der DHBW Friedrichshafen

## Requirements / Planung

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
        - Ausfahrten 
        - Einfahrten
        - Durchschnittliche Belegung
        - Länge der Schlange
        - Freie Parkplätze
        - Durchschnittliche verbleibende Parkdauer
    - End: 
		- Summe der Ausfahrten
        - Summe der Einfahrten
        - Durchschnittliche Wartezeit
        - Gesamt Parkduer aller Autos
        - Durchschnittliche Parkdauer
        - Anzahl der Schritte mit voller Belegung
        - Durchschnittliche relative Belegung
        - Zeit der längsten Schlange + maximale Länge
        - Zeit der höchsten Belegung + höchste Belegung

# Docu / Reasoning according to Task f)

## Projekt Architektur

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
├── config/
│   └── config.txt      # Gespeicherte Simulationskonfiguration
└── output/
    └── *.csv           # Generierte Statistik-Ausgabedateien
```

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

## Output / Stats

### Per-Step Stats

Werden nach jedem Simulationsschritt ausgegeben und in die CSV-Datei geschrieben.

Bei eingen Parametern werden unsigned Integer verwendet, da sie keinen negativen Wert annehmen können dadurch höhere Werte in positiver Richtung, trotz gleichem Speicherverbrauch annehmen können. <br>
Dort, wo genauere Werte benötigt werden, wie zum Beispiel bei der relativen Belegung werden Floats verwendet, um Kommazahlen darstellen zu können.

| Feld | Typ | Beschreibung | Begründung Stat |
|---|---|---|---|
| `temp_exits` | `unsigned int` | Ausgefahrene Autos in diesem Schritt | Zeigt die Ausfahren aus dem Parkhaus und ermöglicht zusammen mit Ankünften die Analyse der Zu-/ Abnahme der Autos im Parkhaus im jewailigen Schritt |
| `temp_entrys` | `unsigned int` | Neu angekommene Autos in diesem Schritt | Zeigt die Einfahrten in das Parkhaus in dem jewailigen Schritt |
| `temp_rel_occupancy_percent` | `float` | Relative Belegung in % (0.0–100.0) | Zeigt wie ausgelastet das Parkhaus gerade ist |
| `temp_queue_length` | `unsigned int` | Warteschlangenlänge am Ende des Schritts | Indikator für Überlast, eine wachsende Schlange signalisiert, dass das Parkhaus zu klein ist |
| `temp_free_spots` | `unsigned int` | Freie Stellplätze nach diesem Schritt | Gibt die  Kapazitätsreserve an |
| `temp_time_left` | `unsigned int` | Durchschnittliche Restparkzeit der Autos im Parkhaus | Gibt an, wann mit den nächsten größeren Mengen an Ausfahrten zu rechen ist |

### Final Stats

Werden einmalig am Ende der Simulation ausgegeben und an die CSV-Datei angehängt.

Bei eingen Parametern werden unsigned Integer verwendet, da sie keinen negativen Wert annehmen können dadurch höhere Werte in positiver Richtung, trotz gleichem Speicherverbrauch annehmen können. <br>
Dort, wo genauere Werte benötigt werden, wie zum Beispiel bei der relativen Belegung werden Floats verwendet, um Kommazahlen darstellen zu können.

Die stats total_queued und total_queue_time werden nicht ausgegeben sondern aus ihnen wird die durchschnittliche Zeit in der Schlange berechnet und ausgegeben.

| Feld | Typ | Beschreibung | Begründung Stat |
|---|---|---|---|
| `total_exits` | `unsigned int` | Gesamt ausgefahrene Autos | Gibt die Summe der Ausfahrten aus dem Parkhaus während der Simulation an |
| `total_entrys` | `unsigned int` | Gesamt angekommene Autos | Gibt die Summe aller während der Simulation in das Parkhaus gefahrenen Autos an |
| `total_queued` | `unsigned int` | Autos, die mindestens einmal warten mussten | Basis zur Berechnung der durchschnittlichen Wartezeit (`total_queue_time / total_queued`) |
| `total_queue_time` | `unsigned int` | Summe aller Wartezeiten in Schritten | Basis zur Berechnung der durchschnittlichen Wartezeit (`total_queue_time / total_queued`) |
| `total_parking_time` | `unsigned int` | Summe aller Parkdauern in Schritten | Basis zur Berechnung der durchschnittlichen Parkdauer (`total_parking_time / total_exits`) oder zur Berechnung des Umsatzes |
| `time_full_occupancy` | `unsigned int` | Schritte mit 100 % Belegung | Zeigt wie oft das Parkhaus an seine Kapazitätsgrenze gestoßen ist, das ist Grundlage für eine Auslastungsanalyse |
| `avg_rel_occupancy` | `float` | Durchschnittliche relative Belegung über alle Schritte (0.0–100.0) | Durchschnitt der Auslastung über die gesamte Simulationsdauer |
| `peak_queue_length` | `unsigned int` | Maximale Warteschlangenlänge | Zeigt, die maximale Länge der Schlange, aussagekräftig für die Anzahl der Zufahrten|
| `step_longest_queue` | `unsigned int` | Schritt, in dem die längste Warteschlange auftrat | Ordnet das Maximum der Schlane zeitlich ein |
| `peak_rel_occupancy` | `float` | Maximale relative Belegung (0.0–100.0) | Zeigt die maximale Auslastung, aussagekräftig für die Anzahl der Parkplätze |
| `step_highest_occupancy` | `unsigned int` | Schritt, in dem die höchste Belegung auftrat | Ordnet das Maximum der Auslastung zeitlich ein |

## Datastructure / Structs

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
    unsigned int seed;                          /**< Seed value for the random number generator. */
} SimConfig;
```

### Parking
Diese Struct repräsentiert das Parkhaus, `total_capacity` und `decks` können zwar der Config Struct entnommen werden allerdings können sie so zum Beispiel bei dem Itterieren durch das Struct verwendet werden, ohne zusätlich auf die Config zugreifen zu müssen.<br>
`occupied_count` wird bei allen Ein-/ und Ausfahrten aktuell gehalten und somit muss bei dem prüfen auf freie Parkplätze nicht durch das gesamte Parkhaus itteriert werden.

`*ptr_decks` ist ein Pointer auf ein Array meherer ParkingDeck Structs. Das Array hat so viele Elemente, wie das Pakhaus Etagen haben soll.
```c
typedef struct {
    unsigned int    total_capacity;  /**< Total number of parking spots across all decks. */
    unsigned int    decks;           /**< Total number of parking decks in the parking. */
    unsigned int    occupied_count;  /**< Number of spots currently occupied. */
    ParkingDeck     *ptr_decks;      /**< Pointer to the array of decks in the garage. */
} Parking;
```

### ParkingDeck
Dieses Struct stellt eine Etage in dem Parkhaus dar. `deck_id` vergibt jedem Deck eine einzigartige ID, anhand der auch die IDs für die Spots vergeben werden. `capacity`und `occupied_count` dienen genauso wie `total_capacity` und `decks` in dem Parking Struct der einfacheren Behandlung in Funktionen.

`*ptr_spots`ist ein Pointer auf ein Array mit mehrerern ParkingSpot Structs. Das Array hat so viele Elemente, wie die Etage Parkplätze hat.
```c
typedef struct {
    unsigned int    deck_id;         /**< Unique identifier of this deck. */
    unsigned int    capacity;        /**< Total number of parking spots on this deck. */
    unsigned int    occupied_count;  /**< Number of spots currently occupied. */
    ParkingSpot     *ptr_spots;      /**< Pointer to the array of parking spots on this deck. */
} ParkingDeck;
```

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

### Vehicle
Diese Struct stellt ein einzelnes Fahrzeug dar. Jedes Fahrzeug erhält eine fortlaufende ID, damit es einzigarteig zugeordnet werden kann.

`entry_time` enthält die Nummer des Steps, in dem das Fahrzeug das Parkhaus befahren hat. Zusammen mit `parking_duration` lässt sich feststellen, wann das Fahrzeug das Parkhaus wieder verlassen muss.

`queue_time` ist die Anzahl der Schritte, die das Fahrzeug in der Warteschlange verbracht hat, sie wird bei jedem Schritt in der Warteschlange inkrementiert und bei dem verlassen der Schlage in die Stats übernommen.
```c
typedef struct {
    unsigned int id;               /**< Unique identifier of the vehicle. */
    unsigned int entry_time;       /**< Simulation step at which the vehicle entered the parking garage. */
    unsigned int parking_duration; /**< Total number of simulation steps the vehicle stays parked. */
    unsigned int queue_time;       /**< Number of simulation steps the vehicle spent waiting in the queue. */
} Vehicle;
```

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

### SimStats
Dieses Struct wird bei dem Ausführen der Simulation einmalig erstellt und an alle Funktionen, die Statistiken erheben übergeben. 

Die Parameter `step_num` und `id_count` werden verwendet um die Nummer des aktuellen Steps zu sichern und die ID, die an die Autos fortlaufend vergeben werden zu tracken.

Die Parameter per step `temp_exits`, `temp_entrys`, `temp_rel_occupancy_percent`, `temp_queue_length`, `temp_free_spots` und `temp_time_left` werden im Lauf von einem Simulationsschritt beschrieben und am Ende eines Schrittes in dem output File gespeichert, soweit notwendig auf die Cumulative stats angewendet und danach zurückgesetzt.

Die Cumulative stats `total_exits`, `total_entrys`, `total_queued`, `total_queue_time`, `total_parking_time`, `time_full_occupancy` und `avg_rel_occupancy` werden ebenfalls während der Laufzeit bei den entsprechenden Aktionen befüllt. Sie werden am Ende der Simulation in die final stats übernommen oder verwendet um diese zu errechnen.

Die Tracked extremes `peak_queue_length`, `step_longest_queue`, `peak_rel_occupancy` und `step_highest_occupancy` werden in jedem Schritt mit dem aktuellen Wert verglichen und, sollte der Aktuelle größer sein, wird der peak Wert zu dem aktuellen Wert angepasst und der entsprechende Step wird auf den aktuellen gestezt.

Für alle Ganzzahlen, die keine negativen Werte annehmen können werden unsigned Interger verwendet, um den positiven Zahlenraum zu vergrößern. Dort wo genauere Werte benötigt werden, werden floats verwendet.
```c
typedef struct {
    unsigned int step_num;                      /**< Current simulation step number. */
    unsigned int id_count;                      /**< Counter for the current Car ID. */

    /* --- Per-step stats (overwritten each step) --- */
    unsigned int temp_exits;                    /**< Cars that exited this step. */
    unsigned int temp_entrys;                   /**< New arrivals this step. */
    float        temp_rel_occupancy_percent;    /**< Relative occupancy this step (0.0–100.0). */
    unsigned int temp_queue_length;             /**< Cars in queue at end of this step. */
    unsigned int temp_free_spots;               /**< Free spots after this step. */
    unsigned int temp_time_left;                /**< Average time left for cars in the car park. */

    /* --- Cumulative stats (accumulated until end) --- */
    unsigned int total_exits;                   /**< Total cars exited over all steps. */
    unsigned int total_entrys;                  /**< Total cars arrived over all steps. */
    unsigned int total_queued;                  /**< Total cars that had to wait in queue. */
    unsigned int total_queue_time;              /**< Sum of all queue waiting times (in steps). */
    unsigned int total_parking_time;            /**< Sum of all parking durations (in steps). */
    unsigned int time_full_occupancy;           /**< Steps where parking was at full capacity. */
    float        avg_rel_occupancy;             /**< Average relative occupancy over all steps. */

    /* --- Tracked extremes for final report --- */
    unsigned int peak_queue_length;             /**< Peak queue length observed. */
    unsigned int step_longest_queue;            /**< Step at which peak queue length occurred. */
    float        peak_rel_occupancy;            /**< Peak relative occupancy observed (0.0–100.0). */
    unsigned int step_highest_occupancy;        /**< Step at which peak occupancy occurred. */
} SimStats;
```

## Functions

### config.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Zentraler Einstiegspunkt für die Konfiguration – ohne diese Funktion müsste die Struct überall im Code manuell allokiert und initialisiert werden | | |
| `create_config()` | Erstellt eine neue `SimConfig` Struct, initialisiert mit Standardwerten. | — | `SimConfig *` (neu allokiert) oder `NULL` bei Fehler |
| ***Begründung:*** | Trennt das Einlesen der Konfiguration vom Rest der Logik, sodass die Simulation unabhängig davon ist, woher die Parameter stammen (Datei oder Standardwerte)| | |
| `get_config(ptr_config)` | Liest Simulationsparameter aus der Konfigurationsdatei in die Struct. Existiert keine Datei, werden Standardwerte verwendet. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Persistiert Nutzeränderungen, damit diese beim nächsten Programmstart nicht erneut eingegeben werden müssen| | |
| `save_config(ptr_config)` | Schreibt alle Felder der Struct in die Konfigurationsdatei und überschreibt eine bestehende Konfiguration. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `create_config`, um den Lebenszyklus der Struct konsistent zu halten| | |
| `free_config(ptr_config)` | Gibt den durch `create_config` allokierten Speicher frei. | `SimConfig *ptr_config` | — |

---

### vehicle.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Zentraler Einstiegspunkt für die Konfiguration – ohne diese Funktion müsste die Struct überall im Code manuell allokiert und initialisiert werden| | |
| `create_vehicle(ptr_stats, ptr_config)` | Erstellt eine neue `Vehicle` Struct mit eindeutiger ID und zufälliger Parkdauer innerhalb der konfigurierten Grenzen. | `SimStats *ptr_stats` (für ID-Vergabe), `SimConfig *ptr_config` (für Parkdauergrenzen) | `Vehicle *` (neu allokiert) |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `create_vehicle`, um den Lebenszyklus der Struct konsistent zu halten| | |
| `free_vehicle(ptr_vehicle)` | Gibt den Speicher einer `Vehicle` Struct nach der Ausfahrt frei. | `Vehicle *ptr_vehicle` | — |

---

### parking.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Kapselt den gesamten Aufbau der Parkhausstruktur, damit die Simulation mit einem einzigen Aufruf einen vollständig initialisierten Zustand erhält| | |
| `init_parking(ptr_config, ptr_stats)` | Erstellt die vollständige Parkhausstruktur mit allen Etagen und Stellplätzen und befüllt sie mit der konfigurierten Anzahl an Initialfahrzeugen. | `SimConfig *ptr_config`, `SimStats *ptr_stats` | `Parking *` (neu allokiert) |
| ***Begründung:*** | Trennt die Einparklogik vom restlichen Simulationsablauf, sodass Belegung und Statistiken zentral an einer Stelle aktualisiert werden| | |
| `entry_parking(ptr_parking, ptr_vehicle, ptr_simstats)` | Parkt ein Fahrzeug auf dem ersten freien Stellplatz und aktualisiert die Belegungszahl sowie die Simulationsstatistiken. | `Parking *ptr_parking`, `Vehicle *ptr_vehicle`, `SimStats *ptr_simstats` | — |
| ***Begründung:*** | Kapselt die Ausfahrtslogik, damit der Simulationsloop nicht direkt auf die interne Parkhausstruktur zugreifen muss| | |
| `check_exit(ptr_parking, ptr_simstats)` | Prüft alle Stellplätze auf Fahrzeuge, deren Parkdauer abgelaufen ist, entfernt sie und aktualisiert Zähler und Statistiken. | `Parking *ptr_parking`, `SimStats *ptr_simstats` | — |
| ***Begründung:*** | Hilfsfunktion um den aktuellen Belegungszustand nach außen bereitzustellen| | |
| `get_free_spots(ptr_parking)` | Iteriert durch die Parkhausstruktur und zählt alle aktuell freien Stellplätze. | `Parking *ptr_parking` | `int` (Anzahl freier Stellplätze) |
| ***Begründung:*** | Kapselt die vollständige Speicherfreigabe passend zu `init_parking`, um den Lebenszyklus der Struct konsistent zu halten| | |
| `free_parking(ptr_parking)` | Gibt den gesamten durch `init_parking` allokierten Speicher frei. | `Parking *ptr_parking` | — |

---

### queue.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Kapselt die Initialisierung der Warteschlange, damit der Aufrufer nicht direkt mit der internen Struktur (head/tail) arbeiten muss| | |
| `init_queue()` | Initialisiert eine leere Warteschlange (head/tail = NULL, size = 0). | — | `Queue *` (neu allokiert) |
| ***Begründung:*** | Kapselt das Einfügen in die Warteschlange, damit die Zeigerlogik der verketteten Liste nicht im Simulationsloop auftaucht| | |
| `enqueue(ptr_queue, ptr_vehicle)` | Hängt ein Fahrzeug an das Ende der Warteschlange. Inkrementiert `size` um 1. | `Queue *ptr_queue`, `Vehicle *ptr_vehicle` | — |
| ***Begründung:*** | Kapselt das Entfernen aus der Warteschlange und nutzt den Moment des Ausreihens, um die Wartezeit des Fahrzeugs zentral in die Statistik zu übertragen| | |
| `dequeue(ptr_queue, ptr_stats)` | Entfernt und gibt das Fahrzeug am Anfang der Warteschlange zurück. Dekrementiert `size` um 1. Gibt `NULL` zurück, wenn die Warteschlange leer ist. | `Queue *ptr_queue`, `SimStats *ptr_stats` | `Vehicle *` oder `NULL` |
| ***Begründung:*** | Ermöglicht es, die Wartezeit aller wartenden Fahrzeuge pro Simulationsschritt mit einem einzigen Aufruf zu aktualisieren, anstatt dies im Simulationsloop manuell zu iterieren| | |
| `increment_queue_time(ptr_queue)` | Inkrementiert `queue_time` jedes Fahrzeugs in der Warteschlange um 1. Tut nichts, wenn die Warteschlange leer ist. | `Queue *ptr_queue` | — |
| ***Begründung:*** | Leert die Warteschlange am Simulationsende, ohne die Queue-Struct selbst freizugeben, damit diese bei Bedarf wiederverwendet werden könnte| | |
| `delete_queue(ptr_queue)` | Gibt alle Knoten der Warteschlange frei und setzt sie auf den Initialzustand zurück (size = 0). Die enthaltenen `Vehicle`-Objekte werden nicht freigegeben. | `Queue *ptr_queue` | — |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `init_queue`, um den Lebenszyklus der Struct konsistent zu halten| | |
| `free_queue(ptr_queue)` | Gibt die durch `init_queue` allokierte `Queue` Struct frei. | `Queue *ptr_queue` | — |

---

### stats.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Kapselt Allokierung und Nullinitialisierung der Statistik-Struct, damit ein definierter Ausgangszustand vor der Simulation garantiert ist| | |
| `init_simstats()` | Allokiert und initialisiert eine `SimStats` Struct mit allen Feldern auf null. | — | `SimStats *` (neu allokiert) oder `NULL` bei Fehler |
| ***Begründung:*** | Kapselt die gesamte Dateilogik inklusive Nutzerinteraktion, damit der Simulationsloop ein fertiges Datei-Handle erhält und nicht mit Dateiverwaltung belastet wird| | |
| `create_output_file(ptr_config)` | Öffnet oder erstellt die CSV-Ausgabedatei. Existiert bereits eine Datei mit diesem Namen, wird der Nutzer gefragt, ob er überschreiben oder umbenennen möchte. Schreibt die Simulationskonfiguration als Header. | `SimConfig *ptr_config` | `FILE *` (offenes Datei-Handle) |
| ***Begründung:*** | Zentralisiert die Berechnung aller Schrittkennwerte| | |
| `update_simstats(ptr_simstats, ptr_parking, ptr_queue)` | Sammelt und berechnet alle relevanten Kennwerte für den aktuellen Simulationsschritt und schreibt sie in die `SimStats` Struct. | `SimStats *ptr_simstats`, `Parking *ptr_parking`, `Queue *ptr_queue` | — |
| ***Begründung:*** | Trennt die Höchstwertaktualisierung von der allgemeinen Statistikberechnung, damit diese Logik separat und gezielt nach jedem Schritt aufgerufen werden kann| | |
| `update_peak(ptr_simstats)` | Vergleicht temporäre Werte mit gespeicherten Höchstwerten und aktualisiert diese, falls ein neues Maximum erkannt wird, und speichert die aktuelle Schrittnummer. | `SimStats *ptr_simstats` | — |
| ***Begründung:*** | Kapselt die Ausgabe pro Schritt, damit Datei- und Konsolenausgabe an einer zentralen Stelle erfolgen und nicht über den Simulationsloop verstreut sind| | |
| `save_temp_dataset(ptr_simstats, ptr_output_file)` | Schreibt die Statistiken des aktuellen Schritts in die Ausgabedatei und auf stdout. | `SimStats *ptr_simstats`, `FILE *ptr_output_file` | — |
| ***Begründung:*** | tellt sicher, dass temporäre Felder zu Beginn jedes Schritts sauber zurückgesetzt werden, ohne dass der Aufrufer die interne Feldstruktur kennen muss| | |
| `reset_temp_stats(ptr_simstats)` | Setzt alle per-Step (temporären) Felder der Struct auf null zurück. | `SimStats *ptr_simstats` | — |
| ***Begründung:*** | apselt die abschließende Ausgabe, damit die Zusammenfassung konsistent an einer Stelle geschrieben wird| | |
| `save_final_dataset(ptr_simstats, ptr_output_file)` | Schreibt die abschließende Simulationszusammenfassung in die Ausgabedatei und auf stdout. | `SimStats *ptr_simstats`, `FILE *ptr_output_file` | — |
| ***Begründung:*** | Kapselt das Schließen der Datei passend zu `create_output_file`, um den Lebenszyklus des Datei-Handles konsistent zu halten| | |
| `close_output_file(ptr_output_file)` | Schließt die geöffnete Ausgabedatei. | `FILE *ptr_output_file` | `1` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Ermöglicht einen vollständigen Neustart der Statistik ohne Neuallokierung, etwa für mehrere aufeinanderfolgende Simulationsläufe| | |
| `reset_all_stats(ptr_simstats)` | Setzt alle Felder der Struct auf null zurück. | `SimStats *ptr_simstats` | — |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `init_simstats`, um den Lebenszyklus der Struct konsistent zu halten| | |
| `free_stats(ptr_simstats)` | Gibt den durch `init_simstats` allokierten Speicher frei. | `SimStats *ptr_simstats` | — |

---

### simulation.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Kapselt den gesamten Simulationsablauf, damit main nur einen einzigen Aufruf benötigt| | |
| `run_simulation(ptr_config, ptr_stats)` | Führt die Simulation für die konfigurierte Anzahl an Schritten aus und ruft dabei alle notwendigen Funktionen je Schritt auf. | `SimConfig *ptr_config`, `SimStats *ptr_stats` | `1` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Isoliert die Zufallsentscheidung über Fahrzeugankunft, damit diese Logik nicht direkt im Simulationsloop steht und bei Bedarf leicht angepasst werden kann| | |
| `rand_arrival(ptr_config)` | Entscheidet zufällig, ob ein Fahrzeug im aktuellen Schritt ankommt, basierend auf der konfigurierten Ankunftswahrscheinlichkeit. | `SimConfig *ptr_config` | `1` (Ankunft) oder `0` (keine Ankunft) |

---

### ui.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Bildet den zentralen Einstiegspunkt der Anwendung und steuert den Programmfluss, bevor die Simulation gestartet wird| | |
| `show_welcome(ptr_config)` | Zeigt den Willkommensscreen und verarbeitet Eingaben: `Enter` → Simulation starten, `S` → Einstellungen, `Q` → Beenden. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Kapselt die gesamte Einstellungslogik, damit Konfigurationsänderungen über eine dedizierte Ansicht erfolgen und nicht in den Hauptablauf eingreifen| | |
| `show_settings(ptr_config)` | Zeigt das Einstellungsmenü und erlaubt das Ändern von Parametern über Zifferntasten (1–9). `ESC`/`Enter`/`Q` → zurück zum Willkommensscreen. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Zentralisiert die validierte Nutzereingabe, damit Eingabeprüfung und Fehlerbehandlung nicht für jedes Konfigurationsfeld separat implementiert werden müssen| | |
| `prompt_input(text, ptr_current_value, min, max)` | Fordert den Nutzer zur Eingabe eines neuen Werts für ein Konfigurationsfeld auf. Wiederholt die Abfrage, bis ein gültiger Wert innerhalb `[min, max]` eingegeben wird. | `char text[]` (Feldname), `void *ptr_current_value` (Zielfeld), `long min`, `long max` | — |
| ***Begründung:*** | Trennt die Darstellung der Einstellungen von der Eingabelogik in `show_settings`, damit beide unabhängig voneinander angepasst werden können| | |
| `render_settings(ptr_config)` | Gibt alle Konfigurationsfelder und ihre aktuellen Werte formatiert aus. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Kapselt die Live-Ausgabe pro Schritt, damit der Simulationsloop nicht direkt mit der Darstellungslogik vermischt wird| | |
| `show_running(ptr_stats)` | Zeigt Live-Statistiken je Schritt (Ausfahrten, Einfahrten, relative Belegung, Warteschlangenlänge). | `SimStats *ptr_stats` | — |
| ***Begründung:*** | Kapselt die Ergebnisanzeige am Simulationsende, damit die Ausgabelogik zentral an einer Stelle liegt und unabhängig vom Simulationsloop angepasst werden kann| | |
| `show_results(ptr_stats)` | Zeigt die abschließende Zusammenfassung aller akkumulierten Simulationsstatistiken. | `SimStats *ptr_stats` | — |

---

### utils.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| ***Begründung:*** | Kapselt den sauberen Programmabschluss, damit Konfigurationsspeicherung und Ressourcenfreigabe garantiert an einer zentralen Stelle erfolgen und nicht vom Aufrufer manuell durchgeführt werden müssen| | |
| `quit(ptr_config)` | Beendet die Anwendung sauber durch Speichern der Konfiguration und Freigabe der Ressourcen. | `SimConfig *ptr_config` | — |
