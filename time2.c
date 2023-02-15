#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>

void  handle(union sigval v)
{
 time_t t;
 char p[32];
 time(&t);
 strftime(p, sizeof(p), "%T", localtime(&t));
 printf("%s thread %lu, val = %d, signal captured.\n", p, pthread_self(), v.sival_int);
 return;
}

int main()
{
 struct sigevent evp;
 struct itimerspec ts;
 timer_t timer;
 int ret;
 memset   (&evp,   0,   sizeof   (evp));
 evp.sigev_value.sival_ptr = &timer;
 evp.sigev_notify = SIGEV_THREAD;
 evp.sigev_notify_function = handle;
 evp.sigev_value.sival_int = 3;   //作为handle()的参数
 ret = timer_create(CLOCK_REALTIME, &evp, &timer);
 if( ret)
  perror("timer_create");
 ts.it_interval.tv_sec = 1;
 ts.it_interval.tv_nsec = 0;
 ts.it_value.tv_sec = 3;
 ts.it_value.tv_nsec = 0;
 ret = timer_settime(timer, TIMER_ABSTIME, &ts, NULL);
 if( ret )
  perror("timer_settime");
 while(1);
}

/*
gcc test2.c -o test2 -lrt
17:03:00 thread 818128640, val = 3, signal captured.
17:03:00 thread 818128640, val = 3, signal captured.
17:03:01 thread 818128640, val = 3, signal captured.
17:03:02 thread 818128640, val = 3, signal captured.
17:03:03 thread 818128640, val = 3, signal captured.
17:03:04 thread 818128640, val = 3, signal captured.
17:03:05 thread 818128640, val = 3, signal captured.
17:03:06 thread 818128640, val = 3, signal captured.
17:03:07 thread 818128640, val = 3, signal captured.
17:03:08 thread 818128640, val = 3, signal captured.
17:03:09 thread 818128640, val = 3, signal captured.
17:03:10 thread 818128640, val = 3, signal captured.
17:03:11 thread 818128640, val = 3, signal captured.
17:03:12 thread 818128640, val = 3, signal captured.
*/
