#include <console.h>

/**
 * This function prints an error message.
 * Layout:
 *
 * `{RED BOLD [ERROR] RESET} {message}\n`
 *
 * @param message The message to print
 * */
void printError(const char *message) {
  printf(ANSI_COLOR_RED ANSI_FONT_BOLD "[ERROR] " ANSI_COLOR_RESET "%s\n",
         message);
}

/**
 * This function prints a success message.
 * Layout:
 * `{GREEN BOLD [SUCCESS] RESET} {message}\n`
 *
 * @param message The message to print
 * */
void printSuccess(const char *message) {
  printf(ANSI_COLOR_GREEN ANSI_FONT_BOLD "[SUCCESS] " ANSI_COLOR_RESET "%s\n",
         message);
}

/**
 * This function prints a warning message.
 * Layout:
 * `{YELLOW BOLD [WARNING] RESET} {message}\n`
 *
 * @param message The message to print
 * */
void printWarning(const char *message) {
  printf(ANSI_COLOR_YELLOW ANSI_FONT_BOLD "[WARNING] " ANSI_COLOR_RESET "%s\n",
         message);
}

/**
 * This function prints an info message.
 * Layout:
 * `{BLUE BOLD [INFO] RESET} {message}\n`
 *
 * @param message The message to print
 * */
void printInfo(const char *message) {
  printf(ANSI_COLOR_BLUE ANSI_FONT_BOLD "[INFO] " ANSI_COLOR_RESET
                                        "%s" ANSI_COLOR_RESET "\n",
         message);
}

/**
 * This function prints a debug message.
 * Restore the default color and font after printing the message.
 *
 * Layout:
 *  `{COLOR} {FONT} {message} {RESET}`
 *
 * @param message The message to print
 * @param color The color of the message (see ANSI_COLOR_* macros)
 * @param font The font of the message (see ANSI_FONT_* macros)
 * */
void print(const char *message, const char *color, const char *font) {
  printf("%s%s%s" ANSI_COLOR_RESET, color, font, message);
}
