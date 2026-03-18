[← README](../README.md)

# Modulreferenz

## Inhalt
- [config.h](#configh)
- [vehicle.h](#vehicleh)
- [parking.h](#parkingh)
- [queue.h](#queueh)
- [stats.h](#statsh)
- [simulation.h](#simulationh)
- [ui.h](#uih)
- [utils.h](#utilsh)

---

## config.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `create_config()` | Erstellt eine neue `SimConfig` Struct, allokiert Speicher und setzt `config_file_name`; alle numerischen Felder werden auf null initialisiert. | — | `SimConfig *` (neu allokiert) oder `NULL` bei Fehler |
| ***Begründung:*** | Zentraler Einstiegspunkt für die Konfiguration – ohne diese Funktion müsste die Struct überall im Code manuell allokiert und initialisiert werden | | |
| `populate_with_default(ptr_config)` | Befüllt alle Felder der `SimConfig` Struct mit den vordefinierten Standardwerten. | `SimConfig *ptr_config` | `0` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Trennt das Setzen der Standardwerte von der Allokierung, damit Defaults auch unabhängig von `create_config` angewendet werden können (z. B. beim Laden einer ungültigen Konfigurationsdatei) | | |
| `get_config(ptr_config)` | Liest Simulationsparameter aus der Konfigurationsdatei in die Struct. Existiert keine Datei, werden Standardwerte verwendet. | `SimConfig *ptr_config` | `0` Standardwerte geladen, `1` Datei geladen |
| ***Begründung:*** | Trennt das Einlesen der Konfiguration vom Rest der Logik, sodass die Simulation unabhängig davon ist, woher die Parameter stammen (Datei oder Standardwerte) | | |
| `save_config(ptr_config)` | Schreibt alle Felder der Struct in die Konfigurationsdatei und überschreibt eine bestehende Konfiguration. | `SimConfig *ptr_config` | `0` überschrieben, `1` neu erstellt, `-1` bei Fehler |
| ***Begründung:*** | Persistiert Nutzeränderungen, damit diese beim nächsten Programmstart nicht erneut eingegeben werden müssen | | |
| `free_config(ptr_config)` | Gibt den durch `create_config` allokierten Speicher frei. | `SimConfig *ptr_config` | `0` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `create_config`, um den Lebenszyklus der Struct konsistent zu halten | | |

---

## vehicle.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `create_vehicle(ptr_stats, ptr_config)` | Erstellt eine neue `Vehicle` Struct mit eindeutiger ID und zufälliger Parkdauer innerhalb der konfigurierten Grenzen. | `SimStats *ptr_stats` (für ID-Vergabe), `SimConfig *ptr_config` (für Parkdauergrenzen) | `Vehicle *` (neu allokiert) |
| ***Begründung:*** | Zentraler Einstiegspunkt für die Fahrzeugerstellung – ohne diese Funktion müsste die Struct überall im Code manuell allokiert und initialisiert werden | | |
| `free_vehicle(ptr_vehicle)` | Gibt den Speicher einer `Vehicle` Struct nach der Ausfahrt frei. | `Vehicle *ptr_vehicle` | `0` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `create_vehicle`, um den Lebenszyklus der Struct konsistent zu halten | | |

---

## parking.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `init_parking(ptr_config, ptr_stats)` | Erstellt die vollständige Parkhausstruktur mit allen Etagen und Stellplätzen und befüllt sie mit der konfigurierten Anzahl an Initialfahrzeugen. | `SimConfig *ptr_config`, `SimStats *ptr_stats` | `Parking *` (neu allokiert) |
| ***Begründung:*** | Kapselt den gesamten Aufbau der Parkhausstruktur, damit die Simulation mit einem einzigen Aufruf einen vollständig initialisierten Zustand erhält | | |
| `entry_parking(ptr_parking, ptr_vehicle, ptr_simstats)` | Parkt ein Fahrzeug auf dem ersten freien Stellplatz und aktualisiert die Belegungszahl sowie die Simulationsstatistiken. | `Parking *ptr_parking`, `Vehicle *ptr_vehicle`, `SimStats *ptr_simstats` | `1` bei Erfolg, `0` wenn kein freier Platz verfügbar, `-1` bei ungültigem Argument |
| ***Begründung:*** | Trennt die Einparklogik vom restlichen Simulationsablauf, sodass Belegung und Statistiken zentral an einer Stelle aktualisiert werden | | |
| `check_exit(ptr_parking, ptr_simstats)` | Prüft alle belegten Stellplätze auf Fahrzeuge, deren Parkdauer abgelaufen ist, entfernt sie und aktualisiert Zähler und Statistiken. | `Parking *ptr_parking`, `SimStats *ptr_simstats` | `1` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Kapselt die Ausfahrtslogik, damit der Simulationsloop nicht direkt auf die interne Parkhausstruktur zugreifen muss | | |
| `get_free_spots(ptr_parking, ptr_stats)` | Berechnet die Anzahl freier Stellplätze aus `total_capacity - occupied_count` und schreibt das Ergebnis in `ptr_stats->temp_free_spots`. | `Parking *ptr_parking`, `SimStats *ptr_stats` | `1` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Hilfsfunktion um den aktuellen Belegungszustand nach außen bereitzustellen | | |
| `free_parking(ptr_parking)` | Gibt den gesamten durch `init_parking` allokierten Speicher frei. | `Parking *ptr_parking` | `0` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Kapselt die vollständige Speicherfreigabe passend zu `init_parking`, um den Lebenszyklus der Struct konsistent zu halten | | |

---

## queue.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `init_queue()` | Initialisiert eine leere Warteschlange (head/tail = NULL, size = 0). | — | `Queue *` (neu allokiert) |
| ***Begründung:*** | Kapselt die Initialisierung der Warteschlange, damit der Aufrufer nicht direkt mit der internen Struktur (head/tail) arbeiten muss | | |
| `enqueue(ptr_queue, ptr_vehicle)` | Hängt ein Fahrzeug an das Ende der Warteschlange. Inkrementiert `size` um 1. | `Queue *ptr_queue`, `Vehicle *ptr_vehicle` | — |
| ***Begründung:*** | Kapselt das Einfügen in die Warteschlange, damit die Zeigerlogik der verketteten Liste nicht im Simulationsloop auftaucht | | |
| `dequeue(ptr_queue, ptr_stats)` | Entfernt und gibt das Fahrzeug am Anfang der Warteschlange zurück. Dekrementiert `size` um 1. Gibt `NULL` zurück, wenn die Warteschlange leer ist. | `Queue *ptr_queue`, `SimStats *ptr_stats` | `Vehicle *` oder `NULL` |
| ***Begründung:*** | Kapselt das Entfernen aus der Warteschlange und nutzt den Moment des Ausreihens, um die Wartezeit des Fahrzeugs zentral in die Statistik zu übertragen | | |
| `delete_queue(ptr_queue)` | Gibt alle Knoten der Warteschlange frei und setzt sie auf den Initialzustand zurück (size = 0). Die enthaltenen `Vehicle`-Objekte werden nicht freigegeben. | `Queue *ptr_queue` | — |
| ***Begründung:*** | Leert die Warteschlange am Simulationsende, ohne die Queue-Struct selbst freizugeben, damit diese bei Bedarf wiederverwendet werden könnte | | |
| `free_queue(ptr_queue)` | Gibt die durch `init_queue` allokierte `Queue` Struct frei. | `Queue *ptr_queue` | — |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `init_queue`, um den Lebenszyklus der Struct konsistent zu halten | | |

---

## stats.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `init_simstats(ptr_config)` | Allokiert und initialisiert eine `SimStats` Struct mit allen Feldern auf null. | `SimConfig *ptr_config` (für Fehlerausgabe, darf `NULL` sein) | `SimStats *` (neu allokiert) oder `NULL` bei Fehler |
| ***Begründung:*** | Kapselt Allokierung und Nullinitialisierung der Statistik-Struct, damit ein definierter Ausgangszustand vor der Simulation garantiert ist | | |
| `create_output_file(ptr_config)` | Öffnet oder erstellt die CSV-Ausgabedatei. Schreibt die Simulationskonfiguration als Header. Existiert bereits eine Datei mit demselben Namen, wird sie ergänzt (Append-Modus). | `SimConfig *ptr_config` | `FILE *` (offenes Datei-Handle) oder `NULL` bei Fehler |
| ***Begründung:*** | Kapselt die gesamte Dateilogik, damit der Simulationsloop ein fertiges Datei-Handle erhält und nicht mit Dateiverwaltung belastet wird | | |
| `update_simstats(ptr_simstats, ptr_parking, ptr_queue)` | Sammelt und berechnet alle relevanten Kennwerte für den aktuellen Simulationsschritt und schreibt sie in die `SimStats` Struct. | `SimStats *ptr_simstats`, `Parking *ptr_parking`, `Queue *ptr_queue` | `0` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Zentralisiert die Berechnung aller Schrittkennwerte | | |
| `update_peak(ptr_simstats)` | Vergleicht temporäre Werte mit gespeicherten Höchstwerten und aktualisiert diese, falls ein neues Maximum erkannt wird, und speichert die aktuelle Schrittnummer. | `SimStats *ptr_simstats` | `0` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Trennt die Höchstwertaktualisierung von der allgemeinen Statistikberechnung, damit diese Logik separat und gezielt nach jedem Schritt aufgerufen werden kann | | |
| `save_temp_dataset(ptr_simstats, ptr_output_file)` | Schreibt die Statistiken des aktuellen Schritts in die Ausgabedatei. | `SimStats *ptr_simstats`, `FILE *ptr_output_file` | `1` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Kapselt die Ausgabe pro Schritt, damit die Dateiausgabe an einer zentralen Stelle erfolgt und nicht über den Simulationsloop verstreut ist | | |
| `reset_temp_stats(ptr_simstats)` | Setzt alle per-Step (temporären) Felder der Struct auf null zurück. | `SimStats *ptr_simstats` | `0` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Stellt sicher, dass temporäre Felder zu Beginn jedes Schritts sauber zurückgesetzt werden, ohne dass der Aufrufer die interne Feldstruktur kennen muss | | |
| `save_final_dataset(ptr_simstats, ptr_output_file)` | Schreibt die abschließende Simulationszusammenfassung in die Ausgabedatei. | `SimStats *ptr_simstats`, `FILE *ptr_output_file` | `1` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Kapselt die abschließende Ausgabe, damit die Zusammenfassung konsistent an einer Stelle geschrieben wird | | |
| `close_output_file(ptr_output_file, ptr_config)` | Schließt die geöffnete Ausgabedatei. | `FILE *ptr_output_file`, `SimConfig *ptr_config` | `1` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Kapselt das Schließen der Datei passend zu `create_output_file`, um den Lebenszyklus des Datei-Handles konsistent zu halten | | |
| `reset_all_stats(ptr_simstats)` | Setzt alle Felder der Struct auf null zurück. | `SimStats *ptr_simstats` | `0` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Ermöglicht einen vollständigen Neustart der Statistik ohne Neuallokierung, etwa für mehrere aufeinanderfolgende Simulationsläufe | | |
| `free_stats(ptr_simstats)` | Gibt den durch `init_simstats` allokierten Speicher frei. | `SimStats *ptr_simstats` | `0` bei Erfolg, `-1` bei ungültigem Argument |
| ***Begründung:*** | Kapselt die Speicherfreigabe passend zu `init_simstats`, um den Lebenszyklus der Struct konsistent zu halten | | |

---

## simulation.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `run_simulation(ptr_config, ptr_stats)` | Führt die Simulation für die konfigurierte Anzahl an Schritten aus und ruft dabei alle notwendigen Funktionen je Schritt auf. | `SimConfig *ptr_config`, `SimStats *ptr_stats` | `1` bei Erfolg, `-1` bei Fehler |
| ***Begründung:*** | Kapselt den gesamten Simulationsablauf, damit main nur einen einzigen Aufruf benötigt | | |
| `rand_arrival(ptr_config)` | Entscheidet zufällig, ob ein Fahrzeug im aktuellen Schritt ankommt, basierend auf der konfigurierten Ankunftswahrscheinlichkeit. | `SimConfig *ptr_config` | `1` (Ankunft) oder `0` (keine Ankunft) |
| ***Begründung:*** | Isoliert die Zufallsentscheidung über Fahrzeugankunft, damit diese Logik nicht direkt im Simulationsloop steht und bei Bedarf leicht angepasst werden kann | | |

---

## ui.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `initialize_ui()` | Initialisiert die ncurses/PDCurses-Umgebung, erstellt das Hauptfenster und setzt Farbpaare. | — | — |
| ***Begründung:*** | Kapselt das gesamte UI-Setup, damit der Aufrufer nicht direkt mit der Curses-API interagieren muss | | |
| `end()` | Beendet die ncurses/PDCurses-Umgebung und stellt das Terminal wieder her. | — | — |
| ***Begründung:*** | Kapselt das Teardown passend zu `initialize_ui`, damit der Aufrufer keine Curses-Interna kennen muss | | |
| `show_welcome(ptr_config)` | Zeigt den Willkommensscreen und verarbeitet Eingaben: `Enter` → Simulation starten, `S` → Einstellungen, `Q` → Beenden. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Bildet den zentralen Einstiegspunkt der Anwendung und steuert den Programmfluss, bevor die Simulation gestartet wird | | |
| `render_welcome()` | Zeichnet den Willkommensscreen (Titel, Beschreibung, Autorenangaben, Tastaturhinweise). Verarbeitet keine Eingaben. | — | — |
| ***Begründung:*** | Trennt die reine Darstellung von der Eingabeverarbeitung in `show_welcome`, damit beide unabhängig voneinander angepasst werden können | | |
| `show_settings(ptr_config)` | Zeigt das Einstellungsmenü und erlaubt das Ändern von Parametern über Zifferntasten (1–9). `ESC`/`Enter`/`Q` → zurück zum Willkommensscreen. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Kapselt die gesamte Einstellungslogik, damit Konfigurationsänderungen über eine dedizierte Ansicht erfolgen und nicht in den Hauptablauf eingreifen | | |
| `render_settings(ptr_config)` | Gibt alle Konfigurationsfelder und ihre aktuellen Werte formatiert aus. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Trennt die Darstellung der Einstellungen von der Eingabelogik in `show_settings`, damit beide unabhängig voneinander angepasst werden können | | |
| `prompt_uint(ptr_label, ptr_value, min, max)` | Fordert den Nutzer zur Eingabe eines `unsigned int`-Werts innerhalb `[min, max]` auf. Bei ungültiger Eingabe wird eine Fehlermeldung angezeigt und der alte Wert beibehalten. | `char *ptr_label` (Feldname), `unsigned int *ptr_value` (Zielfeld), `unsigned int min`, `unsigned int max` | — |
| ***Begründung:*** | Zentralisiert die validierte Nutzereingabe für Zahlenwerte, damit Eingabeprüfung nicht für jedes Konfigurationsfeld separat implementiert werden muss | | |
| `prompt_string(label, ptr_value, size)` | Fordert den Nutzer zur Eingabe eines nicht-leeren Strings auf. Bei leerer Eingabe wird eine Fehlermeldung angezeigt und der alte Wert beibehalten. | `char *label` (Feldname), `char *ptr_value` (Zielpuffer), `int size` (Puffergröße in Bytes) | — |
| ***Begründung:*** | Kapselt die validierte Stringeingabe separat von `prompt_uint`, da für Strings andere Validierungsregeln gelten | | |
| `show_message(col, ptr_msg, color, kill, ptr_config)` | Zeigt eine einzelne Meldung im Fenster an und wartet auf eine Bestätigung. Bei `kill != 0` wird das Programm nach der Bestätigung beendet. | `int col` (Zeile), `const char *ptr_msg` (Meldungstext), `int color` (Farbpaar: 1=grün, 2=rot, 3=weiß, 4=cyan), `int kill` (0=weiter, ≠0=beenden), `SimConfig *ptr_config` | — |
| ***Begründung:*** | Zentralisiert die Anzeige von Statusmeldungen und Fehlern, damit diese einheitlich dargestellt werden und optionales Programmbeenden an einer Stelle kapseln | | |
| `show_running(ptr_stats)` | Zeigt Live-Statistiken je Schritt (Ausfahrten, Einfahrten, relative Belegung, Warteschlangenlänge, freie Plätze, durchschnittliche Restparkdauer). | `SimStats *ptr_stats` | — |
| ***Begründung:*** | Kapselt die Live-Ausgabe pro Schritt, damit der Simulationsloop nicht direkt mit der Darstellungslogik vermischt wird | | |
| `show_results(ptr_stats)` | Zeigt die abschließende Zusammenfassung aller akkumulierten Simulationsstatistiken. | `SimStats *ptr_stats` | — |
| ***Begründung:*** | Kapselt die Ergebnisanzeige am Simulationsende, damit die Ausgabelogik zentral an einer Stelle liegt und unabhängig vom Simulationsloop angepasst werden kann | | |

---

## utils.h

| Funktion | Beschreibung | Parameter | Rückgabe |
|---|---|---|---|
| `output(col, ptr_msg, color, kill, ptr_config)` | Gibt eine Meldung aus. Im normalen Build wird `show_message()` aufgerufen (UI); in Unit-Test-Builds (`UNIT_TEST` definiert) wird auf stdout ausgegeben. | `int col` (Zeile), `const char *ptr_msg` (Meldungstext), `int color` (Farbpaar), `int kill` (0=weiter, ≠0=beenden), `SimConfig *ptr_config` | — |
| ***Begründung:*** | Entkoppelt Fehlermeldungen aus den Kernmodulen von der UI-Abhängigkeit, sodass Unit-Tests ohne Curses-Kontext laufen können | | |
| `quit(ptr_config)` | Beendet die Anwendung sauber durch Speichern der Konfiguration und Freigabe der Ressourcen. | `SimConfig *ptr_config` | — |
| ***Begründung:*** | Kapselt den sauberen Programmabschluss, damit Konfigurationsspeicherung und Ressourcenfreigabe garantiert an einer zentralen Stelle erfolgen und nicht vom Aufrufer manuell durchgeführt werden müssen | | |
