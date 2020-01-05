/*
 * @Descripttion: 
 * @version: 
 * @Author: WangQing
 * @email: 2749374330@qq.com
 * @Date: 2019-12-23 14:05:12
 * @LastEditors  : WangQing
 * @LastEditTime : 2019-12-24 13:17:54
 */
#include<unistd.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>

void getRWX(const unsigned short m)
{
    if (m& S_IRUSR)
       printf("r");
   else
       printf("-");

    if (m & S_IWUSR)
         printf("w");
    else
        printf("-");

    if (m & S_IXUSR)
         printf("x");
    else
        printf("-");

    if (m & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (m & S_IWGRP)
         printf("w");
    else
        printf("-");

    if (m & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (m & S_IROTH)
        printf("r");
    else
        printf("-");

    if (m & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (m & S_IXOTH)
        printf("x   ");
    else
        printf("-   ");
        return;
}

int isPoint(char *str){
	if(str[0]=='.'&&str[1]=='.'&&str[2]=='\0')return 1;
	if(str[0]=='.'&&str[1]=='\0')return 1;
	return 0;
}

void printfMsg(struct dirent *entry, struct stat statbuf, int depth){
    getRWX(statbuf.st_mode);
    printf("%s\t", entry->d_name); //文件名
    printf("%d\t", depth); //深度
    struct passwd *pwd;
    pwd = getpwuid(statbuf.st_uid);
    printf("%s\t", pwd->pw_name);//文件所有者ID
    struct passwd *gpwd;
    if((gpwd=getpwuid(statbuf.st_gid))!=NULL){
        printf("%s\t", gpwd->pw_name);
    }
    printf("%ld\t", statbuf.st_size);//文件大小
    printf("%s",strtok(ctime(&statbuf.st_mtime)+4, "\n")); //最后修改内容时间
    printf("\n");
}

void printdir(char *dir, int depth){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir))==NULL){//打开文件夹
        perror("opendir error");
        return;
    }
    chdir(dir);//改变当前路径
    while((entry=readdir(dp))!=NULL){//读到一个目录项
        lstat(entry->d_name, &statbuf);//得到目录项相关信息
        if(S_ISDIR(statbuf.st_mode)){//是目录
	    if(isPoint(entry->d_name))continue;//目录项名字是“..”“.”跳过
            // 打印目录项的深度、目录名等信息
            printfMsg(entry, statbuf, depth);
            depth+=4;
            printdir(entry->d_name, depth);
            depth-=4;
        }else{
            // 打印目录项的深度、目录名等信息
            printfMsg(entry, statbuf, depth);
        }
    }
    chdir("..");//返回父目录
    closedir(dp);//关闭目录流
}

int main(){
    char dir[100]; //文件目录
    printf("请输入目录：");
    scanf("%s", dir);
    printdir(dir, 0);
    return 0;
}
