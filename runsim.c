#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int makeargv(char *s, char *delimiters, char ***argvp)
{
   char *t;
   char *snew;
   int numtokens;
   int i;
    /* snew is real start of string after skipping leading delimiters */
   snew = s + strspn(s, delimiters);
                              /* create space for a copy of snew in t */
   if ((t = calloc(strlen(snew) + 1, sizeof(char))) == NULL) {
      *argvp = NULL;
      numtokens = -1;
   } else {                     /* count the number of tokens in snew */
      strcpy(t, snew);
      if (strtok(t, delimiters) == NULL)
         numtokens = 0;
      else
         for (numtokens = 1; strtok(NULL, delimiters) != NULL;
              numtokens++)
              ;  
                /* create an argument array to contain ptrs to tokens */
      if ((*argvp = calloc(numtokens + 1, sizeof(char *))) == NULL) {
         free(t);
         numtokens = -1;
      } else {            /* insert pointers to tokens into the array */
         if (numtokens > 0) {
            strcpy(t, snew);
            **argvp = strtok(t, delimiters);
            for (i = 1; i < numtokens + 1; i++)
               *((*argvp) + i) = strtok(NULL, delimiters);
         } else {
           **argvp = NULL;
           free(t);
         }
      }
   }   
   return numtokens;
}

int main (int argc, char *argv[]) {
  pid_t childpid = 0;
  int i, n, pr_limit, pr_count;
  char inbuf[MAX_CANON];
  char delim = " ";
  char **myargv;
   
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
  
  while (fgets(inbuf, MAX_CANON, stdin)== NULL){
    if(pr_count == pr_limit){ 
      wait(NULL);
      pr_count--;
    }
    if((childpid = fork()) == 0){
      makeargv(inbuf, delim, &myargv);
      execvp(myargv[0], myargv);
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
