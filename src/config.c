#include <curses.h>
#include <string.h>

typedef struct {
    float        rel_occupancy_percent;
    float        avg_waiting_time;
    unsigned int step_longest_queue;
    unsigned int step_highest_occupancy;
    float        time_full_occupancy_percent;
    float        revenue;
    unsigned int peak_queue_length;
    float        cars_queued_percent;
} SimStats;

SimStats dummy = {
    .rel_occupancy_percent        = 64.7f,
    .avg_waiting_time             = 3.2f,
    .step_longest_queue           = 38,
    .step_highest_occupancy       = 29,
    .time_full_occupancy_percent  = 12.5f,
    .revenue                      = 4821.50f,
    .peak_queue_length            = 14,
    .cars_queued_percent          = 8.3f,
};

void draw_hline(WINDOW *win, int y, int color_pair) {
    int w = getmaxx(win);
    wattron(win, COLOR_PAIR(color_pair) | A_BOLD);
    mvwhline(win, y, 1, ACS_HLINE, w - 2);
    mvwaddch(win, y, 0,     ACS_LTEE);
    mvwaddch(win, y, w - 1, ACS_RTEE);
    wattroff(win, COLOR_PAIR(color_pair) | A_BOLD);
}

void stat_row(WINDOW *win, int y, int label_pair, int val_pair,
              const char *label, const char *val) {
    wattron(win, COLOR_PAIR(label_pair));
    mvwprintw(win, y, 2, "%-26s:", label);
    wattroff(win, COLOR_PAIR(label_pair));
    wattron(win, COLOR_PAIR(val_pair) | A_BOLD);
    mvwprintw(win, y, 30, "%s", val);
    wattroff(win, COLOR_PAIR(val_pair) | A_BOLD);
}

void draw_bar(WINDOW *win, int y, float percent, int filled_pair, int empty_pair) {
    int w      = getmaxx(win);
    int bar_w  = w - 6;
    int filled = (int)(percent / 100.0f * bar_w);

    mvwaddch(win, y, 2, '[');
    wattron(win, COLOR_PAIR(filled_pair) | A_BOLD);
    for (int i = 0; i < filled; i++)     waddch(win, '|');
    wattroff(win, COLOR_PAIR(filled_pair) | A_BOLD);
    wattron(win, COLOR_PAIR(empty_pair));
    for (int i = filled; i < bar_w; i++) waddch(win, '-');
    wattroff(win, COLOR_PAIR(empty_pair));
    waddch(win, ']');
}

void section_header(WINDOW *win, int y, const char *title) {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(win, y, 2, "%s", title);
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
}

void draw_stats(WINDOW *win, SimStats *s) {
    werase(win);

    int w = getmaxx(win);

    wattron(win, COLOR_PAIR(1) | A_BOLD);
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(1) | A_BOLD);


    const char *title = "PARKING GARAGE - SIMULATION RESULTS";
    wattron(win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, 1, (w - (int)strlen(title)) / 2, "%s", title);
    wattroff(win, COLOR_PAIR(2) | A_BOLD);
    draw_hline(win, 2, 1);

    char buf[32];


    section_header(win, 3, "OCCUPANCY");

    snprintf(buf, sizeof(buf), "%.1f%%", s->rel_occupancy_percent);
    stat_row(win, 4, 3, 4, "Relative Occupancy",        buf);

    snprintf(buf, sizeof(buf), "%.1f%%", s->time_full_occupancy_percent);
    stat_row(win, 5, 3, 4, "Time at Full Occupancy",    buf);

    snprintf(buf, sizeof(buf), "Step %u", s->step_highest_occupancy);
    stat_row(win, 6, 3, 5, "Highest Occupancy at Step", buf);

    draw_bar(win, 7, s->rel_occupancy_percent, 5, 3);
    draw_hline(win, 8, 1);


    section_header(win, 9, "QUEUE");

    snprintf(buf, sizeof(buf), "%.2f steps", s->avg_waiting_time);
    stat_row(win, 16, 3, 4, "Avg Waiting Time",         buf);

    snprintf(buf, sizeof(buf), "%u cars", s->peak_queue_length);
    stat_row(win, 10, 3, 4, "Peak Queue Length",        buf);

    snprintf(buf, sizeof(buf), "Step %u", s->step_longest_queue);
    stat_row(win, 11, 3, 5, "Longest Queue at Step",    buf);

    snprintf(buf, sizeof(buf), "%.1f%%", s->cars_queued_percent);
    stat_row(win, 12, 3, 4, "Cars Queued",              buf);


    section_header(win, 15, "PERFORMANCE");

    snprintf(buf, sizeof(buf), "EUR %.2f", s->revenue);
    stat_row(win, 17, 3, 6, "Total Revenue",            buf);

    draw_hline(win, 18, 1);

    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 19, 2, "Press any key to exit...");
    wattroff(win, COLOR_PAIR(3));

    wrefresh(win);
}

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    init_pair(1, COLOR_CYAN,   COLOR_BLACK); // borders & section headers
    init_pair(2, COLOR_WHITE,  COLOR_BLACK); // title
    init_pair(3, COLOR_WHITE,  COLOR_BLACK); // labels
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // normal values
    init_pair(5, COLOR_RED,    COLOR_BLACK); // peak/warning values
    init_pair(6, COLOR_GREEN,  COLOR_BLACK); // positive values

    int sh, sw;
    getmaxyx(stdscr, sh, sw);

    int win_h = 21;
    int win_w = 52;
    WINDOW *win = newwin(win_h, win_w, (sh - win_h) / 2, (sw - win_w) / 2);

    draw_stats(win, &dummy);
    wgetch(win);

    delwin(win);
    endwin();
    return 0;
}