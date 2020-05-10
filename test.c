#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
wc(int fd, char *name)
{
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf(1, "wc: read error\n");
    exit(0);
  }
  printf(1, "%d %d %d %s\n", l, w, c, name);
}

int
main(void)
{
  printf(1, "Starting waitpid() test:\n");

  int pid = fork();
  int *status = 0;
  printf(1, "CURRENT PID: %d\n", getpid());
  if(pid < 0){
    printf(1, "ERROR: fork() failed\n");
    exit(1);
  }
  else{
    if(pid == 0)
      printf(1, "CHILD PROCESS PID: %d\n", getpid());
    else{
      int fork_result = waitpid(pid, status, 0);
      printf(1, "PARENT PROCESS PID: %d, CHILD PROCESS PID: %d\n", getpid(), pid);
      if(fork_result < 0){
        printf(1, "ERROR: wait did not produce expected results\n");
        exit(1);
      }
    }
  }
  exit(0);
}
