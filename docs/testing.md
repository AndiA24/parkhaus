[← README](../README.md)

# Unit Test Übersicht

Das Projekt verwendet **CMake** als Build-System und **CTest** zum Ausführen der Tests.
Für jede testbare Funktion wurde eine eigene Test-Datei unter `test/` angelegt, in der sich immer mindestens 2 für die Funktion sinnvolle Unit-Tests befeinden. 

---

## Tests ausführen

### 1. Projekt bauen

```bash
cmake -B build
cmake --build build
```

### 2. Alle Tests ausführen

```bash
ctest --test-dir build
```

> **Hinweis:** Die für die Funktionen nötigen `.c-Files` der benötigten Funktionen werden sofern nötig automatisch über die `CMakeList` eingebunden, um auf die daraus benötigten Structs unf Funktionen zugreiben zu können

### 3. Einzelnen Test ausführen

```bash
ctest -R <test_name>
```

Verfügbare Test-Targets:

| Target | Funktion |
|---|---|
| `test_init_parking` | `init_parking()` |
| `test_init_occ` | `initial_occupancy()` |
| `test_free_parking` | `free_parking()` |
| `test_entry_parking` | `entry_parking()` |
| `test_check_exits` | `check_exit()` |
| `test_get_free_spots` | `get_free_spots()` |
| `test_create_vehicle` | `create_vehicle()` |
| `test_free_vehicle` | `free_vehicle()` |
| `test_init_stats` | `init_simstats()` |
| `test_free_stats` | `free_stats()` |
| `test_reset_all_stats` | `reset_all_stats()` |
| `test_reset_temp_stats` | `reset_temp_stats()` |
| `test_update_stats` | `update_simstats()` |
| `test_update_peak` | `update_peak()` |
| `test_create_output_file` | `create_output_file()` |
| `test_close_output_file` | `close_output_file()` |
| `test_save_temp_dataset` | `save_temp_dataset()` |
| `test_save_final_dataset` | `save_final_dataset()` |
| `test_config_create_config` | `create_config()` |
| `test_config_free_config` | `free_config()` |
| `test_config_populate_with_defaults` | `populate_with_default()` |
| `test_config_get_config` | `get_config()` |
| `test_config_save_config` | `save_config()` |
| `test_rand_arrival` | `rand_arrival()` |
| ~~`test_run_simulation`~~ | ~~`run_simulation()`~~ *(in CMakeLists.txt deaktiviert)* |

### 4. Build bereinigen

```bash
rm -rf build
```

---

## Parking

### `test_parking_init_parking.c`
Testet `init_parking()`.
- Test 1: Beide Argumente NULL – `init_parking(NULL, NULL)` gibt NULL zurück
- Test 2: Stats-Argument ist NULL – `init_parking(ptr_config, NULL)` gibt NULL zurück
- Test 3: Config-Argument ist NULL – `init_parking(NULL, ptr_stats)` gibt NULL zurück
- Test 4: Gültige Config ohne Startbelegung – prüft `total_capacity`, `deck_count`, Stellplatz-IDs und `occupied`-Flags
- Test 5: Gültige Config mit Startbelegung – prüft, dass genau `initial_occupancy` Fahrzeuge platziert werden

---

### `test_parking_init_occ.c`
Testet `initial_occupancy()`.
- Test 1: Alle Argumente NULL – `initial_occupancy(NULL, NULL, NULL)` gibt -1 zurück
- Test 2: Parking-Zeiger ist NULL – gibt -1 zurück
- Test 3: Stats-Zeiger ist NULL – gibt -1 zurück
- Test 4: Config-Zeiger ist NULL – gibt -1 zurück
- Test 5: Startbelegung größer als freie Plätze – `initial_occupancy > total_capacity` gibt -2 zurück
- Test 6: Alle Eingaben korrekt – prüft, dass genau die angeforderte Anzahl an Fahrzeugen platziert wird

---

### `test_parking_free_parking.c`
Testet `free_parking()`.
- Test 1: ptr_parking ist NULL – gibt -1 zurück
- Test 2: Gültiger Zeiger wird erfolgreich freigegeben – gibt 0 zurück

---

### `test_parking_entry_parking.c`
Testet `entry_parking()`.
- Test 1: NULL-Schutz – alle NULL-Kombinationen der drei Zeigerargumente geben -1 zurück
- Test 2: Korrekte Einfahrt – prüft `occupied_count`, Stellplatzzuweisung, Stats (`temp_entries`, `total_entries`) und `vehicle->entry_time`

---

