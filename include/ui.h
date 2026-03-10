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
 * @brief Displays the welcome screen and handles its input loop.
 *
 * Renders the welcome screen and waits for user input.
 * - Press `Enter` to start the simulation.
 * - Press `S` to open the settings menu.
 * - Press `Q` to quit the application.
 *
 * @param[in,out] ptr_config Pointer to the simulation configuration struct.
 */
void show_welcome(SimConfig *ptr_config);

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
 * @brief Prompts the user to enter a new value for a configuration field.
 *
 * Displays the field name and its current value, then repeatedly reads
 * user input until a valid value is entered. For numeric fields the input
 * must be a valid number within [@p min, @p max]. For string fields (i.e.
 * the config file name) the input must be a valid string whose length fits
 * within the destination buffer.
 *
 * @param text              Human-readable name of the field being edited,
 *                          shown in the prompt.
 * @param[in,out] ptr_current_value Pointer to the field that will be updated with
 *                          the validated input. The type is inferred from
 *                          context (numeric or string).
 * @param[in] min               Minimum accepted value (inclusive) for numeric fields.
 * @param[in] max               Maximum accepted value (inclusive) for numeric fields.
 */
void prompt_input(char text[], void *ptr_current_value, long min, long max);

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
 * @brief Displays live statistics for the current simulation time step.
 *
 * Prints per-step metrics including exits, entries, relative occupancy,
 * and current queue length. Intended to be called once per simulation step
 * while the simulation is running.
 *
 * @param ptr_stats Pointer to the simulation statistics struct containing
 *                  the current time-step data.
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
 *                  the final aggregated data.
 */
void show_results(SimStats *ptr_stats);

void render_welcome();

#endif