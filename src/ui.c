#include "../include/ui.h"
#include "../include/config.h"
#include "../include/stats.h"
#include "../include/utils.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
//decide if we are on Windows or Linux/MacOS. Windows needs pdcurses for support. The others have ncurses built in.
#ifdef _WIN32
    #include "../pdcurses/curses.h"
    #include <windows.h>
#else
    #include <ncurses.h>
#endif


static WINDOW *ptr_win;


static void print_col(int y, int x, int pair, int attrs, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    wattron(ptr_win, COLOR_PAIR(pair) | attrs);
    wmove(ptr_win, y, x);
    vw_printw(ptr_win, fmt, args);
    wattroff(ptr_win, COLOR_PAIR(pair) | attrs);
    va_end(args);
}

static void draw_hline(int y) {
    int w = getmaxx(ptr_win);
    wattron(ptr_win, COLOR_PAIR(4) | A_BOLD);
    mvwhline(ptr_win, y, 1, ACS_HLINE, w - 2);
    mvwaddch(ptr_win, y, 0,     ACS_LTEE);
    mvwaddch(ptr_win, y, w - 1, ACS_RTEE);
    wattroff(ptr_win, COLOR_PAIR(4) | A_BOLD);
}

void prompt_uint(char *ptr_label, unsigned int *ptr_value, int min, int max) {
    char buf[16] = {0};
    //clear input area to make sure
    print_col(17, 2, 3, 0, "%s (%u-%u):", ptr_label, min, max);
    print_col(18, 2, 3, 0, "> ");
    wrefresh(ptr_win);

    echo();
    curs_set(1);
    wmove(ptr_win, 18, 4);
    wgetnstr(ptr_win, buf, sizeof(buf) - 1); //-1 to leave room for null terminator
    noecho();
    curs_set(0);

    char *ptr_end;
    unsigned long val = strtoul(buf, &ptr_end, 10);
    if(ptr_end == buf || *ptr_end != '\0' || val < min || val > max) {
        print_col(19, 2, 2, 0, "Ungueltig! Der erlaubte Bereich ist: %u-%u", min, max);
        wrefresh(ptr_win);
        wgetch(ptr_win);
    }
    else {
        *ptr_value = val;
    }
}

void prompt_string(char *label, char *ptr_value, int size) {
    char tmp[70] = {0};
    //clear input line here as well
    print_col(17, 2, 3, 0, "%s:", label);
    print_col(18, 2, 3, 0, "> ");
    wrefresh(ptr_win);

    echo();
    curs_set(1);
    wmove(ptr_win, 18, 4);
    wgetnstr(ptr_win, tmp, size-1);
    noecho();
    curs_set(0);

    if(strlen(tmp) == 0) {
        print_col(19, 2, 2, 0, "Ungueltig! Behalte alten Wert bei.");
        wrefresh(ptr_win);
        wgetch(ptr_win);
    }
    else {
        strncpy(ptr_value, tmp, size - 1);
        ptr_value[size - 1] = '\0';
    }
}

