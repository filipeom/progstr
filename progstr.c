#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static char *argv0;

void
die(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(1);
}

void
usage(void) {
  die("Usage: <length> <fill> <empty> <percent>\n");
}

void *
xmalloc(size_t len)
{
  void *ptr;

  if (NULL == (ptr = malloc(len))) {
    die("xmalloc: %s\n", strerror(errno));
  }

  return ptr;
}

char *
progress_string(size_t len, char f, char e, int pnt)
{
  char *b;
  size_t i, high;

  b = xmalloc(len + 1);

  for (i = 0; i < len; ++i)
    b[i] = e;
  b[len] = '\0';

  high = (len * pnt) / 100;
  for (i = 0; i < high; ++i)
    b[i] = f;

  return b;
}

int
main(int argc, char *argv[])
{
  char *bar, f, e;
  long int len, pnt;

  argv0 = argv[0];
  if (argc < 4)
    usage();

  len = atoi(argv[1]);
  if (0 > len) {
    fprintf(stderr, "main: length of bar cannot be a negative number!\n");
    return 1;
  }

  f   = argv[2][0];
  e   = argv[3][0];

  pnt = atoi(argv[4]);
  if ((0 > pnt) || (100 < pnt)) {
    fprintf(stderr, "main: percentage must be between 0~100!\n");
    return 1;
  }
  
  bar = progress_string(len, f, e, pnt);
  printf("%s", bar);

  free(bar);
  return 0;
}
