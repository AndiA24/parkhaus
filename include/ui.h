/**
 * @file ui.h
 * @brief User interface processing.
 *
 * Declares functions for rendering the terminal UI, including the
 * welcome screen, configuration menu, and results display.
 */

#ifndef UI_H
#define UI_H

#include "stats.h"
#include "config.h"

/**
 * @brief Initializes the curses environment and creates the main window.
 *
 * Sets up ncurses/pdcurses, creates a centered WIN_HEIGHT×WIN_WIDTH window,
 * enables keypad input, and initializes the four color pairs used throughout the UI.
 */
void initialize_ui();

/**
 * @brief Tears down the curses environment and destroys the main window.
 *
 * Deletes the window created by initialize_ui() and restores the terminal.
 */
void end();

/**
 * @brief Displays the welcome screen and handles its input loop.
 *
 * Renders the welcome screen and waits for user input.
 * - Press `Enter` to start the simulation.
 * - Press `S` to open the settings menu.
 * - Press `Q` to quit the application.
 *
 * @param[in] ptr_config Pointer to the simulation configuration struct.
 */
void show_welcome(SimConfig *ptr_config);

/**
 * @brief Renders the welcome screen to the window.
 *
 * Draws the title, project description, author credits, and keyboard hint footer.
 * Does not handle any input — call show_welcome() for the full interactive loop.
 *
 * @param[in] ptr_config Pointer to the simulation configuration struct.
 */
void render_welcome();

/**
 * @brief Displays the settings menu and handles its input loop.
 *
 * Renders all configurable simulation parameters and allows the user
 * to modify them by pressing the corresponding number key (1–9).
 * Each key opens a prompt to enter a new value for that setting.
 * - Press `ESC`, `Enter`, or `Q` to return to the welcome screen.
 *
 * @param[in,out] ptr_config Pointer to the simulation configuration struct.
 */
void show_settings(SimConfig *ptr_config);

/**
 * @brief Renders the current simulation settings to the screen.
 *
 * Prints all configuration fields and their current values in a formatted
 * list, including deck count, spots per deck, occupancy, durations,
 * arrival probability, and RNG seed.
 *
 * @param[in] ptr_config Pointer to the simulation configuration struct to display.
 */
void render_settings(SimConfig *ptr_config);

/**
 * @brief Prompts the user to enter an unsigned integer within a given range.
 *
 * Clears the prompt area, displays the label and accepted range, reads one line
 * of input, and validates it. On invalid input an error message is shown and the
 * user must press a key before control returns. On valid input *ptr_value is updated.
 *
 * @param[in]  ptr_label  Human-readable name of the field, shown in the prompt.
 * @param[in,out] ptr_value  Pointer to the unsigned int that will be updated.
 * @param[in]  min        Minimum accepted value (inclusive).
 * @param[in]  max        Maximum accepted value (inclusive).
 */
void prompt_uint(char *ptr_label, unsigned int *ptr_value, unsigned int min, unsigned int max);

/**
 * @brief Prompts the user to enter a non-empty string.
 *
 * Clears the prompt area, displays the label, reads up to size-1 characters,
 * and validates that the input is non-empty. On invalid input an error message
 * is shown and the old value is kept. On valid input ptr_value is updated.
 *
 * @param[in]  label      Human-readable name of the field, shown in the prompt.
 * @param[in,out] ptr_value  Destination buffer that will receive the new string.
 * @param[in]  size       Size of the destination buffer in bytes.
 */
void prompt_string(char *label, char *ptr_value, int size);

/**
 * @brief Displays a single message and optionally terminates the program.
 *
 * Clears the window, prints ptr_msg at the given row and color, then waits for
 * the user to press Enter. If kill is non-zero, pressing Enter calls end() and
 * quit(), ending the process.
 *
 * @param[in]     col        Row at which to print the message.
 * @param[in]     ptr_msg    Message string to display.
 * @param[in]     color      Color pair index to use for the message. 1 = green, 2 = red, 3 = white 4 = cyan
 * @param[in]     kill       If non-zero, quit the program after the user confirms.
 * @param[in] ptr_config Pointer to the simulation configuration (passed to quit()).
 */
void show_message(int col, const char *ptr_msg, int color, int kill, SimConfig *ptr_config);

/**
 * @brief Displays live statistics for the current simulation time step.
 *
 * Prints per-step metrics including exits, entries, relative occupancy,
 * queue length, free spots, and average remaining parking time.
 * Intended to be called once per simulation step while the simulation is running.
 *
 * @param[in] ptr_stats Pointer to the simulation statistics struct containing
 *                      the current time-step data.
 */
void show_running(SimStats *ptr_stats);

/**
 * @brief Displays the final statistics after the simulation has completed.
 *
 * Prints a summary of all accumulated metrics, including total entries,
 * exits, queue statistics, parking duration totals, peak occupancy, and
 * the steps at which peaks occurred.
 *
 * @param[in] ptr_stats Pointer to the simulation statistics struct containing
 *                      the final aggregated data.
 */
void show_results(SimStats *ptr_stats);

#endif