### `test_parking_check_exits.c`
Testet `check_exit()`.
- Test 1: NULL-Schutz – alle NULL-Kombinationen der zwei Zeigerargumente geben -1 zurück
- Test 2: Fahrzeug verlässt das Parkhaus – Fahrzeug fährt aus, wenn `step_num - entry_time >= parking_duration`; prüft Stellplatzfreigabe, Zähler und Stats (`temp_exits`, `total_exits`, `total_parking_time`)
- Test 3: Mehrere Fahrzeuge, nur eines fährt aus – von zwei Fahrzeugen verlässt nur das mit abgelaufener Zeit das Parkhaus

---

### `test_parking_get_free_spots.c`
Testet `get_free_spots()`.
- Test 1: NULL-Schutz – alle NULL-Kombinationen der zwei Zeigerargumente geben -1 zurück
- Test 2: Korrekte Berechnung freier Plätze – prüft `temp_free_spots = total_capacity - occupied_count`

---

## Vehicle

### `test_vehicle_create_vehicle.c`
Testet `create_vehicle()`.
- Test 1: NULL-Schutz – `create_vehicle(NULL, config)` und `create_vehicle(stats, NULL)` geben NULL zurück
- Test 2: Gültiges Fahrzeug wird erstellt – prüft `parking_duration` im Bereich `[min, max]`, `entry_time == 0`, `queue_time == 0`, `id == stats->id_count`
- Test 3: id_count wird inkrementiert – `stats->id_count` wird nach jedem Aufruf um 1 erhöht

---

### `test_vehicle_free_vehicle.c`
Testet `free_vehicle()`.
- Test 1: ptr_vehicle ist NULL – gibt -1 zurück
- Test 2: Gültiger Zeiger wird erfolgreich freigegeben – gibt 0 zurück

---

## Stats

### `test_stats_init_stats.c`
Testet `init_simstats()`.
- Test 1: Rückgabewert ist nicht NULL – zurückgegebener Zeiger ist gültig
- Test 2: Alle Felder nach Init gleich null – alle 19 Felder (int und float) werden mit 0 / 0.0f initialisiert
- Test 3: Zwei Aufrufe geben verschiedene Zeiger zurück – zwei aufeinanderfolgende Aufrufe liefern unabhängige Zeiger

---

### `test_stats_free_stats.c`
Testet `free_stats()`.
- Test 1: ptr_stats ist NULL – gibt -1 zurück
- Test 2: Gültiger Zeiger wird erfolgreich freigegeben – gibt 0 zurück

---

### `test_stats_reset_all_stats.c`
Testet `reset_all_stats()`.
- Test 1: ptr_stats ist NULL – gibt -1 zurück
- Test 2: Alle Felder werden auf 0 zurückgesetzt – alle 19 Felder (temporär und kumulativ) werden explizit auf 0 / 0.0f gesetzt

---

### `test_stats_reset_temp_stats.c`
Testet `reset_temp_stats()`.
- Test 1: ptr_stats ist NULL – gibt -1 zurück
- Test 2: Alle temporären Felder werden auf 0 zurückgesetzt – `temp_entries`, `temp_exits`, `temp_free_spots`, `temp_queue_length`, `temp_rel_occupancy_percent`, `temp_time_left` werden auf 0 gesetzt
- Test 3: Nicht-temporäre Felder werden nicht verändert – `step_num`, `total_entries`, `avg_rel_occupancy`, `peak_queue_length` behalten ihre Werte

---

### `test_stats_update_stats.c`
Testet `update_simstats()`.
- Test 1: ptr_stats ist NULL – gibt -1 zurück
- Test 2: ptr_parking ist NULL – gibt -1 zurück
- Test 3: ptr_queue ist NULL – gibt -1 zurück
- Test 4: Alle berechneten Felder mit gültigen Structs – prüft `temp_rel_occupancy_percent`, `temp_queue_length`, `temp_free_spots`, `avg_rel_occupancy`; ein zweiter Aufruf bei voller Belegung prüft die Inkrementierung von `time_full_occupancy`

---

### `test_stats_update_peak.c`
Testet `update_peak()`.
- Test 1: ptr_stats ist NULL – gibt -1 zurück
- Test 2: Temp-Werte überschreiten Peak – `peak_rel_occupancy`, `step_highest_occupancy`, `peak_queue_length`, `step_longest_queue` werden aktualisiert
- Test 3: Temp-Werte gleich Peak (kein Update) – Peak-Felder werden nicht überschrieben, wenn Werte gleich sind

---

