# Projektdokumentation – Parkhaus-Simulation (gemeinsam verfasst)

## 1. Wie haben wir die Aufgabenstellung gelöst?

### Teamstruktur & Arbeitsaufteilung

Innerhalb unseres Teams sind die Vorkenntnisse ziemlich homogen verteilt, daher konnte eine sehr gleichmäßige Arbeitsteilung erfolgen. 
Wir haben uns zu Beginn alle alleine Gedanken zu der Aufgabenstellung, Features und Konzepten zur technischen Realisierung gemacht. Diese haben wir dann bei einem gemeinsamen Termin abgegelichen und uns auf Anforderungen an die Funktionalität, Bedinung sowie Architektur geeinigt. Anhand dessen haben wir Arbeitspakete für unser Kanban-Board erstellt, und uns auf die Arbeitsteilung geeinigt, sodass sie Arbeitspakete alleine ohne weitere Absprachen bearbeitet werden können.

Im Zuge dessen haben wir uns auf den Ablauf der Simulation im Pseudocode geeinigt und die dafür notwendigen Funktionen definiert, anhand der Funktionsprototypen sowie der zugehörigen Doxygen-Comments haben wir klar definiert, welche Parameter die Funktion erhält, was sie macht und was sie zurück gibt. Im Vergleich zu diesem anfänglichen Entwurf mussten nur kleine Änderungen an einzelnen Funktionen vorgenommen werden und die wesentlich Struktur blieb erhalten.

Um einen Überblick über den aktuellen Arbeitsstand sowie die erledigten Arbeiten zu behalten, haben wir für alle Aufgaben / Arbeitspakete entsprechende Branches auf GIT erstellt, die bei Finalisierung in einer Pull-Request diskutiert wurden. Hier haben wir gegebenenfalls Fehler korrigiert, Umsetzungen diskutiert oder angemerkt, falls uns etwas eingefallen ist, was noch zu beachten ist oder was im Konflikt zu den eigenen Funktionen steht.

Jedes Teammitglied war zuständig und verantwortlich für bestimmte Funktionen. Zwar wurden auch teilweise gegenseitig Änderungen oder Anpassungen vorgenommen, doch hatte für jede Funktion, beziehungsweise jeden Abschnitt des Programms, eine Person den Überblich über den Ablauf sowie etwaiige To-Dos oder Fehler, die durch neue Pull-Requests entstehen könnten.

- **Gemeinsame Planungsphasen**: Anforderungsanalyse und Architekturentscheidungen wurden im gesamten Team besprochen und festgelegt.
- **Funktionssignaturen zuerst**: Bevor mit der Implementierung begonnen wurde, wurden für jede Funktion Parameter, Rückgabewerte und Zuständigkeiten gemeinsam definiert. Dadurch konnten Funktionen unabhängig voneinander entwickelt werden.
- **Pseudocode-First**: Die Simulationslogik wurde zunächst gemeinsam in Pseudocode formuliert. Danach wurden nur noch Feinheiten abgestimmt und die Funktionen implementiert.
- **Feature-Branches & Pull Requests**: Für jedes Arbeitspaket wurde ein eigener Branch erstellt. Änderungen wurden über Pull Requests eingereicht, die das Team reviewt hat. Bei Bedarf wurden Optimierungen oder Korrekturen angefordert.
- **Kanban-Board**: Zur Aufgabenverfolgung wurde ein Kanban-Board eingesetzt (Backlog → Ready → In Progress → In Review → Done).

### Technische Umsetzung

**Datenstruktur des Parkhauses:**

Die Datenstruktur des Parkhauses spiegelt direkt wider, wie ein reales Parkhaus aufgebaut ist: Ein Parking-Objekt enthält mehrere Etagen (ParkingDeck), und jede Etage enthält wiederum eine Reihe einzelner Stellplätze (ParkingSpot). Jeder Stellplatz besitzt einen Parameter, der zeigt, ob er frei ist. Falls dieser belegt ist, enthält er einen Pointer auf das Fahrzeug, das auf dem Parkplatz steht. Dieses liegt ebenfalls im Heap und wird nur über seine Adresse verwaltet.

Die gesamte Struktur ist dabei vollständig dynamisch allokiert: Weder Etagen noch Stellplätze werden vorab in fester Anzahl im Code festgelegt, sondern zur Laufzeit auf dem Heap angelegt. Das macht das Parkhaus beliebig skalierbar.

Das Parkhaus ist modular und vollständig dynamisch allokiert aufgebaut:

