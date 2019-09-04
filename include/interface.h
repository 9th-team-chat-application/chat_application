/*
 * @Copyright: CS of BIT
 * @Author: 王可欣
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 09:02:24 -0700
 * @LastEditTime: 2019-09-03 01:54:27 -0700
 * @LastEditors: 
 * @Description: 
 */
#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#define LOADING 1
#define TALKING 2

///////////////////////////结构体定义区///////////////////////



typedef struct from_to_windows{
    GtkTextBuffer *from;
    GtkTextBuffer *to;
    int type;
}FromToWin;

typedef struct _WinAppear
{
    gchar* title;
    gint width,height;
    GtkWindowPosition position;
}WINAPPEAR;


typedef struct SelfInfo{
    char *NickName;
    char *ID;
}Self;

//头像结构
typedef struct portraitInfo{
    GtkWidget *sticker_window;
    GtkTextBuffer *view_buffer; //文本缓冲区
    char *str;   //表情的名字
    struct sticker_info **spointer;
}Portrait;

//好友
typedef struct FriendInfo{
    int num;
    char *Id;
    
}Friend;

//表情
typedef struct sticker_info{
    GtkWidget *sticker_window;
    GtkTextBuffer *view_buffer; //文本缓冲区
    char *str;   //表情的名字
    struct sticker_info **spointer;
}Emoji;

//文本
typedef struct text_view_info{
    GtkWidget *view;
    GtkTextBuffer *view_buffer;
}TextView;



///////////////////////////函数声明区////////////////////////////////
void on_send(GtkButton * button,FromToWin* ftw);
GtkWidget* CreateMainWindow( void );
GtkWidget* CreateTalkWindow( char * name );
GtkWidget* CreateLoading(void);
GtkWidget* CreateFriendlist(void);


FromToWin *chatwin;
#endif
