#include <task.h>

const TaskStatusMap taskStatusMap[] = {
    {"pending", PENDING}, {"in_progress", IN_PROGRESS},
    {"blocked", BLOCKED}, {"deleted", DELETED},
    {"done", DONE},       {NULL, -1}};

DEFINE_ENUM_TO_STRING(fromTaskStatus, TaskStatus, taskStatusMap,
                      sizeof(taskStatusMap) / sizeof(taskStatusMap[0]), "");

DEFINE_ENUM_PARSER(toTaskStatus, TaskStatus, taskStatusMap,
                   sizeof(taskStatusMap) / sizeof(taskStatusMap[0]), -1);

struct Task *createTask(const int id, const char *name, TaskStatus status, const char* description) {
  struct Task *task = (struct Task *)malloc(sizeof(struct Task));

  if (task == NULL) {
    printError("Cannot allocate memory for task");
    exit(1);
  }

  task->id = id;
  task->name = strdup(name);
  task->status = status;
  task->description = strdup(description);

  return task;
}