void render_welcome(SimConfig *ptr_config) {
    werase(ptr_win);

    int w = getmaxx(ptr_win);

    wattron(ptr_win, COLOR_PAIR(4) | A_BOLD);
    box(ptr_win, 0, 0);
    wattroff(ptr_win, COLOR_PAIR(4) | A_BOLD);

    const char *title = "PARKING GARAGE SIMULATOR";
    print_col(1, (w - (int)strlen(title)) / 2, 4, A_BOLD, "%s", title);

    draw_hline(2);

    print_col(4, 2, 3, 0, "Eine Simulation eines Parkhauses. Entwickelt");
    print_col(5, 2, 3, 0, "im Rahmen eines Hochschulprojekts, um das");
    print_col(6, 2, 3, 0, "Belegungsverhalten, Warteschlangen und die");
    print_col(7, 2, 3, 0, "Auslastung eines Parkhauses zu modellieren.");

    draw_hline(9);

    print_col(10, 2, 4, A_BOLD, "KONFIGURATION");

    unsigned int total = ptr_config->num_decks * ptr_config->spots_per_deck;

    print_col(11,  2, 3, 0,      "Etagen:");
    print_col(11, 10, 1, A_BOLD, "%-4u",   ptr_config->num_decks);
    print_col(11, 15, 3, 0,      "Stellpl./Etage:");
    print_col(11, 31, 1, A_BOLD, "%-4u",   ptr_config->spots_per_deck);
    print_col(11, 36, 3, 0,      "Gesamt:");
    print_col(11, 44, 1, A_BOLD, "%u",     total);

    print_col(12,  2, 3, 0,      "Dauer:");
    print_col(12,  9, 1, A_BOLD, "%u Schritte", ptr_config->sim_duration_steps);
    print_col(12, 30, 3, 0,      "Ankunft:");
    print_col(12, 39, 1, A_BOLD, "%u%%",   ptr_config->arrival_probability_percent);

    print_col(13,  2, 3, 0,      "Parkzeit:");
    print_col(13, 12, 1, A_BOLD, "%u-%u Schritte", ptr_config->min_parking_duration_steps,
                                                    ptr_config->max_parking_duration_steps);
    print_col(13, 33, 3, 0,      "Seed:");
    print_col(13, 39, 1, A_BOLD, "%u",     ptr_config->seed);

    draw_hline(15);

    print_col(16,  2, 4, A_BOLD, "[ENTER]");
    print_col(16, 10, 3, 0,      "Simulation starten");
    print_col(17,  2, 4, A_BOLD, "[S]");
    print_col(17, 10, 3, 0,      "Einstellungen");
    print_col(18,  2, 4, A_BOLD, "[Q]");
    print_col(18, 10, 3, 0,      "Beenden");

    wrefresh(ptr_win);
}

void render_settings(SimConfig *ptr_config) {
    werase(ptr_win);
    int width = getmaxx(ptr_win);

    wattron(ptr_win, COLOR_PAIR(4) | A_BOLD);
    box(ptr_win, 0, 0);
    wattroff(ptr_win, COLOR_PAIR(4) | A_BOLD);

    print_col(1, (width - 13) / 2, 4, A_BOLD, "%s", "EINSTELLUNGEN");

    draw_hline(2);

    print_col(3,  2, 4, A_BOLD, "[1]"); 
    print_col(3,  6, 3, 0, "Etagen:");          
    print_col(3,  28, 1, A_BOLD, "%u", ptr_config->num_decks);

    print_col(4,  2, 4, A_BOLD, "[2]"); 
    print_col(4,  6, 3, 0, "Stellpl./Etage:");  
    print_col(4,  28, 1, A_BOLD, "%u", ptr_config->spots_per_deck);

    print_col(5,  2, 4, A_BOLD, "[3]"); 
    print_col(5,  6, 3, 0, "Startbelegung:");   
    print_col(5,  28, 1, A_BOLD, "%u", ptr_config->initial_occupancy);

    print_col(6,  2, 4, A_BOLD, "[4]"); 
    print_col(6,  6, 3, 0, "Max. Parkdauer:");  
    print_col(6,  28, 1, A_BOLD, "%u", ptr_config->max_parking_duration_steps);

    print_col(7,  2, 4, A_BOLD, "[5]"); 
    print_col(7,  6, 3, 0, "Min. Parkdauer:");  
    print_col(7,  28, 1, A_BOLD, "%u", ptr_config->min_parking_duration_steps);

    print_col(8,  2, 4, A_BOLD, "[6]"); 
    print_col(8,  6, 3, 0, "Sim.-Dauer:");      
    print_col(8,  28, 1, A_BOLD, "%u", ptr_config->sim_duration_steps);

    print_col(9,  2, 4, A_BOLD, "[7]"); 
    print_col(9,  6, 3, 0, "Ankunftswahr.:");   
    print_col(9,  28, 1, A_BOLD, "%u%%", ptr_config->arrival_probability_percent);

    print_col(10, 2, 4, A_BOLD, "[8]"); 
    print_col(10, 6, 3, 0, "Seed:");            
    print_col(10, 28, 1, A_BOLD, "%u", ptr_config->seed);

    print_col(11, 2, 4, A_BOLD, "[9]"); 
    print_col(11, 6, 3, 0, "Ausgabedatei:");
    print_col(11, 28, 1, A_BOLD, "%s", ptr_config->output_file_name);   
    
    draw_hline(13);

    print_col(14, 2, 3, 0, "Zahl druecken um den entsprechenden Wert zu bearbeiten");
    print_col(15, 2, 4, A_BOLD, "[Q]");
    print_col(15, 6, 3, 0, "/");
    print_col(15, 6, 3, 0, "[ENTER]");
    print_col(15, 16, 3, 0, "Zurueck");
}

