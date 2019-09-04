/*
 * @Copyright: CSDepartment,BIT
 * @Author: Tian Yuhang
 * @File name: 
 * @Version: 
 * @Date: 2019-09-04 15:14:57 +0800
 * @LastEditTime: 2019-09-05 00:14:25 +0800
 * @LastEditors: 
 * @Description: 
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__
#include"head.h"
/************************定义区**********************/
#define MsgSize 512//发送请求
typedef struct Send_Request{
    char Message[102400];
    int Type;
}Send_Req;
int MsgId;
static pthread_mutex_t Lock_Of_Queue;
void QueuInit();
void PushMessage(char Msg[]);
void GetMessage(char Msg[]);
void DestroyQueue(int Id);


#endif