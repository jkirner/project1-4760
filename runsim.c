#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
  pid_t childpid = 0;
  int i, n, pr_limit, pr_count;
  
  
  if (argc != 2) {
    fprintf(stderr, "%s: Error: Requires exactly one(1) argument", argv[0]);
    return 1;
  }
  
  pr_limit = atoi(argv[1]);
  
  if (pr_limit < 1) {
    fprintf(stderr, "%s: Error: Command line arguement must be a numerical value greater than 0", argv[0]);
    return 1;
  }
  
  fprintf("How many times would you like to fork?");
  fgets(n);
  
  pr_count = 0;
  
  for (i = 1; i < n; i++){
    if(pr_count == pr_limit){ 
      wait(NULL);
      pr_count--;
    }
    if((childpid = fork()) == 0){
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