- `Parking` enthält ein Array von Pointern auf `ParkingDeck`-Structs
- Jede `ParkingDeck` enthält ein Array von Pointern auf `ParkingSpot`-Structs
- Jeder `ParkingSpot` enthält eine ID, einen Belegt-Status und – falls belegt – einen Pointer auf das dynamisch allokierte `Vehicle`

Durch diese Struktur kann gut auf die einzelnen Elemente über Schleifen und Pointer-Arithmetik beziehungsweise Itterationen zugegriffen werden.

Durch den konsequenten Einsatz von Pointern müssen Daten nicht kopiert / übergeben werden. Datenzugriff sowie die damit einhergehende Bearbeitung der Daten erfolgt durch Übergabe der entsprechenden Pointer. Das spart Speicher und steigert die Effizienz.

**Laufzeitoptimierungen:**

- Freie Parkplätze werden auf einem **Stack** gehalten → O(Decks) bei der Suche nach einem freien Platz (statt O(Decks × Spots) Iteration durch das gesamte Parkhaus)
- Geparkte Fahrzeuge werden in einem **separaten Array** verwaltet → nur tatsächlich belegte Plätze müssen auf abgelaufene Parkdauer geprüft werden
- Eine **Queue** nimmt wartende Fahrzeuge auf, bevor sie einfahren

Eine später implementierte Funktion optimiert die Komplexität des Codes. Vorher wurde bei der Suche nach freien Spots, sowie dem Überprüfen, welches Auto das Parking verlässt, durch das gesamte Parkhaus itteriert. 

Durch eine Optimierung, liegen Pointer auf freie Parkplätze auf einem Stack. Dadurch kann der nächste freie Parkplatz der obersten Stelle des Stack entnommen werden. Durch die Verwendung einer Arrays zur Speicherung der Pointer auf belegte Spots müssen nur die tatsächlich belegten Spots bei dem `check_exits()` durchlaufen werden. Das spart Zeit und Ressourcen.

**Error Handling:**

Ein später implementiertes Error-Hanlding behandelt einheitlich alle Fehler die zur Laufzeit auftreten können.

Wir überprüfen in jeder Funktion Fehler durch fehlende oder falsch übergebene Parameter, Fehler beim Allokieren von Speicher, unplausible Werte oder die Division-by-zero. Dadurch können wir weitere Fehler erkennen, bevor sie entstehen und Segfaults oder Memory-Leaks erkennen.

Wenn solche Fehler auftreten, geben wir die für C idiomatischen Rückgabewerte zurück: -1 / NULL für einen fatalen Fehler, -2 für sonstige Fehler, 0 für Erfolg. Nach jedem Funktionsaufruf prüfen wir den Rückgbewert, um im Falle eines Fehler reagieren zu können. Wir unterscheiden bewusst bei den Schweregraden der Fehler. Es gibt Fehler wie beispielsweise in `create_initial_occupancy()`, die dem Nutzer mitgeteilt werden, den weiteren Programmlauf jedoch nicht behindern, wodurch das Programm fortgesetzt werden kann. Andere Fehler, wie zum Beispiel Fehler bei dem Allokieren von Speicher, um die `Struct Parking` zu erstellen, führen zu einem fatalen Fehler, wodurch das Programm gezielt beendet wird.

Wir haben für sämlichen allokierten Speicher clean-up Funktionen, um Memory-Leaks zu vermeiden. An manchen Stellen geben wir den Speicher jedoch bewusst nicht im Code frei, sondern verwenden den nativen Befehl `exit()`, der das Programm beendet und den gesammten im Heap allokierten Speicher freigibt.


**Build & Testing:**

- **CMake**: Programm und Unit-Tests werden mit einem Befehl kompiliert
- **CTest**: Alle Tests werden mit einem Befehl ausgeführt; Ergebnisse landen in einem Log-File
- **Compile-Flag**: Das User Interface kann beim Kompilieren für Unit-Tests vollständig ausgeblendet werden. Eigene Wrapper-Funktionen entscheiden, ob Ausgaben über das UI oder über `printf` erfolgen.

Durch diesen Workflow haben wir während der Entwicklung viel Zeit gespart. Das CMake-File musste einmal erstellt werden und wurde bei Ergänzungen von z.B. Unit-Tests nur ergäntz, dadurch konnte jedes Teammitglied das Projekt unter gleichen Bedingungen kompillieren, ohne dass lange Befehel ausgetauscht werden mussten.

Außerdem ist der Code durch das UI schwierig zu testen. Compile-Flags in den CMake Befehlen, sowie bedingte includes / bedingte Ausgaben in dem Code haben uns ermöglicht, Funktionen die normal von dem UI beziehungsweise der Ausgaben über das UI abhängen in den Unit-Tests ohne das UI über einfache Übergaben sowie Ausgaben üper `printf()` zu verwenden.

