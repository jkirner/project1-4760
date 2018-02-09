#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int s,l;
  
  if (argc != 3) {
    perror("%s: Error: Must recieve exactly two(2) arguments", argv[0]);
  }
  s = atoi(argv[1]);
  l = atoi(argv[2]);
  if (s < 1 || l < 1) {
    perror("%s: Error: Must recieve a sleep time and a loop amount greater than 0", argv[0];
  }
  while(l > 0) {
    sleep(s);
  }
  return 0;
}
