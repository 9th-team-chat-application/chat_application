/*
 * @Copyright: CS of BIT
 * @Author: 王可欣
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 19:45:05 -0700
 * @LastEditTime: 2019-09-03 20:09:59 -0700
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "interface.h"
#include "mainprogram.h"
/**
 * @Author: 王可欣
 * @Description: 在输入框中插入表情
 * @Param: 
 * @Return: 
 */
void InsertEmoji(GtkWidget *widget, GdkEventButton *event, Emoji *sinfo)
{

    char head[30] = "./bin/sticker";
    char tail[10] = ".gif";
    for (int i = 0; i < 3; i++)
        head[13 + i] = sinfo->str[i];
    for (int i = 0; i < 4; i++)
        head[16 + i] = tail[i];
    g_printf("%s\n", head);

    GtkTextIter end;
    //获取缓冲区的尾部
    gtk_text_buffer_get_end_iter(sinfo->view_buffer, &end);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(head, NULL);
    gtk_text_buffer_insert_pixbuf(sinfo->view_buffer, &end, pixbuf);
    //向缓冲区插入数据
    // gtk_text_buffer_insert(sinfo->view_buffer,&end,sinfo->str,-1);

    GtkWidget *sticker_window = sinfo->sticker_window;
    Emoji **p = sinfo->spointer;
    int i;
    for (i = 0; i < 6; i++)
        free(p[i]);
    free(p);
    gtk_widget_destroy(sticker_window);
}

/**
 * @Author: 王可欣
 * @Description: 销毁表情窗口
 * @Param: 
 * @Return: 
 */
void DestoryStickerWindow(GtkWidget *widget, GdkEventCrossing *event, GtkWidget *data)
{
    gtk_widget_destroy(data);
}

/**
 * @Author: 王可欣
 * @Description:按下插入表情按钮 
 * @Param: 
 * @Return: 
 */
void PressStickerBtn(GtkWidget *widget, GdkEvent *event, TextView *viewinfo)
{

    GdkEventButton *event_button = (GdkEventButton *)event;

    GtkWidget *sticker_window;
    GtkWidget *eventbox;
    GtkWidget *sbox1, *sbox2, *sbox3, *sbox4, *sbox5, *sbox6; //盛放6个表情的eventbox
    GtkWidget *table;
    GtkWidget *s1, *s2, *s3, *s4, *s5, *s6; //6个表情的image

    sticker_window = gtk_window_new(GTK_WINDOW_POPUP); //弹出式不边框窗口
    gtk_window_set_default_size(GTK_WINDOW(sticker_window), 100, 100);
    gtk_widget_set_size_request(sticker_window, 200, 100);
    gtk_window_set_position(GTK_WINDOW(sticker_window), GTK_WIN_POS_MOUSE); //出现在鼠标位置

    eventbox = gtk_event_box_new();
    g_signal_connect(G_OBJECT(eventbox), "leave_notify_event", G_CALLBACK(DestoryStickerWindow), sticker_window);
    gtk_container_add(GTK_CONTAINER(sticker_window), eventbox);
    table = gtk_table_new(2, 3, FALSE);
    gtk_container_add(GTK_CONTAINER(eventbox), table);

    sbox1 = gtk_event_box_new();
    sbox2 = gtk_event_box_new();
    sbox3 = gtk_event_box_new();
    sbox4 = gtk_event_box_new();
    sbox5 = gtk_event_box_new();
    sbox6 = gtk_event_box_new();

    Emoji **spointer = (Emoji **)malloc(sizeof(Emoji *) * 6);

    Emoji *sinfo1 = (Emoji *)malloc(sizeof(Emoji));
    sinfo1->str = "/am";
    sinfo1->view_buffer = viewinfo->view_buffer;
    sinfo1->sticker_window = sticker_window;
    sinfo1->spointer = spointer;

    Emoji *sinfo2 = (Emoji *)malloc(sizeof(Emoji));
    sinfo2->str = "/dk";
    sinfo2->view_buffer = viewinfo->view_buffer;
    sinfo2->sticker_window = sticker_window;
    sinfo2->spointer = spointer;

    Emoji *sinfo3 = (Emoji *)malloc(sizeof(Emoji));
    sinfo3->str = "/fd";
    sinfo3->view_buffer = viewinfo->view_buffer;
    sinfo3->sticker_window = sticker_window;
    sinfo3->spointer = spointer;

    Emoji *sinfo4 = (Emoji *)malloc(sizeof(Emoji));
    sinfo4->str = "/sk";
    sinfo4->view_buffer = viewinfo->view_buffer;
    sinfo4->sticker_window = sticker_window;
    sinfo4->spointer = spointer;

    Emoji *sinfo5 = (Emoji *)malloc(sizeof(Emoji));
    sinfo5->str = "/wx";
    sinfo5->view_buffer = viewinfo->view_buffer;
    sinfo5->sticker_window = sticker_window;
    sinfo5->spointer = spointer;

    Emoji *sinfo6 = (Emoji *)malloc(sizeof(Emoji));
    sinfo6->str = "/zj";
    sinfo6->view_buffer = viewinfo->view_buffer;
    sinfo6->sticker_window = sticker_window;
    sinfo6->spointer = spointer;

    spointer[0] = sinfo1;
    spointer[1] = sinfo2;
    spointer[2] = sinfo3;
    spointer[3] = sinfo4;
    spointer[4] = sinfo5;
    spointer[5] = sinfo6;

    g_signal_connect(G_OBJECT(sbox1), "button_press_event", G_CALLBACK(InsertEmoji), (gpointer)sinfo1);
    g_signal_connect(G_OBJECT(sbox2), "button_press_event", G_CALLBACK(InsertEmoji), (gpointer)sinfo2);
    g_signal_connect(G_OBJECT(sbox3), "button_press_event", G_CALLBACK(InsertEmoji), (gpointer)sinfo3);
    g_signal_connect(G_OBJECT(sbox4), "button_press_event", G_CALLBACK(InsertEmoji), (gpointer)sinfo4);
    g_signal_connect(G_OBJECT(sbox5), "button_press_event", G_CALLBACK(InsertEmoji), (gpointer)sinfo5);
    g_signal_connect(G_OBJECT(sbox6), "button_press_event", G_CALLBACK(InsertEmoji), (gpointer)sinfo6);

    s1 = gtk_image_new_from_file("./bin/sticker/am.gif");
    s2 = gtk_image_new_from_file("./bin/sticker/dk.gif");
    s3 = gtk_image_new_from_file("./bin/sticker/fd.gif");
    s4 = gtk_image_new_from_file("./bin/sticker/sk.gif");
    s5 = gtk_image_new_from_file("./bin/sticker/wx.gif");
    s6 = gtk_image_new_from_file("./bin/sticker/zj.gif");

    gtk_container_add(GTK_CONTAINER(sbox1), s1);
    gtk_container_add(GTK_CONTAINER(sbox2), s2);
    gtk_container_add(GTK_CONTAINER(sbox3), s3);
    gtk_container_add(GTK_CONTAINER(sbox4), s4);
    gtk_container_add(GTK_CONTAINER(sbox5), s5);
    gtk_container_add(GTK_CONTAINER(sbox6), s6);

    gtk_table_attach_defaults(GTK_TABLE(table), sbox1, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), sbox2, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), sbox3, 2, 3, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), sbox4, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), sbox5, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), sbox6, 2, 3, 1, 2);

    gtk_widget_show_all(sticker_window);
}

