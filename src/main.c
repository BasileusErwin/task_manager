#include <main.h>
#include <task.h>

int main(int argc, const char **argv) {
  if (argc < 2) {
    showHelp();
    return 1;
  }

  cli(argc, argv);
  return 0;
}
