#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

static char msg[] = "I received a msg.\n";
int len;
static time_t lasttime;

void show_msg(int signo)
{
    write(STDERR_FILENO, msg, len);
}

int main()
{
    struct sigaction act;
    union sigval tsval;
    act.sa_handler = show_msg;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(50, &act, NULL);
    len = strlen(msg);
    time(&lasttime);
    while ( 1 )
    {
        time_t nowtime;
        /*获取当前时间*/
        time(&nowtime);
        /*和上一次的时间做比较，如果大于等于2秒，则立刻发送信号*/
        if (nowtime - lasttime >= 2)
        {
            /*向主进程发送信号，实际上是自己给自己发信号*/
            sigqueue(getpid(), 50, tsval);
            lasttime = nowtime;
        }
    }
    return 0;
}
//gcc test3.c -o test3 -lrt
/*
I received a msg.
I received a msg.
I received a msg.
I received a msg.
I received a msg.

*/
