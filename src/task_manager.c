#include "task.h"
#include <task_manager.h>

void initTaskManager(TaskManager *taskManager) {
  taskManager->tasks = (Task *)malloc(sizeof(Task) * 1024);
  taskManager->tasksCount = 0;
}

void freeTaskManager(TaskManager *taskManager) {
  for (int i = 0; i < taskManager->tasksCount; i++) {
    freeTask(&taskManager->tasks[i]);
  }

  free(taskManager);
}

void loadTasks(TaskManager *taskManager) {
  FILE *file = fopen("task.data", "r");
  char line[1024];

  struct json_object *parsedJson;
  struct json_object *description;
  struct json_object *status;

  if (file == NULL) {
    printError("Error opening file: task.data");
    exit(1);
  }

  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '\n' || line[0] == '\0') {
      continue;
    }

    parsedJson = json_tokener_parse(line);

    if (parsedJson == NULL) {
      continue;
    }

    json_object_object_get_ex(parsedJson, "description", &description);

    json_object_object_get_ex(parsedJson, "status", &status);

    taskManager->tasks = (Task *)realloc(
        taskManager->tasks, (taskManager->tasksCount + 1) * sizeof(Task));

    const char *descriptionStr = json_object_get_string(description);
    TaskStatus statusEnum =
        toTaskStatusFromString(json_object_get_string(status));

    const Task *newTask = createTask(taskManager->tasksCount, descriptionStr,
                                     statusEnum, descriptionStr);

    taskManager->tasks[taskManager->tasksCount] = *newTask;
    taskManager->tasksCount += 1;
  }

  fclose(file);
}

void saveTasks(Task *task) {
  FILE *file = fopen("task.data", "a");

  if (file == NULL) {
    printError("Error opening file");
    exit(1);
  }

  fprintf(file, "{\"description\": \"%s\", \"status\": \"%s\"}\n",
          task->description, fromTaskStatusToString(task->status));

  fclose(file);
}
