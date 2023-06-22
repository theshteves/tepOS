#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: memory-user <KiloBytes>\n");
    return -1;
  }
  unsigned long long int requested_bytes = strtoull(argv[1], NULL, 10) * 1000;
  printf("%lluKB? Fine...\n", requested_bytes / 1000);


  char *blob = (char*)calloc(requested_bytes, sizeof(char));
  if (!blob) {
    fprintf(stderr, "Failed to allocate %llu-byte blob", requested_bytes);
    return -1;
  }


  srand(time(NULL)); // seed RNG
  while (1) {
    size_t index = rand() % requested_bytes;
    blob[index] = rand() % CHAR_MAX;
    printf("%zu => %c\n", index, blob[index]);
    usleep(250000); // Sleep for 0.5 seconds
  }

  free(blob);
  return 0;
}
