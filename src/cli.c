#include <cli.h>

const SubCommandMap subCommandMap[] = {
    {"add", ADD},   {"remove", REMOVE}, {"list", LIST},
    {"help", HELP}, {NULL, -1},
};

DEFINE_ENUM_TO_STRING(fromSubCommand, SubCommand, subCommandMap,
                      sizeof(subCommandMap) / sizeof(subCommandMap[0]), "");

DEFINE_ENUM_PARSER(toSubCommand, SubCommand, subCommandMap,
                   sizeof(subCommandMap) / sizeof(subCommandMap[0]), -1);

const OptionMap optionMap[] = {
    {"-h", HELP_OPTION}, {"--help", HELP_OPTION},
    {"-v", VERSION},     {"--version", VERSION},
    {NULL, -1},
};

DEFINE_ENUM_TO_STRING(fromOption, Option, optionMap,
                      sizeof(optionMap) / sizeof(optionMap[0]), "");

DEFINE_ENUM_PARSER(toOption, Option, optionMap,
                   sizeof(optionMap) / sizeof(optionMap[0]), -1);

/**
 * This function prints the help message.
 *
 * Layout:
 * {Command name} {Command Version}
 * {Command description}
 *
 * {Command usage}
 *
 * {Options}
 *
 * {Subcommands}
 **/
void showHelp() {
  print("Task Manager", ANSI_COLOR_GREEN, ANSI_FONT_BOLD);
  print(" Version " VERSION_NUMBER "\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
  print(" A simple task manager\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
  printf("\n");

  print("Usage: task-manager <OPTIONS> <SUBCOMMAND>\n", ANSI_COLOR_RESET,
        ANSI_FONT_BOLD);
  printf("\n");

  print("Options:\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
  print("  -h, --help:  Show help message\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
  print("  -v, --version: Show version\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);

  printf("\n");
  print("Subcommands:\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
  print("  add <task>:  Added a new task\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
  print("\t-s {STATUS}: Status for task (Optional)\n", ANSI_COLOR_RESET,
        ANSI_FONT_BOLD);
  print("\t-d {DESCRIPTION}: Description for task (Optional)\n",
        ANSI_COLOR_RESET, ANSI_FONT_BOLD);
  print("  remove <id>: Remove a task by id\n", ANSI_COLOR_RESET,
        ANSI_FONT_BOLD);
  print("  list:        List all task \n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
}

/**
 * handle the add command and create a new task
 **/
Task *handleAddCommand(int argc, const char **argv) {
  if (argc < 3) {
    printError("Missing task name");
    exit(1);
  }

  const char *taskName = argv[2];
  TaskStatus status = PENDING;
  const char *description = "";

  for (int i = 3; i < argc; i++) {
    if (argv[i] == NULL) {
      break;
    }

    if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
      description = argv[i + 1];
      i++;
    } else if (strncmp(argv[i], "-d", 2) == 0) {
      if (argv[i][2] != '\0') {
        description = argv[i] + 2;
        continue;
      }

      if (i + 1 < argc) {
        description = argv[i + 1];
        i++;
      }
    }

    if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
      status = toTaskStatusFromString(argv[i + 1]);

      if (status == -1) {
        printError(concat("Invalid status: ", argv[i + 1]));
        exit(1);
      }

      i++;
    } else if (strncmp(argv[i], "-s", 2) == 0) {
      const char *statusStr;
      if (argv[i][2] == '\0') {
        if (i + 1 < argc) {
          statusStr = argv[i + 1];
          i++;
        } else {
          return NULL;
        }
      } else {
        statusStr = argv[i] + 2;
      }

      status = toTaskStatusFromString(statusStr);
      if (status == -1) {
        printError(concat("Invalid status: ", statusStr));
        exit(1);
      }
    }
  }

  struct Task *task = createTask(1, taskName, status, description);

  if (task == NULL) {
    printError("Cannot create task");
    exit(1);
  }

  saveTasks(task);

  return task;
}

void handleListCommand(TaskManager *taskManager) {
  for (int i = 0; i < taskManager->tasksCount; i++) {
    Task task = taskManager->tasks[i];
    printf("%d. %s\n", task.id, task.name);
    printf("\tStatus: %s\n", fromTaskStatusToString(task.status));
    printf("\tDescription: %s\n", task.description);
  }
}

int runSubcommand(const char *arg, int argc, const char **argv,
                  TaskManager *taskManager) {
  SubCommand subcommand = toSubCommandFromString(arg);

  switch (subcommand) {
  case ADD: {
    const Task *task = handleAddCommand(argc, argv);

    taskManager->tasks = (Task *)realloc(
        taskManager->tasks, (taskManager->tasksCount + 1) * sizeof(Task));

    taskManager->tasks[taskManager->tasksCount] = *task;

    return 0;
  }
  case REMOVE:
    printf("REMOVE\n");
    return 0;
  case LIST:
    handleListCommand(taskManager);
    return 0;
  case HELP:
    showHelp();
    return 0;
  }

  return 1;
}

int runOption(const char *arg) {
  Option option = toOptionFromString(arg);

  switch (option) {
  case HELP_OPTION:
    showHelp();
    return 0;
  case VERSION:
    print("Version: ", ANSI_COLOR_BLUE, ANSI_FONT_BOLD);
    print(VERSION_NUMBER "\n", ANSI_COLOR_RESET, ANSI_FONT_BOLD);
    return 0;
  }

  return 1;
}

void cli(const int argc, const char **argv, TaskManager *taskManger) {
  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    if (arg == NULL) {
      printError("Unknown command: n\n");
      return;
    }

    if (runOption(arg) == 0) {
      return;
    }

    if (runSubcommand(arg, argc, argv, taskManger) == 0) {
      return;
    }

    char *error = concat("Unknown command: ", arg);
    printError(error);

    free(error);

    exit(1);
  }
}