### Erweiterungen über die Aufgabenstellung hinaus

Wir haben uns bereits zu Beginn während der Planung der Anforderungen und der Umsetzung entschieden, einige Anforderungen zu setzen, die über die Aufgabenstellung hinausgehen.

- **Dynamische Speicherverwaltung** für speicher- und laufzeitschonendes Verhalten
- **`typedef struct`** für bessere Lesbarkeit des Codes
- **Erweitertes User Interface**: Intuitiver als eine reine `printf`/`scanf`-Lösung, benutzerfreundlicher und schnellere Bedinung als alle Eingabeparameter zu durchlaufen
- **CSV-Ausgabe**: Ergebnisse können direkt in Excel oder anderen Programmen / Scrips geöffnet und ausgewertet werden (z. B. als Diagramme). Das ermöglicht dem Benutzer das Ergebnis der Simulation besser zu interpretieren (gegenüber blanken Zahlenwerten) und anhand von diesem eine Entscheidung über den Ausbau / die Dimensionierung des Parkhauses zu treffen.
- **Erweiterte Statistiken**: Mehr als gefordert, aber alle Werte treffen relevante Aussagen über den Parkbetrieb und lassen Rückschlüsse auf Stoßzeiten, falsche Dimensionierung und andere Umweltfaktoren treffen (Begründung zu den Statistiken siehe [output-format.md – Statistik-Begründungen](output-format.md#statistik-begründungen))
- **Konfigurationsdatei**: Wird automatisch generiert, falls keine vorhanden. Aktuelle Einstellungen werden beim Simulationsstart gespeichert und beim nächsten Programmstart wiederhergestellt. Dadurch muss der Nutzer nicht alle Parameter eingaben sondern nur einzelne Parameter anpassen.
- **Freier Output-Dateiname**: Mehrere Simulationen können gespeichert werden, ohne dass Ergebnisse überschrieben werden
- **Konfigurationsinfo im Output-File**: Die Infos über die in der jewailigen Simulation verwendeten Parameter sthen in der Kopfzeile der Ausgabedatei. Der Benutzer kann dadurch anhand der Ausgabedatei nachvollziehen, mit welchen Einstellungen simuliert wurde
- **Endlosschleife**: Das Programm läuft nach einer Simulation nicht automatisch aus, sondern ermöglicht mehrere aufeinanderfolgende Simulationen bis zur bewussten Beendung.
- **Initial Occupancy**: Dem Parkhaus kann eine Belegung zu Beginn der Simulation zugewiesen werden, da ein komplett leeres Parkhaus generell unrealistisch wäre.

---

## 2. Welche Optionen wurden diskutiert?

### Datenstruktur für freie Parkplätze

- **Option A (initial)**: Iteration durch das gesamte Parkhaus zur Suche nach einem freien Platz → O(Decks × Spots)
- ⁠**Option B (gewählt)**: Freie Parkplätze werden auf einem Stack gehalten → O(Decks) bei der Suche
Zunächst wurde die Suche nach einem freien Parkplatz so implementiert, dass das gesamte Parkhaus durchsucht wird. Im schlechtesten Fall führt das zu einer Laufzeit von O(Decks × Spots), da jeder Spot geprüft werden muss. Um diese Suche zu vermeiden, wurde pro Deck ein Stack eingeführt, der Pointer auf alle freien Spots hält. Beim Initialisieren des Parkhauses wird jeder Spot auf den Stack seines Decks gelegt. Fährt ein Fahrzeug ein, wird der oberste Eintrag des Stacks gepoppt und das Fahrzeug diesem zugewiesen. Fährt ein Fahrzeug aus, wird der freigewordene Spot wieder oben auf den Stack gelegt. Da nur noch über die Decks iteriert wird bis eine mit freien Spots gefunden wird, verbessert sich die Laufzeit auf O(Decks).

### Prüfung auf abgelaufene Parkdauer

- ⁠**Option A (initial)**: Iteration durch alle Parkplätze des gesamten Parkhauses
- ⁠**Option B (gewählt)**: Separates Array mit nur den aktuell geparkten Fahrzeugen → deutlich kleinere Iteration
Um festzustellen, ob die Parkdauer eines Fahrzeugs abgelaufen ist, wurde zunächst das gesamte Parkhaus durchlaufen. Im schlechtesten Fall führt das zu einer Laufzeit von O(Decks × Spots), da jeder Spot einzeln geprüft werden muss. Um diese Suche zu vermeiden, wurde ein Array eingeführt, das Pointer auf alle aktuell belegten Spots hält. Bei der Überprüfung muss nun nur noch über dieses Array iteriert werden, was die Laufzeit auf O(belegte Spots) verbessert. Verlässt ein Fahrzeug das Parkhaus, wird sein Eintrag aus dem Array entfernt. Um Lücken im Array zu vermeiden, übernimmt das letzte Element des Arrays die Position des entfernten Eintrags.

#### Einfahrtsbeschränkung auf ein Fahrzeug pro Zeitschritt

Bei der Einfahrt wurde bewusst entschieden, dass pro Simulationsschritt maximal ein Fahrzeug aus der Warteschlange ins Parkhaus einfahren kann. Diese Einschränkung spiegelt die Realität einer physischen Schranke wider: Eine Schranke lässt immer nur ein Fahrzeug auf einmal passieren – erst wenn dieses eingefahren ist und die Schranke wieder geschlossen wurde, kann das nächste Fahrzeug den Einfahrtsvorgang starten.

Bei der **Ausfahrt** besteht diese Einschränkung nicht. Dort wird stattdessen eine automatische Kennzeichenerkennung angenommen: Das System erfasst das Kennzeichen des ausfahrenden Fahrzeugs und bucht den Parkplatz automatisch frei. Deshalb können mehrere Autos in einem Zeitschritt ausfahren, denn es wird angenommen, dass die Erfassung berührungslos und ohne manuelle Interaktion erfolgt.

### Ausgabeformat

- **Option A**: Einfache Konsolenausgabe mit ⁠ printf ⁠
- **Option B (gewählt)**: CSV-Ausgabe → kompatibel mit Excel, ermöglicht Diagramme und weitere Auswertungen

Für das Ausgabeformat wurde bewusst CSV gewählt, da dieses Format mehrere Vorteile bietet. CSV-Dateien sind mit gängigen Tabellenkalkulationsprogrammen wie Excel kompatibel, was eine übersichtliche Darstellung der Daten ermöglicht — besonders bei großen Datensätzen. Darüber hinaus lassen sich die Daten einfach visualisieren und auswerten, da Diagramme direkt aus den importierten Daten erstellt werden können.

### Vereinzelte Implementierungslogiken

#### Queue
Die Warteschlange wurde von Beginn an als Queue-Datenstruktur geplant, da das FIFO-Prinzip das natürliche Verhalten einer Einfahrtswarteschlange abbildet. Für die interne Implementierung wurde zunächst eine doppelt verkettete Liste in Betracht gezogen. Im Laufe der Entwicklung stellte sich jedoch heraus, dass eine Rückwärtsnavigation nicht benötigt wird, weshalb die Implementierung auf eine einfach verkettete Liste reduziert wurde. Dies vereinfacht die Struktur und vermeidet unnötigen Verwaltungsaufwand. 

#### Vorbelegung (Initial Occupancy)
Eine weitere Entwurfsentscheidung betraf die Vorbelegung des Parkhauses vor Simulationsstart. Anstatt die Simulation stets mit einem leeren Parkhaus zu beginnen, wurde die Möglichkeit eingeführt, eine vom Benutzer konfigurierbare Anzahl an Fahrzeugen beim Initialisieren einzuparken. Diese Option wurde bewusst gewählt, um realistischere Ausgangszustände simulieren zu können und dem Benutzer mehr Kontrolle über die Simulationsparameter zu geben.

#### Ausgabe (Output-Datei)
Bei der Handhabung der Ausgabedatei stand zur Diskussion, ob bei einer bereits existierenden Datei mit gleichem Namen der neue Inhalt angehängt oder die Datei überschrieben werden soll. Die Entscheidung fiel auf das Überschreiben, da angehängte Daten mehrerer Simulationsläufe die Datei schnell unübersichtlich und schwer auswertbar machen würden. Da jede Simulation über einen konfigurierbaren Seed reproduzierbar ist, kann ein bestimmtes Szenario bei Bedarf jederzeit erneut ausgeführt werden und liefert dabei denselben Output.

---

## 3. Warum haben wir uns für die gewählte Variante entschieden?

- **Stack für freie Plätze**: Die Laufzeitverbesserung von O(Decks * Spots) auf O(Decks) ist bei großen Parkhäusern erheblich. Der Mehraufwand beim Initialisieren ist vernachlässigbar.

- **Separates Array für geparkte Fahrzeuge**: Vermeidet unnötige Iterationen über leere Parkplätze, was gerade bei einem niedrig ausgelastetem Parkhaus relevant wird.

- **CSV anstatt plain text**: CSV-Dateien ermöglichen eine strukturierte Darstellung, einfache Filterung und die Erstellung von Diagrammen zur Auswertung der Datensätze. Plain Text hätte eine zusätzliche Konvertierung erfordert, bevor die Daten sinnvoll ausgewertet werden könnten.

- **Dynamische Speicherverwaltung**: Die Größe des Parkhauses wird erst zur Laufzeit durch die Benutzerkonfiguration festgelegt. Statische Arrays würden entweder Speicher verschwenden oder die maximale Größe des Parkauses künstlich begrenzen. Zusätzlich wird bei Funktionsaufruf ausschließlich der Pointer übergeben, was das Kopieren großer Strukturen vermeidet und den Speicher- sowie Zeitaufwand reduziert.

- **Erweitertes UI**: Eine intuitive Bedienung steigert die Nutzbarkeit des Programms. Das UI führt den Benutzer durch die Konfiguration, zeigt den Simulationsfortschritt in Echtzeit und stellt die Ergebnisse strukturiert dar.

- **Konfigurationspersistenz**: Ohne Persistenz müsste der Benutzer bei jedem Programmstart alle Parameter erneut eingeben. Durch das Speichern der Konfiguration in einer Datei werden häufig verwendete Szenarien direkt beim nächsten Start geladen, was den Workflow bei wiederholter Nutzung erheblich beschleunigt.

---

## 4. Gab es Schwierigkeiten bei der Zusammenarbeit?

### Merge-Konflikte / überflüssige Arbeiten durch fehlende Absprache

Vereinzelt haben wir begonnen, an einem Bereich / einem Arbeitspaket / einer Funktion zu arbeiten, ohne uns vorher einen vollständigen Überblick über den aktuellen Arbeitsstand zu verschaffen beziehungsweise uns untereinenander abzustimmen. Das führte zu:

- Doppelt vorgenommenen Änderungen
- Arbeit auf veralteter Codebasis, durch parallele Änderungen an zusammenhängender Logik
- Unit-Tests die auf einer veralteten Funktions-Logik basieren
- Merge-Konflikten oder nachträglichen nötigen Anpassungen

**Maßnahme**: Durch konsequentere Nutzung des Kanban-Boards und der Branches wurde dieses Problem im Laufe des Projekts deutlich reduziert.

### Anfängliche Unsicherheiten im Workflow

Zu Beginn gab es kleinere Unsicherheiten beim Mergen von Branches (main wurde in ein working Branch gemerged statt umgekehrt oder veraltete lokale Version eines working Branches wurde gepushed anstelle des aktuellen) und beim korrekten Befüllen des Kanban-Boards. Diese haben sich jedoch im Verlauf des Projekts gelegt, sodass eine effiziente und gleichmäßige Arbeitsstruktur entstand.

### Plattformunterschiede

Das Team arbeitete auf unterschiedlichen Betriebssystemen (Linux, MacOS, Windows). Dies stellte jedoch kein Problem dar. Wir haben das Programm jederzeit so gehalten, dass es auf allen Plattformen kompillierbar war. Durch den Import von unter Linux und MacOS nativen Libarys haben wir das Projekt auch für Windows laufbar gemacht und durch plattformabhängige Flags / Includes haben wir das Programm so gestalte, dass keine Anpassungen notwendig waren.

---

## 5. Was ist einfach gefallen bzw. sehr gut gelungen?

- **Gemeinsame Planungsphase**: Das frühe gemeinsame Festlegen von Anforderungen, Architektur und Funktionssignaturen hat eine reibungslose parallele Entwicklung ermöglicht.

- **Pseudocode-Ansatz**: Die Logik konnte schnell gemeinsam erarbeitet werden. Der Pseudocode stellte eine solide Grundlage für die endgültige Implementierung der einzelnen Funktionen dar.

- **GitHub-Workflow**: Feature-Branches und Pull Requests haben für klare Verantwortlichkeiten und eine gute Nachvollziehbarkeit der Änderungen gesorgt.

- **Frühzeitiges Testen**: Da Unit-Tests bereits früh eingebunden werden konnten, wurden Fehler frühzeitig entdeckt und nicht erst bei der finalen Integration.

- **Gleichmäßige Kompetenzverteilung**: Da alle Teammitglieder mit vergleichbaren Vorkenntnissen gestartet sind, konnte die Arbeit fair aufgeteilt werden, ohne dass einzelne Personen dauerhaft überlastet wurden.

- **Qualität des Endprodukts**: Durch die bewussten Erweiterungen über die Aufgabenstellung hinaus ist ein Programm entstanden, auf das wir als Team sehr stolz sind.