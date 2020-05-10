#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h" // printf()
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

char buf[512];

// void
// wc(int fd, char *name)
// {
//   int i, n;
//   int l, w, c, inword;
//
//   l = w = c = 0;
//   inword = 0;
//   while((n = read(fd, buf, sizeof(buf))) > 0){
//     for(i=0; i<n; i++){
//       c++;
//       if(buf[i] == '\n')
//         l++;
//       if(strchr(" \r\t\n\v", buf[i]))
//         inword = 0;
//       else if(!inword){
//         w++;
//         inword = 1;
//       }
//     }
//   }
//   if(n < 0){
//     printf(1, "wc: read error\n");
//     exit(0);
//   }
//   printf(1, "%d %d %d %s\n", l, w, c, name);
// }
//
// int
// main(void)
// {
//   printf(1, "Starting waitpid() test:\n");
//
//   int pid = fork();
//   int *status = 0;
//   printf(1, "CURRENT PID: %d\n", getpid());
//   if(pid < 0){
//     printf(1, "ERROR: fork() failed\n");
//     exit(1);
//   }
//   else{
//     if(pid == 0)
//       printf(1, "CHILD PROCESS PID: %d\n", getpid());
//     else{
//       int fork_result = waitpid(pid, status, 0);
//       printf(1, "PARENT PROCESS PID: %d, CHILD PROCESS PID: %d\n", getpid(), pid);
//       if(fork_result < 0){
//         printf(1, "ERROR: wait did not produce expected results\n");
//         exit(1);
//       }
//     }
//   }
//   exit(0);
// }

int stdout = 1;

int main(int argc, char* argv[]) {
	//printf(stdout, "in tests.c main function\n");

	if (argv[1][0] == '1' || argv[1] == 0) {
		// first test
		//exittest();
		printf(stdout, "Testing scheduling priority function\n");
		int pid1,pid2,pid3;

		if ((pid1 = fork())==0){
			// First Child
			setPriority(0);
			printf(stdout, "This is the first child created, pid(%d)\n",(int)getpid());
			while(1){
				printf(stdout, "A");
			}
				exit(0); // First child exits
			}
			else if ((pid2 = fork())==0){
				// Second Child
			setPriority(15);
				printf(stdout, "This is the second child created, pid(%d)\n", (int)getpid());
			while(1){
				printf(stdout, "B");
			}
				exit(0); // Second child exits
		}
		else if ((pid3=fork())==0){
			// Third Child
			setPriority(25);
			printf(stdout, "This is the third child created, pid(%d)\n", (int)getpid());
			while(1){
				printf(stdout, "C");
			}
			exit(0);
		}
		int status1, status2, status3;
		waitpid(pid1,&status1,0);
		waitpid(pid2,&status2,0);
		waitpid(pid3,&status3,0);

		exit(0);
	}
	else if (argv[1][0] == '2') {
		// second test
		int pid;

		if ((pid = fork()) == 0) {
			//child
			setPriority(5);
			sleep(3);
			printf(stdout, "Entered child process, pid: %d, with priority 5\n", (int)getpid());
			while(1) {
				printf(stdout, "c");
			}
		}
		else {
			//parent
			setPriority((int)25);
			sleep(3);
			printf(stdout, "Entered parent process, pid: %d, with priority 25\n", (int)getpid());
			while(1) {
				printf(stdout, "p");
			}
		}

		exit(0);

	}
	else {
		printf(stdout, "Wrong usage or incorrect test number\n");
	}

	exit(0);
}
