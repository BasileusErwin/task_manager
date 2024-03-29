#ifndef TASK_TASK_MANAGER_H
#define TASK_TASK_MANAGER_H

#include <common.h>
#include <console.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <task.h>

typedef struct TaskManager {
  Task *tasks;
  int tasksCount;
} TaskManager;

void initTaskManager(TaskManager *taskManager);
void freeTaskManager(TaskManager *taskManager);

void loadTasks(TaskManager *taskManager);
void saveTasks(Task *task);

#endif
