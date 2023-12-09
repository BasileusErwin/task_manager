#ifndef TASK_MANAGER_CLI_H
#define TASK_MANAGER_CLI_H

#include <common.h>
#include <console.h>
#include <utils.h>
#include <stdio.h>
#include <task.h>

#define VERSION_NUMBER "0.0.1"

/**
 * @brief SubCommand enum
 *
 * This enum is used to represent the subcommands
 * */
typedef enum {
  ADD,
  REMOVE,
  LIST,
  HELP,
} SubCommand;

DEFINE_ENUM_MAP(SubCommand);
DEFINE_FUNCTION_ENUM_PARSER(toSubCommand, SubCommand);
DEFINE_FUNCTION_ENUM_TO_STRING(fromSubCommand, SubCommand);

/**
 * Option enum
 * */
typedef enum {
  HELP_OPTION,
  VERSION,
} Option;

DEFINE_ENUM_MAP(Option);
DEFINE_FUNCTION_ENUM_PARSER(toOption, Option);
DEFINE_FUNCTION_ENUM_TO_STRING(fromOption, Option);

void showHelp();
Option getOption(const char *str);
void cli(const int argc, const char **argv);

#endif