void show_settings(SimConfig *ptr_config) {
    render_settings(ptr_config);
    int active = 1;
    while(active) {
        int key = wgetch(ptr_win);
        switch (key) {
            case '1':
                prompt_uint("Anzahl der Etagen des Parkhauses", &ptr_config->num_decks, 1, 99);
                render_settings(ptr_config);
                break;
            case '2':
                prompt_uint("Anzahl der Stellplätze pro Etage", &ptr_config->spots_per_deck, 1, 999);
                render_settings(ptr_config);
                break;
            case '3':
                prompt_uint("Anzahl der Fahrzeuge im Parkhaus zum Beginn der Simulation", &ptr_config->initial_occupancy, 0, ptr_config->num_decks*ptr_config->spots_per_deck);
                render_settings(ptr_config);
                break;
            case '4':
                prompt_uint("Maximal Parkdauer eines Fahrzeuges", &ptr_config->max_parking_duration_steps, 1, ptr_config->sim_duration_steps);
                render_settings(ptr_config);
                break;
            case '5':
                prompt_uint("Minimale Parkdauer eines Fahrzeuges", &ptr_config->min_parking_duration_steps, 1, ptr_config->max_parking_duration_steps);
                render_settings(ptr_config);
                break;
            case '6':
                prompt_uint("Dauer der Simulation in Schritten", &ptr_config->sim_duration_steps, 1, UINT_MAX);
                render_settings(ptr_config);
                break;
            case '7':
                prompt_uint("Wahrscheinlichkeit für das Ankommen eines Fahrzeuges pro Schritt", &ptr_config->arrival_probability_percent, 1, 100);
                render_settings(ptr_config);
                break;
            case '8':
                prompt_uint("RNG Seed der Simulation", &ptr_config->seed, 0, UINT_MAX);
                render_settings(ptr_config);
                break;
            case '9':
                prompt_string("Name der Ausgabedatei", ptr_config->output_file_name, sizeof(ptr_config->output_file_name));
                render_settings(ptr_config);
                break;
            case 'q':
            case 'Q':
            case '\n':
            case KEY_ENTER:
            case 27: //Ascii code for ESC key. ESC isn't defined anywhere...
                active = 0;
                break;
            default:
                // we should probably throw an error if we ever hit the default since that shouldn't happen.
                break;
        }
    }
}

void show_welcome(SimConfig *ptr_config) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int win_height = 22;
    int win_width = 72;
    int sh, sw;
    getmaxyx(stdscr, sh, sw);
    ptr_win = newwin(win_height, win_width, (sh - win_height) / 2, (sw - win_width) / 2);
    keypad(ptr_win, TRUE);
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);     //good results (no queue, high but not full occupancy)
    init_pair(2, COLOR_RED, COLOR_BLACK);       //bad results (full car park, long queue)
    init_pair(3, COLOR_WHITE, COLOR_BLACK);     //neutral info text
    init_pair(4, COLOR_CYAN, COLOR_BLACK);      //boxes and borders

    int active = 1;
    render_welcome(ptr_config);
    while (active) {
        int key = wgetch(ptr_win);
        switch (key) {
        case 'q':
        case 'Q':
            active = 0;
            //quit(ptr_config);
            break;
        case 's':
        case 'S':
            show_settings(ptr_config);
            render_welcome(ptr_config);
            break;
        case '\n':
        case KEY_ENTER:
            active = 0;
            break;
        default:
            break;
        }
    }

    delwin(ptr_win);
    endwin();
}

