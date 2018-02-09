#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
  pid_t childpid = 0;
  int i, n, pr_limit, pr_count;
  
  
  if (argc != 2) {
    perror ("%s: Error: Requires exactly one(1) argument", argv[0]);
    return 1;
  }
  
  pr_limit = atoi(argv[1]);
  
  if (pr_limit < 1) {
    perror ("%s: Error: Command line arguement must be a numerical value greater than 0", argv[0]);
    return 1;
  }
  
  pr_count = 0;
  
  while (){
    if(pr_count == pr_limit){ 
      wait(NULL);
      pr_count--;
    }
    if((childpid = fork()) == 0){
      char chFile[MAX_CANON];
      char chSleep[MAX_CANON];
      char chLoop[MAX_CANON];
      fgets(chFile);
      fgets(chSleep);
      fgets(chLoop);
      execvp(chFile, chSleep, chLoop)
      break;
    }
    if(childpid > 0) 
      pr_count++;
    if ((childpid == -1) && (errno != EINTR))
      break;
  }
  if (childpid != 0) {
    while (pr_count > 0){
      wait(NULL);
      pr_count--;
  }
  fprintf(stderr, "I am process %ld, my parent is %ld\n", (long)getpid(), (long)getppid());
  return 0;
  }
