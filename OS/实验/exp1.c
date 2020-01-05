/*
 * @Descripttion: 
 * @version: 
 * @Author: WangQing
 * @email: 2749374330@qq.com
 * @Date: 2019-12-02 19:02:46
 * @LastEditors: WangQing
 * @LastEditTime: 2019-12-02 21:54:56
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t pid1, pid2;
int pipefd[2];
char buf[30];
int n = 1;
// main函数收到signal信号的处理函数
void handle(int sig)
{
    kill(pid1, SIGUSR1); //发SIGUSR1给子进程1
    kill(pid2, SIGUSR2); //发SIGUSR2给子进程2
}
void handle1()
{
    //关闭管道
    close(pipefd[0]);
    close(pipefd[1]);
    printf("Child Process l is Killed by Parent!\n");
    exit(0);
}
void handle2()
{
    //关闭管道
    close(pipefd[0]);
    close(pipefd[1]);
    printf("Child Process 2 is Killed by Parent!\n");
    exit(0);
}
void child1()
{
    signal(SIGINT, SIG_IGN);  //设置忽略信号SIGINT
    signal(SIGUSR1, handle1); //设置信号SIGUSR1
    while (1)
    {
        sprintf(buf, "I send you %d times.\n", n); //将字符串存储到buf中
        write(pipefd[1], buf, 30);                 // 将buf写入管道
        n++;
        sleep(1); //等待1s
    }
}
void child2()
{
    signal(SIGINT, SIG_IGN);  //设置忽略信号SIGINT
    signal(SIGUSR2, handle2); //设置信号SIGUSR2
    while (1)
    {
        read(pipefd[0], buf, 30);
        printf("%s", buf);
    }
}
int main()
{
    if (pipe(pipefd) < 0)
    { //创建无名管道失败
        perror("pipe");
        exit(-1);
    }
    signal(SIGINT, handle); //设置软中断信号SIGINT

    pid1 = fork();
    if (pid1 == 0)
    {
        child1(); //子进程1执行
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            child2(); //子进程2执行
        }
        else //main
        {

            //等待子进程结束
            int status;
            waitpid(pid1, &status, 0); //1结束
            waitpid(pid2, &status, 0); //2结束
            printf("Parent Process is Killed!\n");

            //关闭管道
            close(pipefd[0]);
            close(pipefd[1]);
            return 0;
        }
    }
}

