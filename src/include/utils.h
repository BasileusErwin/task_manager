#ifndef TASK_MANAGER_UTILS_H
#define TASK_MANAGER_UTILS_H

#include <common.h>
#include <stdlib.h>
#include <string.h>

#define DEFINE_ENUM_MAP(type)                                                  \
  typedef struct {                                                             \
    const char *str;                                                           \
    type value;                                                                \
  } type##Map;

#define DEFINE_FUNCTION_ENUM_PARSER(name, type)                                \
  type name##FromString(const char *str);

#define DEFINE_ENUM_PARSER(name, type, map, map_size, default_value)           \
  type name##FromString(const char *str) {                                     \
    for (int i = 0; i < map_size; ++i) {                                       \
      if (map[i].str == NULL) {                                                \
        break;                                                                 \
      }                                                                        \
      if (strcmp(str, map[i].str) == 0) {                                      \
        return map[i].value;                                                   \
      }                                                                        \
    }                                                                          \
    return default_value;                                                      \
  }

#define DEFINE_FUNCTION_ENUM_TO_STRING(name, type)                             \
  const char *name##ToString(type enumType);

#define DEFINE_ENUM_TO_STRING(name, type, map, map_size, default_value)        \
  const char *name##ToString(type enumType) {                                  \
    for (int i = 0; i < map_size; ++i) {                                       \
      if (map[i].str == NULL) {                                                \
        break;                                                                 \
      }                                                                        \
      if (enumType == map[i].value) {                                          \
        return map[i].str;                                                     \
      }                                                                        \
    }                                                                          \
    return default_value;                                                      \
  }

char *concat(const char *s1, const char *s2);
char *intToString(unsigned int num);

#endif
