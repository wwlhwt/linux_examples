#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

int sec;

void sigroutine(int signo){
   switch (signo){
   case SIGALRM:
       printf("Catch a signal -- SIGALRM \n");
       signal(SIGALRM, sigroutine);
       break;
   case SIGVTALRM:
       printf("Catch a signal -- SIGVTALRM \n");
       signal(SIGVTALRM, sigroutine);
       break;
   }
   return;
}

int main()
{
   struct itimerval value, ovalue, value2;

   sec = 5;
   printf("process id is %d ", getpid());
   signal(SIGALRM, sigroutine);
   signal(SIGVTALRM, sigroutine);
   value.it_value.tv_sec = 1;
   value.it_value.tv_usec = 0;
   value.it_interval.tv_sec = 1;
   value.it_interval.tv_usec = 0;
   setitimer(ITIMER_REAL, &value, &ovalue);
   value2.it_value.tv_sec = 0;
   value2.it_value.tv_usec = 500000;
   value2.it_interval.tv_sec = 0;
   value2.it_interval.tv_usec = 500000;
   setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
   for(;;);
}


/*
gcc test4.c -o test4 -lrt
关于setitimer调用的一个简单示范，在该例子中，每隔一秒发出一个SIGALRM，每隔0.5秒发出一个SIGVTALRM信号
process id is 11996 Catch a signal -- SIGVTALRM 
Catch a signal -- SIGALRM 
Catch a signal -- SIGVTALRM 
Catch a signal -- SIGVTALRM 
Catch a signal -- SIGALRM 
Catch a signal -- SIGVTALRM 
Catch a signal -- SIGVTALRM 
Catch a signal -- SIGALRM 
Catch a signal -- SIGVTALRM 
Catch a signal -- SIGVTALRM 
*/
