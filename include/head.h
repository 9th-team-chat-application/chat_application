/*
 * @Copyright: CS of BIT
 * @Author: 王占坤
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 19:44:55 -0700
 * @LastEditTime: 2019-09-04 10:12:43 -0700
 * @LastEditors: 
 * @Description: 这里是主头文件，包含了所有的库文件，全局变量声明，结构体声明等
 */
#ifndef __HEAD_H__
#define __HEAD_H__
///////////////include库文件区/////////////
#include "config.h"//这里为了防止遗忘，确保把config文件链接到所有文件中
#include <cjson/cJSON.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>  
#include <errno.h>  
#include <sys/types.h>   
#include <pthread.h>
#include <gdk/gdkkeysyms.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
/////////////define区////////////////////
#define MAX_QUEUE_SIZE 500




//////////////typedef区/////////////////
typedef int socketfd;
//从队列中读取服务器发送消息
typedef struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    void **Array;
}*Queue;


/////////////全局结构体定义区//////////




///////////////全局变量声明区/////////////
GtkWidget *FriendWindow;
GtkWidget *LoadingWindow;
Queue Q;
char *local;

#endif

