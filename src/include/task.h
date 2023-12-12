#ifndef TASK_MANANGER_TASK_H
#define TASK_MANANGER_TASK_H

#include <common.h>
#include <console.h>

/**
 * Task status enum
 * */
typedef enum TaskStatus {
  PENDING,
  IN_PROGRESS,
  BLOCKED,
  DELETED,
  DONE,
} TaskStatus;

DEFINE_FUNCTION_ENUM_PARSER(toTaskStatus, TaskStatus);
DEFINE_ENUM_MAP(TaskStatus);

DEFINE_FUNCTION_ENUM_TO_STRING(fromTaskStatus, TaskStatus);

/**
 * Task struct
 *
 * @field id Task id
 * @field name Task name
 * @field status Task status
 * @field description Task description
 * */
typedef struct Task {
  unsigned int id;
  char *name;
  TaskStatus status;
  char *description;
} Task;

Task *createTask(const int id, const char *name, TaskStatus status,
                 const char *description);
void initTask(Task *task);
void freeTask(Task *task);

#endif
