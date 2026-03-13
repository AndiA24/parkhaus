#ifndef UTILS_H
#define UTILS_H

#include "config.h"

/**
 * @brief Displays a message to the user.
 *
 * In normal builds, delegates to show_message() to render the message in the
 * PDCurses/ncurses UI and wait for the user to press enter. In unit test builds (UNIT_TEST defined),
 * prints the message to stdout instead.
 *
 * @param col      Column position at which to display the message. 2 should almost always be used.
 * @param ptr_msg  Null-terminated string containing the message to display.
 * @param color    Color attribute index to use when rendering the message. 1: green, 2: red, 3: white, 4: cyan
 * @param kill     If non-zero, prompts the user to exit the program after the
 *                 message and terminates on confirmation; otherwise prompts to
 *                 continue.
 * @param ptr_config Pointer to the simulation configuration, used when
 *                   terminating the program (may be NULL if kill is 0).
 */
void output(int col, const char *ptr_msg, int color, int kill, SimConfig *ptr_config);

/**
 * @brief Saves the simulation configuration and terminates the program.
 *
 * @param ptr_config Pointer to the simulation configuration to save before exit.
 */
void quit(SimConfig *ptr_config);


#endif