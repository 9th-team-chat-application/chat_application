/*
 * @Copyright: CS of BIT
 * @Author: 王可欣
 * @File name: 
 * @Version: 
 * @Date: 2019-09-03 06:20:30 -0700
 * @LastEditTime: 2019-09-03 20:08:44 -0700
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "interface.h"
#include "callbacks.h"

gint sd; //套接字句柄

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

void *Front(Queue Q)
{
    if (!IsEmpty(Q))
    {
        return Q->Array[Q->Front];
    }
}

void MakeEmpty(Queue Q)
{
    Q->Front = 1;
}

/**
 * @Author: 王可欣
 * @Description: 连接多人聊天服务器
 * @Param: 
 * @Return: 
 */
gboolean do_connect(void) //连接多人聊天服务器
{
    // GtkTextIter iter;
    // gint slen;
    // sd = socket(AF_INET, SOCK_STREAM, 0); //创建
    // if (sd < 0)
    // {
    //     gtk_text_buffer_get_end_iter(buffer, &iter);
    //     gtk_text_buffer_insert(buffer, &iter, "打开套接字时出错!\n", -1);
    //     return FALSE;
    // }
    // s_in.sin_family = AF_INET;
    // s_in.sin_port = OURPORT;
    // slen = sizeof(s_in);
    // if (connect(sd, &s_in, slen) < 0) //连接
    // {
    //     gtk_text_buffer_get_end_iter(buffer, &iter);
    //     gtk_text_buffer_insert(buffer, &iter, "连接服务器时出错!\n", -1);
    //     return FALSE;
    // }
    // else
    // {
    //     gtk_text_buffer_get_end_iter(buffer, &iter);
    //     gtk_text_buffer_insert(buffer, &iter, username, -1);
    //     gtk_text_buffer_get_end_iter(buffer, &iter);
    //     gtk_text_buffer_insert(buffer, &iter, "\n成功与服务器连接....\n", -1);
    //     //
    //     write(sd, username, 64); //向服务器发送用户名
    //     //
    //     isconnected = TRUE;
    //     return TRUE;
    // }
}
/**
 * @Author: 王可欣
 * @Description:读取信息的线程 
 * @Param: 
 * @Return: 
 */
void recv_thread()
{
    // int numbytes;
    // while(1) {
    // 	printf("recv serverfd = %d\n", serverfd);
    // 	memset(buffer, 0, BUFFER_SIZE);
    // 	numbytes = recv(serverfd, buffer, BUFFER_SIZE, 0);
    // 	printf("recv over, serverfd = %d, numbytes = %d\n", serverfd);
    // 	if(numbytes == 0){
    // 		printf("server offline.\n");
    // 		exit(1);
    // 	}
    // 	if(numbytes == -1){
    // 		perror("error receiving message\n");
    // 		exit(1);
    // 	}
    // 	printf("recv judge over, serverfd = %d\n", serverfd);
    // 	//buffer[numbytes] = '\0';
    //     	printf("received message from server: \"%s\"\n", buffer);
    // 	printf("before handle message, serverfd = %d\n", serverfd);
    // 	//gdk_threads_enter();
    //     handle_message(buffer);
    // 	//gdk_threads_leave();
    // }
}
/**
 * @Author: 王可欣
 * @Description: 线程要执行的函数,读取来自服务器的数据
 * @Param: 
 * @Return: 
 */
void get_message(void)
{
    // GtkTextIter iter;
    // gchar get_buf[1024];
    // gchar buf[1024];
    // while (read(sd, buf, 1024) != -1) //只要读取数据成功就循环执行
    // {
    //     sprintf(get_buf, "%s", buf);
    //     gdk_threads_enter();
    //     //进入
    //     gtk_text_buffer_get_end_iter(buffer, &iter);
    //     gtk_text_buffer_insert(buffer, &iter, get_buf, -1); //显示读取的数据
    //     gdk_threads_leave();
    //     //离开
    // }
}

/**
 * @Author: 王可欣
 * @Description: 向服务器发送消息
 * @Param: 
 * @Return: 
 */
void SendServer(GtkButton *button, gpointer data)
{
    //向服务器发送数据
    //     const char *message;
    // if (isconnected == FALSE)
    //     return;
    // message = gtk_entry_get_text(GTK_ENTRY(message_entry));
    // sprintf(buf, "%s\n", message);
    // write(sd, buf, 1024); //发送
    // gtk_entry_set_text(GTK_ENTRY(message_entry), "");
    //清除单行录中的文字
}

/**
 * @Author: 王可欣
 * @Description: 自动更新线程
 * @Param: 
 * @Return: 
 */
void auto_update_thread()
{
    // while (1)
    // {
    //     //不断进行通讯，收取数据，解析数据
    //     if (Q->Front != Q->Size)
    //     {
            GtkTextIter show;
            // if (isconnected == FALSE)
            //     return;
           char *message="nsjansjasja";
            gdk_threads_enter(); //进入
            gtk_text_buffer_get_end_iter(chatwin->to, &show);

            gtk_text_buffer_insert(chatwin->to, &show, "好友:  ", -1);
            gtk_text_buffer_insert(chatwin->to,&show,"\n",-1);

            gtk_text_buffer_insert(chatwin->to, &show, message, -1);
            gtk_text_buffer_insert(chatwin->to,&show,"\n",-1);
           // new_folder(username, get_buf);
            gdk_threads_leave();
    //     }
    // }
}