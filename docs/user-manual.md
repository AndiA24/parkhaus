[← README](../README.md)

# Benutzerhandbuch

## Inhalt
- [Voraussetzungen & Starten](#voraussetzungen--starten)
- [Hauptmenü](#hauptmenü)
- [Einstellungen](#einstellungen)
- [Simulation läuft](#simulation-läuft)
- [Ergebnisse](#ergebnisse)
- [Ausgabedatei](#ausgabedatei)

---

## Voraussetzungen & Starten

### Voraussetzungen
- CMake ≥ 3.10
- GCC oder kompatibler C-Compiler
- Terminal mit ncurses-Unterstützung (Linux/macOS) bzw. PDCurses (Windows)

### Projekt bauen

```bash
cmake -B build
cmake --build build
```

### Programm starten auf

> **Wichtig:** Das Terminalfenster muss vor dem Start auf mindestens **86 × 25 Zeichen** gezogen werden, damit die Oberfläche korrekt dargestellt wird. Außerdem darf es keine git-bash sein sondern muss ein reguläres terminal sein.

```bash
./build/parkhaus
```

Beim Start wird automatisch die Konfigurationsdatei `parkhaus_config.csv` eingelesen (falls vorhanden). Andernfalls werden Standardwerte verwendet.

---

## Hauptmenü

Nach dem Start erscheint der Willkommensbildschirm mit einer kurzen Projektbeschreibung.

| Taste | Aktion |
|---|---|
| `ENTER` | Simulation mit aktuellen Einstellungen starten |
| `S` | Einstellungen öffnen |
| `Q` | Programm beenden |

---

## Einstellungen

Im Einstellungsmenü können alle Simulationsparameter angepasst werden. Die aktuelle Belegung wird jeweils rechts neben dem Feldnamen angezeigt.

Taste drücken, um den entsprechenden Wert zu bearbeiten. Mit `ENTER`, `Q` oder `ESC` wird gespeichert und zum Hauptmenü zurückgekehrt. Die Einstellungen werden automatisch in der Konfigurationsdatei gespeichert.

| Taste | Feld | Wertebereich | Beschreibung |
|---|---|---|---|
| `1` | Etagen | 1 – 99 | Anzahl der Stockwerke des Parkhauses |
| `2` | Stellpl./Etage | 1 – 999 | Anzahl der Parkplätze pro Etage |
| `3` | Startbelegung | 0 – Gesamtkapazität | Fahrzeuge im Parkhaus zu Simulationsbeginn |
| `4` | Max. Parkdauer | 1 – Sim.-Dauer | Maximale Schritte, die ein Fahrzeug parken kann |
| `5` | Min. Parkdauer | 1 – Max. Parkdauer | Minimale Schritte, die ein Fahrzeug parken muss |
| `6` | Sim.-Dauer | 1 – 4294967295 | Gesamtanzahl der Simulationsschritte |
| `7` | Ankunftswahr. | 1 – 100 % | Wahrscheinlichkeit, dass pro Schritt ein Fahrzeug ankommt |
| `8` | Seed | 0 – 4294967295 | Startwert für den Zufallsgenerator (gleicher Seed = gleiche Ergebnisse) |
| `9` | Ausgabedatei | Text | Dateiname der CSV-Ausgabedatei (ohne Endung) |

> **Hinweis:** Die Gesamtkapazität ergibt sich aus `Etagen × Stellpl./Etage`.

---

## Simulation läuft

Während der Simulation wird eine Live-Ansicht mit den aktuellen Werten des jeweiligen Schritts angezeigt. Die Simulation kann nicht manuell unterbrochen werden und läuft bis zum Ende der eingestellten Schrittanzahl.<br>
Sollte es einen Fehler geben, der nicht von der Logik abgedeckt wird oder das Proramm einfach erzwungen beendet werden, so muss das über `CTRL` + `C` erfolgen

| Anzeige | Beschreibung |
|---|---|
| Aktueller Schritt | Der gerade simulierte Zeitschritt |
| Einfahrten diesen Schritt | Fahrzeuge, die in diesem Schritt eingeparkt haben |
| Ausfahrten diesen Schritt | Fahrzeuge, die in diesem Schritt ausgefahren sind |
| Aktuell freie Parkplätze | Anzahl der freien Stellplätze |
| Länge der Warteschlange | Fahrzeuge, die aktuell auf einen Platz warten |
| Durchschn. Parkzeit pro Auto | Mittlere verbleibende Parkdauer der geparkten Fahrzeuge |
| Auslastung (Balken) | Prozentuale Belegung des Parkhauses (grün < 85 %, rot ≥ 85 %) |

---

## Ergebnisse

Nach Abschluss der Simulation werden die Gesamtstatistiken angezeigt.

**Fahrzeuge:**

| Anzeige | Beschreibung |
|---|---|
| Ausfahrten gesamt | Fahrzeuge, die während der Simulation ausgeparkt haben |
| Einfahrten gesamt | Fahrzeuge, die während der Simulation eingeparkt haben |

**Warteschlange:**

| Anzeige | Beschreibung |
|---|---|
| Fahrzeuge in Warteschlange gesamt | Gesamtanzahl aller Fahrzeuge, die warten mussten |
| Summierte Wartezeit | Summe aller Warteschritte aller Fahrzeuge |
| Längste Warteschlange | Maximale Schlangenlänge während der gesamten Simulation |
| Schritt mit längster Schlange | Zeitschritt, an dem die Schlange am längsten war |
| Durchschn. Wartezeit pro Auto | Summierte Wartezeit ÷ Anzahl wartender Fahrzeuge |
| Anteil wartender Fahrzeuge | Prozentualer Anteil der Fahrzeuge, die warten mussten |

**Parkhaus:**

| Anzeige | Beschreibung |
|---|---|
| Durchschn. Parkdauer | Mittlere Parkdauer aller ausgeparkten Fahrzeuge |
| Summierte Parkzeit | Summe aller Parkschritte aller Fahrzeuge |
| Durchschn. Auslastung | Mittlere prozentuale Belegung über die gesamte Simulation |
| Höchste Auslastung | Maximale Belegung in einem einzelnen Schritt |
| Schritt mit höchster Auslastung | Zeitschritt, an dem die Auslastung am höchsten war |
| Schritte mit voller Belegung | Anzahl der Schritte, in denen das Parkhaus komplett belegt war |

Mit `ENTER`, `Q` oder `ESC` gelangt man zurück zum Hauptmenü.

---

## Ausgabedatei

Nach jeder Simulation wird automatisch eine CSV-Datei mit dem konfigurierten Namen (Standard: `parkhaus_results.csv`) erstellt. Sie enthält die Konfiguration, pro-Schritt-Daten und die Gesamtstatistiken.

Weitere Informationen zum Dateiformat und zur Verwendung in Excel: [Ausgabeformat](output-format.md)
