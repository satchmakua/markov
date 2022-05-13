//
// shuffle.c
// Filter that reads evey lines from stdin (or a specified file), 
// shuffles them randomly, and outputs the shuffled lines to stdout.
// This is a partial replacement for the 'shuf' command provided
// with most Linux installations.
// Author: W. Cochran wcochran@wsu.edu
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Seed stdlib's random() with a random
// seed using kernel urandom device.
//
void seedRandom(void) {
  FILE *f;
  if ((f = fopen("/dev/urandom", "rb")) == NULL) {
    perror("/dev/urandom");
    exit(-1);
  }
  unsigned int seed;
  fread(&seed, sizeof(seed), 1, f);
  fclose(f);
  srandom(seed);
}

//
// Fisher–Yates shuffle using stdlib's random()
// https://en.wikipedia.org/wiki/Fisher–Yates_shuffle#Potential_sources_of_bias
// Not really doing this exactly right, see
// https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
// 
void shuffle(int numLines, char *lines[]) {  
  for (int i = 0; i < numLines-1; i++) {
    const int n = numLines - i;
    const int j = random() % n + i;
    char *tmp = lines[i];
    lines[i] = lines[j];
    lines[j] = tmp;
  }
}

int main(int argc, char *argv[]) {
  //
  // Read from stdin by default else read from
  // first argument specified on command line.
  //
  FILE *f = stdin;
  if (argc >= 2) {
    f = fopen(argv[1], "rb");
    if (f == NULL) {
      perror(argv[1]);
      exit(1);
    }
  }

  //
  // Buffer each input line into (dynamically sized) array.
  // Caveat: Assume lines are less than 200 chars long (I'm too
  // lazy to do this right).
  //
  int capacity = 10;
  int numLines = 0;
  char **lines = (char **) malloc(capacity * sizeof(char *));
  char buf[200];
  while (fgets(buf, sizeof(buf), f) != NULL) {
    if (numLines >= capacity) {
      capacity *= 2;
      lines = realloc(lines, capacity * sizeof(char *));
    }
    lines[numLines++] = strdup(buf);
  }

  fclose(f);

  //
  // Seed random number generator used by shuffle.
  //
  seedRandom();

  //
  // Shuffle lines.
  //
  shuffle(numLines, lines);
  
  //
  // Echo shuffled lines to stdout.
  //
  for (int i = 0; i < numLines; i++)
    printf("%s", lines[i]);

  return 0;
}