int main() {
    SimConfig config = {
        .num_decks = 3,
        .spots_per_deck = 50,
        .initial_occupancy = 10,
        .max_parking_duration_steps = 100,
        .min_parking_duration_steps = 10,
        .sim_duration_steps = 500,
        .arrival_probability_percent = 40,
        .seed = 42,
        .config_file_name = "parkhaus.cfg",
        .output_file_name = "output.csv"
    };
    show_welcome(&config);
    return 0;
}

/*

Dies ist die vorläufige Version des UI. Allerdings kann sich hier noch einiges ändern. In ersten Tests mit der Library habe ich bereits festgestellt,
dass noch weitere kleine Hilfsfunktionen gebraucht werden um das UI effizient zu erzeugen (z.B. zur Darstellung von Prozentbalken). Zusätzlich ist in diesem 
Pseudocode noch nicht richtig dargestellt, wie der User Input ermittelt wird (Keyboard Shortcuts, Einstellungen eingeben). Außerdem sind auch Dinge wie 
die Reihenfolge der Daten oder die genutzten Tasten für die Funktionen noch nicht final. Alles soll eine erste Richtung darstellen wird aber beim 
Programmieren des tatsächlichen UI vermutlich noch deutlich verändert werden.




FUNCTION show_welcome(Struct *ptr_SimConfig)
    active <- true
    CALL render_welcome()

    WHILE active
        key <- CALL get_input()
        
        IF key = 'Q' THEN
            CALL quit(ptr_SimConfig)
        ELSE IF key = 'S' THEN
            CALL show_settings(ptr_SimConfig)
        ELSE IF key = 'Enter' THEN
            active <- false //main will start simulation
        END IF
    END WHILE
END FUNCTION


FUNCTION show_settings(Struct *ptr_SimConfig)
    active <- true
    CALL render_settings(ptr_SimConfig)

    WHILE active
        key <- CALL get_input()
        
        IF key = '1' THEN
            ptr_SimConfig->num_decks <- CALL prompt_input("Number of Decks", ptr_SimConfig->num_decks, 1, 99)
        ELSE IF key = '2' THEN
            ptr_SimConfig->spots_per_deck <- CALL prompt_input("Spots per Deck", ptr_SimConfig->spots_per_deck, 1, 999)
        ELSE IF key = '3' THEN
            ptr_SimConfig->initial_occupancy <- CALL prompt_input("Initial Occupancy", ptr_SimConfig->initial_occupancy, 0, 999)
        ELSE IF key = '4' THEN
            ptr_SimConfig->max_parking_duration_steps <- CALL prompt_input("Max Parking Duration", ptr_SimConfig->max_parking_duration_steps, 1, 9999)
        ELSE IF key = '5' THEN
            ptr_SimConfig->min_parking_duration_steps <- CALL prompt_input("Min Parking Duration", ptr_SimConfig->min_parking_duration_steps, 1, 9999)
        ELSE IF key = '6' THEN
            ptr_SimConfig->sim_duration_steps <- CALL prompt_input("Simulation Duration", ptr_SimConfig->sim_duration_steps, 1, 9999)
        ELSE IF key = '7' THEN
            ptr_SimConfig->arrival_probability_percent <- CALL prompt_input("Arrival Probability %", ptr_SimConfig->arrival_probability_percent, 0, 100)
        ELSE IF key = '8' THEN
            ptr_SimConfig->seed <- CALL prompt_input("RNG Seed", ptr_SimConfig->seed, 0, 9999)
        ELSE IF key = '9' THEN
            ptr_SimConfig->config_file_name <- CALL prompt_input("The file name to store the config inside of", ptr_SimConfig->output_file_name)
        ELSE IF key = 'ESC' || 'Enter' || 'Q' THEN
            active <- false
        END IF
    END WHILE
END FUNCTION


FUNCTION prompt_input(name, current_value, min, max)

    valid <- false
    CALL render_prompt(name, current_value)

    WHILE NOT valid
        input <- CALL get_text_input()
        
        IF current_value is not config_file_name AND input is a valid number AND input >= min AND input <= max THEN
            valid <- true
        ELSE IF current_value is config_file_name AND input is a valid string AND input length < array length THEN
            valid <- true
        ELSE
            CALL print("Please enter a correct value between min and max")
        END IF
    END WHILE
    
    RETURN input
END FUNCTION

FUNCTION render_settings(Struct *ptr_SimConfig)
    CALL print("Number of Decks", SimConfig->num_decks)
    CALL print("Spots per Deck", SimConfig->spots_per_deck)
    CALL print("Initial Occupancy", SimConfig->initial_occupancy)
    CALL print("Max Parking Duration", SimConfig->max_parking_duration_steps)
    CALL print("Min Parking Duration", SimConfig->min_parking_duration_steps)
    CALL print("Simulation Duration", SimConfig->sim_duration_steps)
    CALL print("Arrival Probability %", SimConfig->arrival_probability_percent)
    CALL print("RNG Seed", SimConfig->seed)
END FUNCTION

FUNCTION show_running(Struct ptr_SimStats)
    CALL print("Exists this time step", ptr_SimStats->temp_exits)
    CALL print("entries this time step", ptr_SimStats->temp_entries)
    CALL print("Relative Occupancy this time step", ptr_SimStats->temp_rel_occupancy_precent)
    CALL print("Current queue length", ptr_SimStats->temp_queue_length)
    CALL print("Free spots this timestep", ptr_SimStats->temp_free_spots)
    CALL print("Average remaining parking duration of vehicles", ptr_SimStats->temp_time_left)
END FUNCTION

FUNCTION show_results(Struct ptr_SimStats)
    results <- true     
    CALL print("Total cars that left the car park", ptr_SimStats->total_exits)
    CALL print("Total cars that entered the car park", ptr_SimStats->total_entries)
    CALL print("Total cars that had to wait in queue", ptr_SimStats->total_queued)
    CALL print("Sum of all queue steps", ptr_SimStats->total_queue_time)
    CALL print("Steps cars spent in the car park", ptr_SimStats->total_parking_time)
    CALL print("Steps the parking garage was full", ptr_SimStats->time_full_occupancy)
    CALL print("Peak queue length during the simulation", ptr_SimStats->peak_queue_length)
    CALL print("Step at which the queue was the longest", ptr_SimStats->step_longest_queue)
    CALL print("Peak relative occupany during the simulation", ptr_SimStats->peak_rel_occupancy)
    CALL print("Step at which the highest occupancy occured", ptr_SimStats->step_highest_occupancy)
    IF ptr_SimStats->total_queued = 0
        CALL print("Avarage wait time in queue", ptr_SimStats->total_queued)
    ELSE
        CALL print("Avarage wait time in queue", ptr_SimStats->total_queue_time/ptr_SimStats->total_queued)
    END IF
    IF ptr_SimStats->total_queued = 0
        CALL print("Percentage of vehicles that had to wait", (total_queued * 100) / total_entries)
    ELSE
        CALL print("Percentage of vehicles that had to wait", ptr_SimStats->total_entries/ptr_SimStats->total_queued)
    END IF
    CALL print("Average occupancy throughout the entire simulation", ptr_SimStats->avg_rel_occupancy)
    WHILE results
        key <- CALL get_input()
        IF key = 'Enter' OR 'Q' OR 'ESC' THEN
            restults <- false
        END IF
    END WHILE
END FUNCTION


*/