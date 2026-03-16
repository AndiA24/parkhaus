# Parking-simulation in C
Team-Repository für den Programmentwurf "Parkhaus" zur Vorlesung Programmieren I an der DHBW Friedrichshafen

## Docs
> **Erläuterung / Reflektion nach Aufgabe d): [Projektreflexion](docs/project-reflection.md)**

- [User Manual](docs/user-manual.md)
- [Konfigurationsdatei](docs/configuration.md)
- [Ausgabeformat](docs/output-format.md)
- [Architektur & Datenstrukturen](docs/architecture.md)
- [Modulreferenz](docs/modules.md)
- [Anforderungen & Planung](docs/requirements.md)
- [Testing](docs/testing.md)



## Features

- Schrittbasierte Simulation eines Parkhauses mit konfigurierbaren Etagen und Stellplätzen
- Warteschlange bei voller Belegung
- Live-Anzeige der Kennwerte je Simulationsschritt (Terminal-UI via ncurses/PDCurses)
- Auswertung und Anzeige von Gesamtstatistiken am Simulationsende
- Alle Parameter über ein interaktives Einstellungsmenü konfigurierbar
- Konfiguration wird automatisch gespeichert und beim nächsten Start geladen
- Seed für reproduzierbare Simulationsergebnisse
- Automatische CSV-Ausgabedatei nach jeder Simulation

## Quick Start

> **Wichtig:** Terminalfenster vor dem Start auf mindestens **86 × 25 Zeichen** vergrößern.

```bash
cmake -B build
cmake --build build
./build/parkhaus
```

Weitere Informationen zu Voraussetzungen, Einstellungen und Bedienung: [User Manual](docs/user-manual.md)

Detaillierte Architektur, Datenstrukturen, Coding-Konventionen und Modulreferenz: [Architektur](docs/architecture.md) · [Module](docs/modules.md)
