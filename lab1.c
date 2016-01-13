#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>


int main(int argc, char *argv[])

{

	pid_t pid;

	switch(pid=fork()){

	case -1:{

		exit(1);
		}

	case 0:{
		pid_t cldpid = getpid();

		pid_t parpid = getppid();


		FILE*pFile1;

		pFile1 = fopen ("cldprocess.txt","w");

		printf ("Opening cldprocess.txt\n")
		fprintf (pFile1, "parentpid=%d\nchildpid=%d\n",parpid,cldpid);

		printf("Writing parentpid and childpid in cldprocess.txt\n")
		fclose(pFile1);

		exit(0);
}
	default:{
		pid_t mypid = getpid();


		FILE*pFile2;

		pFile2 = fopen ("parprocess.txt","w");

		printf("Opening parprocess.txt\n")
		fprintf (pFile2, "mypid=%d\n",mypid);

		printf("Writing pid in parprocess.txt")
		fclose(pFile2);

		sleep(5);
		}
	}

}
