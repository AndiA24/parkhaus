#include <curses.h>
#include <string.h>

typedef struct {
    unsigned int total_exits;
    unsigned int total_entrys;
    unsigned int total_queued;
    unsigned int total_queue_time;
    unsigned int total_parking_time;
    unsigned int time_full_occupancy;
    unsigned int peak_queue_length;
    unsigned int step_longest_queue;
    float        peak_rel_occupancy;
    unsigned int step_highest_occupancy;
} SimStats;

SimStats dummy = {
    .total_exits             = 210,
    .total_entrys            = 230,
    .total_queued            = 47,
    .total_queue_time        = 150,
    .total_parking_time      = 8400,
    .time_full_occupancy     = 63,
    .peak_queue_length       = 14,
    .step_longest_queue      = 38,
    .peak_rel_occupancy      = 64.7f,
    .step_highest_occupancy  = 29,
};

void draw_hline(WINDOW *p_win, int y, int color_pair) {
    int w = getmaxx(p_win);
    wattron(p_win, COLOR_PAIR(color_pair) | A_BOLD);
    mvwhline(p_win, y, 1, ACS_HLINE, w - 2);
    mvwaddch(p_win, y, 0,     ACS_LTEE);
    mvwaddch(p_win, y, w - 1, ACS_RTEE);
    wattroff(p_win, COLOR_PAIR(color_pair) | A_BOLD);
}

void stat_row(WINDOW *p_win, int y, int label_pair, int val_pair,
              const char *label, const char *val) {
    wattron(p_win, COLOR_PAIR(label_pair));
    mvwprintw(p_win, y, 2, "%-26s:", label);
    wattroff(p_win, COLOR_PAIR(label_pair));
    wattron(p_win, COLOR_PAIR(val_pair) | A_BOLD);
    mvwprintw(p_win, y, 30, "%s", val);
    wattroff(p_win, COLOR_PAIR(val_pair) | A_BOLD);
}

void draw_bar(WINDOW *p_win, int y, float percent, int filled_pair, int empty_pair) {
    int w      = getmaxx(p_win);
    int bar_w  = w - 6;
    int filled = (int)(percent / 100.0f * bar_w);

    mvwaddch(p_win, y, 2, '[');
    wattron(p_win, COLOR_PAIR(filled_pair) | A_BOLD);
    for (int i = 0; i < filled; i++) {
        waddch(p_win, '|');
    }
    wattroff(p_win, COLOR_PAIR(filled_pair) | A_BOLD);
    wattron(p_win, COLOR_PAIR(empty_pair));
    for (int i = filled; i < bar_w; i++) {
        waddch(p_win, '-');
    }
    wattroff(p_win, COLOR_PAIR(empty_pair));
    waddch(p_win, ']');
}

void section_header(WINDOW *p_win, int y, const char *title) {
    wattron(p_win, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(p_win, y, 2, "%s", title);
    wattroff(p_win, COLOR_PAIR(1) | A_BOLD);
}

void draw_stats(WINDOW *p_win, SimStats *s) {
    werase(p_win);

    int w = getmaxx(p_win);

    wattron(p_win, COLOR_PAIR(1) | A_BOLD);
    box(p_win, 0, 0);
    wattroff(p_win, COLOR_PAIR(1) | A_BOLD);

    const char *title = "PARKING GARAGE - SIMULATION RESULTS";
    wattron(p_win, COLOR_PAIR(2) | A_BOLD);
    mvwprintw(p_win, 1, (w - (int)strlen(title)) / 2, "%s", title);
    wattroff(p_win, COLOR_PAIR(2) | A_BOLD);
    draw_hline(p_win, 2, 1);

    char buf[32];

    section_header(p_win, 3, "TRAFFIC");

    snprintf(buf, sizeof(buf), "%u", s->total_entrys);
    stat_row(p_win, 4, 2, 4, "Total Arrivals", buf);

    snprintf(buf, sizeof(buf), "%u", s->total_exits);
    stat_row(p_win, 5, 2, 4, "Total Exits", buf);

    snprintf(buf, sizeof(buf), "%u", s->total_queued);
    stat_row(p_win, 6, 2, 5, "Total Cars Queued", buf);

    snprintf(buf, sizeof(buf), "%u steps", s->total_queue_time);
    stat_row(p_win, 7, 2, 5, "Total Queue Time", buf);

    snprintf(buf, sizeof(buf), "%u steps", s->total_parking_time);
    stat_row(p_win, 8, 2, 4, "Total Parking Time", buf);

    draw_hline(p_win, 9, 1);

    section_header(p_win, 10, "OCCUPANCY");

    snprintf(buf, sizeof(buf), "%.1f%%", s->peak_rel_occupancy);
    if(s->peak_rel_occupancy < 85.0) {
        stat_row(p_win, 11, 2, 6, "Peak Relative Occupancy", buf);
        draw_bar(p_win, 12, s->peak_rel_occupancy, 6, 2);
    }
    else {
        stat_row(p_win, 11, 2, 5, "Peak Relative Occupancy", buf);
        draw_bar(p_win, 12, s->peak_rel_occupancy, 5, 2);
    }
    

    

    snprintf(buf, sizeof(buf), "Step %u", s->step_highest_occupancy);
    stat_row(p_win, 13, 2, 4, "Peak Occupancy at Step", buf);

    snprintf(buf, sizeof(buf), "%u steps", s->time_full_occupancy);
    stat_row(p_win, 14, 2, 5, "Time at Full Occupancy", buf);

    draw_hline(p_win, 15, 1);

    section_header(p_win, 16, "QUEUE");

    snprintf(buf, sizeof(buf), "%u cars", s->peak_queue_length);
    stat_row(p_win, 17, 2, 4, "Peak Queue Length", buf);

    snprintf(buf, sizeof(buf), "Step %u", s->step_longest_queue);
    stat_row(p_win, 18, 2, 5, "Longest Queue at Step", buf);

    draw_hline(p_win, 19, 1);

    wattron(p_win, COLOR_PAIR(2));
    mvwprintw(p_win, 20, 2, "Press any key to exit...");
    wattroff(p_win, COLOR_PAIR(2));

    wrefresh(p_win);
}

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    init_pair(1, COLOR_CYAN,   COLOR_BLACK); // borders & section headers
    init_pair(2, COLOR_WHITE,  COLOR_BLACK); // title & lables 
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // normal values
    init_pair(5, COLOR_RED,    COLOR_BLACK); // peak/warning values
    init_pair(6, COLOR_GREEN,  COLOR_BLACK); // positive values

    int sh, sw;
    getmaxyx(stdscr, sh, sw);

    int win_h = 22;
    int win_w = 52;
    WINDOW *p_win = newwin(win_h, win_w, (sh - win_h) / 2, (sw - win_w) / 2);

    draw_stats(p_win, &dummy);
    wgetch(p_win);

    delwin(p_win);
    endwin();
    return 0;
}