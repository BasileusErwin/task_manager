#include <main.h>

int main(int argc, const char **argv) {
  if (argc < 2) {
    showHelp();
    return 1;
  }

  TaskManager *taskManager = (TaskManager *)malloc(sizeof(TaskManager));
  initTaskManager(taskManager);

  loadTasks(taskManager);

  cli(argc, argv, taskManager);

  freeTaskManager(taskManager);

  return 0;
}
