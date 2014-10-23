#include <stdio.h>

int main (int argc, char *argv[]) {
  int i=0;
  printf("cmdline args count=%d\n", argc);

  /* First argument is executable name only */
  printf("executable name='%s'\n", argv[0]);

  for (i=1; i< argc; i++) {
    printf("arg%d='%s'\n", i, argv[i]);
  }

  return 0;
}