static GtkWidget *dialog = NULL;
/*
 * @Author: 王可欣
 * @Description: 文件选择框点击取消
 * @Param: 
 * @Return: 
 */
void CancelSelectDocument(GtkButton *button, gpointer data)
{
    gtk_widget_destroy(dialog);
}

/**
 * @Author: 王可欣
 * @Description: 文件选择框中点击确定
 * @Param: 
 * @Return: 
 */
void ChosenDocument(GtkButton *button, gpointer data)
{
    //filename是文件路径
    const char *filename;
    GtkWidget *window;
    filename = gtk_file_selection_get_filename(GTK_FILE_SELECTION(data));
    g_printf("%s\n", filename);
}

gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    gtk_main_quit();
    return FALSE;
}

/**
 * @Author: 王可欣
 * @Description: 点击发送文件按钮的回调函数
 * @Param: 
 * @Return: 
 */
void OpenSelectDocument(GtkMenuItem *menuitem, gpointer data)
{
    //函数创建文件选择的窗口
    g_printf(" njzznjnk");
    dialog = gtk_file_selection_new("请选择一个图像文件");
    g_signal_connect(G_OBJECT(dialog), "destroy",
                     G_CALLBACK(gtk_widget_destroy), dialog);
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button),
                     "clicked", G_CALLBACK(ChosenDocument), dialog);
    g_signal_connect_swapped(G_OBJECT(
                                 GTK_FILE_SELECTION(dialog)->ok_button),
                             "clicked", G_CALLBACK(CancelSelectDocument), NULL);
    g_signal_connect(G_OBJECT(
                         GTK_FILE_SELECTION(dialog)->cancel_button),
                     "clicked", G_CALLBACK(CancelSelectDocument), NULL);
    gtk_widget_show(dialog);
}

/**
 * @Author: 王可欣
 * @Description: 返回登录界面
 * @Param: 
 * @Return: 
 */
void BackToLoading(GtkMenuItem *menuitem, gpointer data)
{
    gtk_widget_hide_all(FriendWindow);
    LoadingWindow = CreateLoading();
    gtk_widget_show(LoadingWindow);
}

/**
 * @Author: 邓方晴
 * @Description: 发送按钮点击事件：将文本编辑框中的信息传给显示区，编辑框清空，显示区显示内容,目前只能传送文本
 * @Param: 结构体，包括编辑框的缓冲区指针和显示区的缓冲区指针
 * @Return: 
 * @Throw: 
 */
gboolean isconnected = TRUE;

void on_send(GtkButton *button, FromToWin *ftw)
{
    gchar *message;
    GtkTextIter start, end,show;
    if (isconnected == FALSE)
        return;
    gtk_text_buffer_get_bounds(ftw->from, &start, &end);
    gtk_text_buffer_get_start_iter(ftw->to,&show);

    message = gtk_text_buffer_get_text(ftw->from, &start, &end, FALSE);

    gtk_text_buffer_get_end_iter(ftw->to, &show);
    gtk_text_buffer_insert(ftw->to, &show, "server:  ", -1);
    gtk_text_buffer_get_end_iter(ftw->to, &show);
    gtk_text_buffer_insert(ftw->to, &show, "\n", -1);
    gtk_text_buffer_get_end_iter(ftw->to, &show);

    gtk_text_buffer_insert(ftw->to, &show, message, -1);
    gtk_text_buffer_get_end_iter(ftw->to, &show);
    gtk_text_buffer_insert(ftw->to, &show, "\n", -1);

    gtk_text_buffer_insert_range(ftw->to,&show,&start,&end);
  //  gtk_text_buffer_insert(ftw->to,&show,"\n",-1);


    gtk_text_buffer_set_text(ftw->from, "", 1);
    g_thread_create((GThreadFunc)auto_update_thread, NULL, FALSE, NULL);
}

/**
 * @Author: 邓方晴
 * @Description: 按下“消息记录”
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void CheckMessageLog(GtkWidget *widget, GdkEvent *event)
{
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "历史记录");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_show_all(window);
}