### `test_stats_create_output_file.c`
Testet `create_output_file()`.
- Test 1: NULL-Schutz – `create_output_file(NULL)` gibt NULL zurück
- Test 2: Gültige Config erstellt Datei – Datei wird auf dem Datenträger angelegt und ein gültiger `FILE*` wird zurückgegeben

---

### `test_stats_close_output_file.c`
Testet `close_output_file()`.
- Test 1: NULL-Schutz – `close_output_file(NULL, NULL)` gibt -1 zurück
- Test 2: Offene Ausgabedatei wird geschlossen – eine offene Datei (via `tmpfile()`) wird erfolgreich geschlossen, gibt 0 zurück

---

### `test_stats_save_temp_dataset.c`
Testet `save_temp_dataset()`.
- Test 1: NULL-Schutz – alle NULL-Kombinationen der zwei Zeigerargumente geben -1 zurück
- Test 2: Gültige Argumente – prüft Rückgabewert 1 und dass eine CSV-Zeile in die Datei geschrieben wird

---

### `test_stats_save_final_dataset.c`
Testet `save_final_dataset()`.
- Test 1: NULL-Schutz – alle NULL-Kombinationen der zwei Zeigerargumente geben -1 zurück
- Test 2: Gültiger Aufruf schreibt in Datei – prüft, dass eine Kopfzeile gefolgt von einer Datenzeile geschrieben wird

---

## Config

### `test_config_create_config.c`
Testet `create_config()`.
- Test 1: Rückgabewert ist nicht NULL – zurückgegebener Zeiger ist gültig
- Test 2: config_file_name gesetzt, numerische Felder null-initialisiert – `config_file_name == "parkhaus_config.csv"`, alle numerischen Felder sind 0

---

### `test_config_free_config.c`
Testet `free_config()`.
- Test 1: Gültiger Zeiger gibt 0 zurück – gibt 0 zurück
- Test 2: NULL-Zeiger gibt -1 zurück – gibt -1 zurück

---

### `test_config_populate_with_defaults.c`
Testet `populate_with_default()`.
- Test 1: Alle Felder werden auf erwartete Standardwerte gesetzt – prüft alle 10 Felder (num_decks=5, spots_per_deck=60, initial_occupancy=150, max_duration=200, min_duration=10, sim_duration=1000, arrival_prob=70, output_file="parkhaus_results", config_file="parkhaus_config.csv", seed=69), gibt 0 zurück
- Test 2: NULL-Zeiger gibt -1 zurück – gibt -1 zurück

---

### `test_config_get_config.c`
Testet `get_config()`.
- Test 1: Fehlende Config-Datei lädt Standardwerte und gibt 0 zurück – nicht vorhandene Datei führt zum Laden der Standardwerte
- Test 2: Gültige Config-Datei wird korrekt eingelesen und gibt 1 zurück – alle 9 Felder werden korrekt aus der CSV gelesen
- Test 3: Fehlerhafte Config-Datei lädt Standardwerte und gibt 0 zurück – ungültige CSV führt zum Laden der Standardwerte

---

### `test_config_save_config.c`
Testet `save_config()`.
- Test 1: Gespeicherte Config wird korrekt zurückgelesen – gespeicherte Werte können per `get_config()` korrekt zurückgelesen werden, gibt 1 zurück
- Test 2: save_config überschreibt bestehende Datei – bestehende Datei wird mit neuen Werten überschrieben, gibt 0 zurück

---

## Simulation

### `test_simulation_rand_arrival.c`
Testet `rand_arrival()`.
- Test 1: ptr_config ist NULL – gibt 0 zurück
- Test 2: arrival_probability_percent = 0, kommt nie an – 100 Aufrufe geben immer 0 zurück
- Test 3: arrival_probability_percent = 100, kommt immer an – 100 Aufrufe geben immer 1 zurück
- Test 4: Bekannter Seed – prüft deterministisches Verhalten über 100 Iterationen mit festem Seed (546373) und 10% Wahrscheinlichkeit anhand vorberechneter Erwartungswerte

---

### `test_simulation_run_simulation.c` *(derzeit deaktiviert)*
Testet `run_simulation()`. Der entsprechende CMake-Eintrag ist in `CMakeLists.txt` auskommentiert und wird von `ctest` nicht ausgeführt.
- Test 1: NULL-Schutz – alle NULL-Kombinationen der zwei Zeigerargumente geben -1 zurück
- Test 2: Minimaler Durchlauf – `sim_duration_steps=0`, `arrival_probability_percent=0`; prüft Rückgabewert 1, Existenz der Ausgabedatei und `step_num == 0`