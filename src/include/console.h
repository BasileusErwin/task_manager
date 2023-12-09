#ifndef TASK_MAMANGER_CONSOLE_H
#define TASK_MAMANGER_CONSOLE_H

#include <common.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_FONT_BOLD "\x1b[1m"
#define ANSI_FONT_UNDERLINE "\x1b[4m"

void printError(const char *message);
void printSuccess(const char *message);
void printWarning(const char *message);
void printInfo(const char *message);
void printDebug(const char *message);
void print(const char *message, const char *color, const char *font);

#endif
