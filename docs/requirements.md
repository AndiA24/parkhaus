[← README](../README.md)

# Anforderungen & Planung

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
