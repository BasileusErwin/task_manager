#include <task.h>

const TaskStatusMap taskStatusMap[] = {
    {"pending", PENDING}, {"in_progress", IN_PROGRESS},
    {"blocked", BLOCKED}, {"deleted", DELETED},
    {"done", DONE},       {NULL, -1}};

DEFINE_ENUM_TO_STRING(fromTaskStatus, TaskStatus, taskStatusMap,
                      sizeof(taskStatusMap) / sizeof(taskStatusMap[0]), "");

DEFINE_ENUM_PARSER(toTaskStatus, TaskStatus, taskStatusMap,
                   sizeof(taskStatusMap) / sizeof(taskStatusMap[0]), -1);

Task *createTask(const int id, const char uuid[UUID_SIZE], const char *name,
                 TaskStatus status, const char *description) {
  Task *task = (Task *)malloc(sizeof(Task));

  if (task == NULL) {
    printError("Cannot allocate memory for task");
    exit(1);
  }

  if (uuid == NULL) {
    generateUUID(task->uuid);
  } else {
    strcpy(task->uuid, uuid);
  }

  task->id = id;
  task->name = strdup(name);
  task->status = status;
  task->description = strdup(description);

  return task;
}

void initTask(Task *task) {
  task->id = 0;
  task->name = "";
  task->status = PENDING;
  task->description = "";
  task->uuid[0] = '\0';
}

void freeTask(Task *task) {
  free(task->name);
  free(task->description);
}
