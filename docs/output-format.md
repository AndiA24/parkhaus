[← README](../README.md)

# Ausgabeformat

## Inhalt
- [Überblick](#überblick)
- [Aufbau der CSV-Datei](#aufbau-der-csv-datei)
- [Abschnitt 1: Konfiguration](#abschnitt-1-konfiguration)
- [Abschnitt 2: Pro-Schritt-Daten](#abschnitt-2-pro-schritt-daten)
- [Abschnitt 3: Gesamtstatistiken](#abschnitt-3-gesamtstatistiken)
- [Statistik-Begründungen](#statistik-begründungen)
- [Verwendung in Excel](#verwendung-in-excel)

---

## Überblick

Während der Simulation wird automatisch eine .csv Datei mit den Stats erstellt. Der Dateiname kann in den Einstellungen festgelegt werden (Standard: `parkhaus_results`). Die Endung `.csv` wird automatisch angehängt. Falls bereits eine Output-Datei mit demselben Namen existiert, wird diese überschrieben.

---

## Aufbau der CSV-Datei

Die Datei besteht aus drei Abschnitten, die direkt hintereinander geschrieben werden.
Für eine Simulation mit N Schritten gilt:

```
[Zeile 1]  Spaltennamen der Konfiguration
[Zeile 2]  Konfigurationswerte des Durchlaufs
[Zeile 3]  Spaltennamen der Pro-Schritt-Daten
[Zeile 4]  Daten 1. Schritt
[Zeile 5]  Daten 2. Schritt
...
[Zeile N]  Daten letzter Schritt
[Zeile N+1] Spaltennamen der Gesamtstatistiken
[Zeile N+2] Gesamtstatistiken der Simulation
```

---

## Abschnitt 1: Konfiguration

In der ersten Zeile stehen die Kopfzeile zu den Konfiguartions-Parametern mit der die Simulation durchlaufen wurde.<br>
In der zweiten Zeile folgen die entsprechenden Werte zu den Parametern aus der ersten Zeile.<br>
Die Simulations-Parameter werden in der Ergebnis-Datei gespeicher, damit der Nuter nachvollziehen kann, mit welchen Eingabe-Parametern die Simulation durchlaufen wurde.

| Spalte | Typ | Beschreibung |
|---|---|---|
| `num_decks` | Integer | Anzahl der Etagen |
| `spots_per_deck` | Integer | Stellplätze pro Etage |
| `initial_occupancy` | Integer | Fahrzeuge zu Simulationsbeginn |
| `max_parking_duration_steps` | Integer | Maximale Parkdauer in Schritten |
| `min_parking_duration_steps` | Integer | Minimale Parkdauer in Schritten |
| `sim_duration_steps` | Integer | Gesamtdauer der Simulation in Schritten |
| `arrival_probability_percent` | Integer | Ankunftswahrscheinlichkeit in % |
| `output_file_name` | Text | Name der Ausgabedatei |
| `seed` | Integer | Seed des Zufallsgenerators |

**Beispiel:**
```
num_decks,spots_per_deck,initial_occupancy,max_parking_duration_steps,min_parking_duration_steps,sim_duration_steps,arrival_probability_percent,output_file_name,seed
5,60,150,200,10,1000,70,parkhaus_results,69
```

---

## Abschnitt 2: Pro-Schritt-Daten

In der 3. Zeile folgt die Kopfzeile für die Per-Step Statistiken (Temp-Stats).<br>
Für jeden Simulationsschritt der Simulation wird eine neue Zeile angelegt. Dadurch lassen sich die Daten später einfach auswerten, zum Beispiel mit einem Script oder durch den Import in Excel.

| Spalte | Typ | Beschreibung |
|---|---|---|
| `step_num` | Integer | Fortlaufende Nummer des aktuellen Schrittes |
| `temp_exits` | Integer | Ausfahrten in diesem Schritt |
| `temp_entries` | Integer | Einfahrten in diesem Schritt |
| `temp_rel_occupancy_percent` | Float | Auslastung in % (z. B. `83.33`) |
| `temp_queue_length` | Integer | Länge der Warteschlange |
| `temp_free_spots` | Integer | Freie Stellplätze |
| `temp_time_left` | Integer | Durchschn. verbleibende Parkdauer der aktuell geparkten Fahrzeuge |

> **Hinweis:** Die Schrittnummer (`step_num`) wird nicht in die CSV geschrieben. Die Zeilennummer innerhalb der Pro-Schritt-Daten (ab Zeile 4) entspricht direkt dem Simulationsschritt.

**Beispiel (3 Schritte):**
```
step_num,temp_exits,temp_entries,temp_rel_occupancy_percent,temp_queue_length,temp_free_spots,temp_time_left
0,0,1,50.33,0,149,87
1,2,1,49.67,0,151,85
2,0,0,49.67,0,151,84
```

---

## Abschnitt 3: Gesamtstatistiken

Nach den N Zeilen für jeden einzelnen Simulationsschritt folgt eine "Fußzeile" mit den Finalen Statistiken. Genau wie alle anderem abgelegten Daten gliedert auch sie sich in eine Kopfzeile mit den Bezeichnern für die Felder und einer weiteren Zeile, die den Datensatz enthält.

| Spalte | Typ | Beschreibung |
|---|---|---|
| `total_exits` | Integer | Gesamtanzahl ausgeparkter Fahrzeuge |
| `total_entries` | Integer | Gesamtanzahl eingeparkter Fahrzeuge |
| `total_queued` | Integer | Fahrzeuge, die mindestens einmal gewartet haben |
| `total_queue_time` | Integer | Summe aller Warteschritte aller Fahrzeuge |
| `total_parking_time` | Integer | Summe aller Parkschritte aller Fahrzeuge |
| `time_full_occupancy` | Integer | Anzahl der Schritte mit 100 % Belegung |
| `peak_queue_length` | Integer | Maximale Warteschlangenlänge |
| `step_longest_queue` | Integer | Schritt mit der längsten Warteschlange |
| `peak_rel_occupancy` | Float | Höchste Auslastung in % |
| `step_highest_occupancy` | Integer | Schritt mit der höchsten Auslastung |

**Beispiel:**
```
total_exits,total_entries,total_queued,total_queue_time,total_parking_time,time_full_occupancy,peak_queue_length,step_longest_queue,peak_rel_occupancy,step_highest_occupancy
712,698,43,187,74831,0,8,423,96.67,312
```

---

## Statistik-Begründungen

Begründung der erhobenen Statistikfelder gemäß Aufgabenstellung.

Bei einigen Parametern werden `unsigned int` verwendet, da sie keine negativen Werte annehmen können und dadurch bei gleichem Speicherverbrauch einen größeren positiven Wertebereich abdecken. Für Kommazahlen (z. B. relative Belegung) werden `float`-Werte verwendet.

### Per-Step Stats

Werden nach jedem Simulationsschritt erhoben und in die CSV-Datei geschrieben.

| Feld | Typ | Begründung |
|---|---|---|
| `temp_exits` | `unsigned int` | Zeigt die Ausfahrten und ermöglicht zusammen mit den Ankünften die Analyse der Zu-/Abnahme der Fahrzeuge im jeweiligen Schritt |
| `temp_entries` | `unsigned int` | Zeigt die Einfahrten in das Parkhaus im jeweiligen Schritt |
| `temp_rel_occupancy_percent` | `float` | Zeigt wie ausgelastet das Parkhaus gerade ist |
| `temp_queue_length` | `unsigned int` | Indikator für Überlast – eine wachsende Schlange signalisiert, dass das Parkhaus zu klein ist |
| `temp_free_spots` | `unsigned int` | Gibt die Kapazitätsreserve an |
| `temp_time_left` | `unsigned int` | Gibt an, wann mit den nächsten größeren Mengen an Ausfahrten zu rechnen ist |

### Final Stats

Werden einmalig am Ende der Simulation erhoben und an die CSV-Datei angehängt. `total_queued` und `total_queue_time` werden nicht direkt ausgegeben, sondern zur Berechnung der durchschnittlichen Wartezeit verwendet.

| Feld | Typ | Begründung |
|---|---|---|
| `total_exits` | `unsigned int` | Gibt die Summe der Ausfahrten während der gesamten Simulation an |
| `total_entries` | `unsigned int` | Gibt die Summe aller Einfahrten während der Simulation an |
| `total_queued` | `unsigned int` | Basis zur Berechnung der durchschnittlichen Wartezeit (`total_queue_time / total_queued`) |
| `total_queue_time` | `unsigned int` | Basis zur Berechnung der durchschnittlichen Wartezeit (`total_queue_time / total_queued`) |
| `total_parking_time` | `unsigned int` | Basis zur Berechnung der durchschnittlichen Parkdauer (`total_parking_time / total_exits`) |
| `time_full_occupancy` | `unsigned int` | Zeigt wie oft das Parkhaus an seine Kapazitätsgrenze gestoßen ist – Grundlage für eine Auslastungsanalyse |
| `peak_queue_length` | `unsigned int` | Zeigt die maximale Länge der Schlange – aussagekräftig für die Anzahl der Zufahrten |
| `step_longest_queue` | `unsigned int` | Ordnet das Maximum der Schlange zeitlich ein |
| `peak_rel_occupancy` | `float` | Zeigt die maximale Auslastung – aussagekräftig für die Anzahl der Parkplätze |
| `step_highest_occupancy` | `unsigned int` | Ordnet das Maximum der Auslastung zeitlich ein |

---

## Verwendung in Excel

### Datei öffnen

Da die CSV-Datei Kommas als Trennzeichen verwendet, muss sie in Excel über den Import-Assistenten unter Daten/ Daten abrufen aus Textdatei/csv – **nicht** per Doppelklick geöffnet werden.

**Excel (Windows/Mac):**
1. `Daten` → `Aus Text/CSV`
2. Datei auswählen
3. Trennzeichen: **Komma** auswählen
4. `Laden` klicken

> **Hinweis:** Alle Werte, die Kommazahlen annehmen können, z.B. `temp_rel_occupancy_percent` und `peak_rel_occupancy` verwenden einen **Punkt** als Dezimaltrennzeichen. Das sollte bei der Weiterverarbeitung mit Excel oder anderen Programmen beachtet werden.

---

### Empfohlene Diagramme

**Auslastung über Zeit** (Liniendiagramm):
- X-Achse: `step_num` (= Simulationsschritt)
- Y-Achse: `temp_rel_occupancy_percent`

**Warteschlange über Zeit** (Liniendiagramm):
- X-Achse: `step_num` (= Simulationsschritt)
- Y-Achse: `temp_queue_length`

**Ein- und Ausfahrten pro Schritt** (Säulendiagramm):
- X-Achse: `step_num` (= Simulationsschritt)
- Y-Achse: `temp_entries` und `temp_exits` als zwei Datenreihen

**Freie Plätze über Zeit** (Flächendiagramm):
- X-Achse: `step_num` (= Simulationsschritt)
- Y-Achse: `temp_free_spots`
