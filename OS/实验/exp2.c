/*
 * @Descripttion: 
 * @version: 
 * @Author: WangQing
 * @email: 2749374330@qq.com
 * @Date: 2019-12-09 18:31:05
 * @LastEditors: WangQing
 * @LastEditTime: 2019-12-09 21:36:22
 */
#include <stdio.h>
#include <sys/sem.h>
//#include <pthread.h>

int semid;
int sum;
const int N = 100;
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
union semun semopts;

//P、V操作的定义
void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;       //操作标记：0或IPC_NOWAIT等
    semop(semid, &sem, 1); //1:表示执行命令的个数
    return;
}

void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

void *subp1(void *arg)
{
    sum = 0;
    int i;
    for (i = 1; i <= N; i++)
    { //循环累加计算
        P(semid, 1);
        sum = sum + i;
        V(semid, 0);
    }
    return NULL;
}

void *subp2(void *arg)
{
    int i;
    for (i = 1; i <= N; i++)
    {
        P(semid, 0);
        printf("sum = %d\n", sum); //打印结果
        V(semid, 1);
    }
    return NULL;
}

// 封装初始化信号灯函数
void init_semaphore(int sid, int semnum, int initval)
{
    semopts.val = initval;
    semctl(sid, semnum, SETVAL, semopts);
}

int main()
{
    //定义两个信号灯
    semid = semget(0, 2, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget");
        return 0;
    }
    // 初始化信号灯
    init_semaphore(semid, 0, 0);
    init_semaphore(semid, 1, 1);

    // 创建线程
    pthread_t p1, p2;
    pthread_create(&p1, NULL, subp1, NULL);
    pthread_create(&p2, NULL, subp2, NULL);
    // 挂起等待线程结束
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
	// 删除信号灯集
    semctl(semid, 0, IPC_RMID, semopts);
    return 0;
}
