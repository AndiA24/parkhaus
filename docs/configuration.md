[← README](../README.md)

# Konfigurationsdatei

## Inhalt
- [Überblick](#überblick)
- [Felder](#felder)
- [Standardwerte](#standardwerte)
- [Dateiformat](#dateiformat)
- [Manuell bearbeiten](#manuell-bearbeiten)

---

## Überblick

Die Simulation speichert alle Einstellungen automatisch in einer Konfigurationsdatei. Beim nächsten Programmstart werden diese Werte geladen, sodass die letzte Konfiguration erhalten bleibt. Und auch nach einem Neustart der Simulation noch die Werte der letzten Simulation vorhanden sind, sodass nur einzelne Werte geändert werden müssen. Außderm ist dadurch ein Exportieren oder Importieren der Konfiguration möglich.

- **Dateiname:** `parkhaus_config.csv` (im Arbeitsverzeichnis)
- Wird automatisch (falls vohanden) beim Programmstart geladen
- Nach dem Starten der Simulation wird die verwendete Konfiguration in der Datei gespeichert. Falls noch nicht vorhanden wird die Datei erstellt.
- Falls die Datei bei Programmstart nicht vorhanden ist, werden Standardwerte geladen. 
- Eine Info über das erfolgreiche Laden der Konfiguration oder das Laden von Standardwerten erfolgt bei Programmstart.

---

## Felder

| Feld | Typ | Wertebereich | Beschreibung |
|---|---|---|---|
| `num_decks` | Integer | 1 – 99 | Anzahl der Etagen des Parkhauses |
| `spots_per_deck` | Integer | 1 – 999 | Stellplätze pro Etage. Gesamtkapazität = `num_decks × spots_per_deck` |
| `initial_occupancy` | Integer | 0 – Gesamtkapazität | Fahrzeuge, die zu Beginn der Simulation bereits im Parkhaus stehen |
| `max_parking_duration_steps` | Integer | 1 – `sim_duration_steps` | Maximale Anzahl an Schritten, die ein Fahrzeug parken darf |
| `min_parking_duration_steps` | Integer | 1 – `max_parking_duration_steps` | Minimale Anzahl an Schritten, die ein Fahrzeug parken muss |
| `sim_duration_steps` | Integer | 1 – 4294967295 | Gesamtdauer der Simulation in Schritten |
| `arrival_probability_percent` | Integer | 1 – 100 | Wahrscheinlichkeit in %, dass pro Schritt ein neues Fahrzeug ankommt |
| `output_file_name` | Text | max. 69 Zeichen | Name der Ergebnis-CSV-Datei (ohne `.csv`-Endung) |
| `seed` | Integer | 0 – 4294967295 | Seed des Zufallsgenerators. Gleicher Seed + gleiche Einstellungen = identische Simulation |

> **Hinweis:** `config_file_name` (`parkhaus_config.csv`) ist von Programmseite her festgelegt und kann nicht verändert werden.

---

## Standardwerte

Wenn keine Konfigurationsdatei gefunden wird oder die Datei ungültig ist, werden folgende Standardwerte verwendet:

| Feld | Standardwert |
|---|---|
| `num_decks` | `5` |
| `spots_per_deck` | `60` |
| `initial_occupancy` | `150` |
| `max_parking_duration_steps` | `200` |
| `min_parking_duration_steps` | `10` |
| `sim_duration_steps` | `1000` |
| `arrival_probability_percent` | `70` |
| `output_file_name` | `parkhaus_results` |
| `seed` | `69` |

Die Standardkonfiguration entspricht einem mittelgroßen Parkhaus (300 Plätze) mit einer moderaten Ankunftsrate.

---

## Dateiformat

Die Konfigurationsdatei enthält genau eine Datenzeile ohne Kopfzeile. Die Werte stehen in folgender Reihenfolge:

| Position | Feldname |
|----------|----------|
| 1 | `num_decks` |
| 2 | `spots_per_deck` |
| 3 | `initial_occupancy` |
| 4 | `max_parking_duration_steps` |
| 5 | `min_parking_duration_steps` |
| 6 | `sim_duration_steps` |
| 7 | `arrival_probability_percent` |
| 8 | `output_file_name` |
| 9 | `seed` |

**Beispiel (`parkhaus_config.csv`):**
```
5,60,150,200,10,1000,70,parkhaus_results,69
```

Es gibt keine Kopfzeile, da die Datei mit `fscanf` positionsbasiert gelesen wird. Eine Kopfzeile würde beim Einlesen als ungültig erkannt und die Standardwerte würden geladen.

Die Felder sind ohne Leerzeichen mit Kommata getrennt.

---

## Manuell bearbeiten

Die Konfigurationsdatei kann auch direkt mit einem Texteditor bearbeitet werden. Dabei sind folgende Punkte zu beachten:

- Die Werte müssen in der **exakten Reihenfolge** aus der Tabelle oben stehen
- **Kein Zeilenumbruch** am Ende (oder genau einer – beides funktioniert)
- Alle Werte müssen **positive ganze Zahlen** sein und sich innerhalb des für die Simulation sinnvollen Wertebereichs befinden, daher ist ein Bearbeiten der Datei nur empfohlen für erfahrene Benutzer
- Bei einem Fehler im Format werden beim nächsten Start **Standardwerte** geladen und die fehlerhafte Datei überschrieben

> **Tipp:** Es ist einfacher, die Werte direkt im Einstellungsmenü des Programms zu ändern, da dort automatisch auf gültige Wertebereiche geprüft wird. Bearbeiten der Datei ist nur für erfahrene Nutzer vorgesehen. Eigentlicher Nutzen ist das Ex- & Importieren der Konfiguration.
