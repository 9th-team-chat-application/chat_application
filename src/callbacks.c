/*
 * @Copyright: CS of BIT
 * @Author: 王可欣
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 19:45:05 -0700
 * @LastEditTime: 2019-09-04 14:40:03 -0700
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "interface.h"
#include "mainprogram.h"

/**
 * @Author: hhz
 * @Description: 
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void SubmitInfo(GtkWidget *button, gpointer window,GtkWidget *data)
{
    gtk_widget_destroy(data);
}

/**
 * @Author: 邓方晴
 * @Description: 在输入为空的情况下点击发送键
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void on_input_null()
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "发送内容不能为空！", "title");
    gtk_window_set_title(GTK_WINDOW(dialog), "提示");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
static char nowtime[30];//全局变量，显示当前时间
/**
 * @Author: 邓方晴
 * @Description: 获得当前系统时间，返回字符串
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void getThisTime()
{
    time_t now ;
    struct tm *l_time;
    now = time((time_t *)NULL);
    l_time = localtime(&now); //取本地时间
    memset(nowtime,'\0',sizeof(nowtime));
    sprintf(nowtime,"%d/%d/%d  %d:%d:%d",l_time->tm_year+1900,l_time->tm_mon+1,l_time->tm_mday,l_time->tm_hour,l_time->tm_min,l_time->tm_sec);
    g_printf("%s\n",nowtime);
}
/**
 * @Author: hhz
 * @Description: 
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void ClickedGroup(GtkWidget *button, gpointer window)
{
    GtkWidget *TalkWindow;
    TalkWindow=CreateTalkWindow(NULL);
    gtk_widget_show(TalkWindow);
}

/**
 * @Author: 王可欣
 * @Description: 在输入框中插入表情
 * @Param: 
 * @Return: 
 */
void InsertEmoji(GtkWidget *widget, GdkEventButton *event, Emoji *sinfo)
{
    gchar* SendMessage;
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
    //gtk_text_buffer_insert(sinfo->view_buffer,&end,sinfo->str,-1);
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

static GtkWidget *entry1;
static GtkWidget *entry2;
static GtkWidget *entry5;
static GtkWidget *entry4;
/**
 * @Author: 王可欣
 * @Description: 修改个人资料
 * @Param: 
 * @Return: 
 */
void EditInformation(GtkMenuItem *menuitem, gpointer data)
{
    GtkWidget *window;
    GtkWidget *label1, *label2, *label4;
    GtkWidget *box1, *box2, *box3, *box4;
    GtkWidget *button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "修改个人资料");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    box3 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box3);

    label1 = gtk_label_new("昵称:");
    entry1 = gtk_entry_new();
    box1 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), label1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box1), entry1, FALSE, FALSE, 5);

    label2 = gtk_label_new("性别:");
    entry2 = gtk_entry_new();
    box2 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box2), label2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box2), entry2, FALSE, FALSE, 5);

    label4 = gtk_label_new("签名:");
    entry4 = gtk_entry_new();
    box4 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box4), label4, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box4), entry4, FALSE, FALSE, 5);

    button=gtk_button_new_with_label("确定");
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(SubmitInfo), window);

    gtk_box_pack_start(GTK_BOX(box3), box1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box3), box2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box3), box4, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box3), button, FALSE, FALSE, 5);
    gtk_widget_show_all(window);
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
    gchar *username="DengFangqing2746 ";
    gchar *friendname="HeHezi2116";
    GtkTextIter start, end, show;
    gchar *report; //report是最终向服务器发送对字符串
    //TODO:report需要有全局或局部变量外部接应

    
    // username = my_string_new("DengFangqing2746 ");
    // friendname = my_string_new("HeHezi2116  ");
    //TODO:此处应有措施传递用户名

    if (isconnected == FALSE)
        return;
    getThisTime(); //获取发送信息的时间

    gtk_text_buffer_get_bounds(ftw->from, &start, &end);
    //TODO:发表情功能加入后，如何提示输出为空
    //message = gtk_text_buffer_get_text(ftw->from,&start,&end,FALSE);//获取输入框内文字
    message = gtk_text_buffer_get_slice(ftw->from, &start, &end, TRUE);
    //printf("%s",message);
    if (strlen(message) == 0 || message == NULL) //当输入空字符时弹出提示对话框
    {
        on_input_null();
        return;
    }
    gtk_text_buffer_get_end_iter(ftw->to, &show);
    /////////////////////聊天窗口界面显示/////////////////////////////
    gtk_text_buffer_insert_with_tags_by_name(ftw->to, &show, username, -1,"AutoWrap","GREEN",NULL);
    gtk_text_buffer_get_end_iter(ftw->to, &show);
    gtk_text_buffer_insert_with_tags_by_name(ftw->to, &show, nowtime, -1,"AutoWrap","GREEN",NULL);
    gtk_text_buffer_insert(ftw->to, &show, "\n", -1);
    gtk_text_buffer_get_end_iter(ftw->to, &show);

    gtk_text_view_set_editable(GTK_TEXT_VIEW(ftw->show), TRUE);  //开启编辑权限
    gtk_text_buffer_insert_range(ftw->to, &show, &start, &end);  //含有pixbuf显示
    gtk_text_view_set_editable(GTK_TEXT_VIEW(ftw->show), FALSE); //关闭编辑权限
    gtk_text_buffer_get_end_iter(ftw->to, &show);
    gtk_text_buffer_insert(ftw->to, &show, "\n", -1);

    gtk_text_buffer_set_text(ftw->from, "", 1); //清空输入框
    ////////////////////////合成发送信息/////////////////////////////
    //TODO:如何将表情包和文件发送信息转成字符发送
    // report = my_string_new("~$Username: ");
    // report = my_string_add(report, username);
    // report = my_string_add(report, "\n~$Friendname: ");
    // report = my_string_add(report, friendname);
    // report = my_string_add(report, "\n~$Time: ");
    // report = my_string_add(report, nowtime);
    // report = my_string_add(report, "\n~$Message: ");
    // report = my_string_add(report, message); //FIXME:
    // report = my_string_add(report, "\nEND \n");

    gtk_text_buffer_get_end_iter(ftw->to, &show);
    gtk_text_buffer_insert(ftw->to, &show, report, -1); //在聊天界面显示，用于验证合成是否成功
    // cJSON* data = cJSON_CreateObject();
    //local,ftw->target,nowtime;
    // encodeUserMessage

    // sendTextToServer(data);
    //g_thread_create((GThreadFunc)auto_update_thread, NULL, FALSE, NULL);
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
    TextView messagelog;
    GtkWidget *scroll;
    GtkTextIter end;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "历史记录");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    scroll = gtk_scrolled_window_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(window), scroll);

    messagelog.view = gtk_text_view_new();
    messagelog.view_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(messagelog.view));
    gtk_text_view_set_editable(messagelog.view,FALSE);
    gtk_text_buffer_get_end_iter(messagelog.view_buffer,&end);//设置历史记录不可以被编辑
    gtk_text_buffer_insert(messagelog.view_buffer,&end,"显示消息记录",-1);

    gtk_container_add(GTK_CONTAINER(scroll),messagelog.view);

    gtk_widget_show_all(window);
}

/**
 * @Author: 王可欣
 * @Description: 修改背景
 * @Param: 
 * @Return: 
 */
void ChangeBack(GtkWidget *widget, int w,int h,const gchar *path)
{
    gtk_widget_set_app_paintable(widget, TRUE); //允许窗口可以绘图
    gtk_widget_realize(widget);

    /* 更改背景图时，图片会重叠
	 * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。
	 */
    gtk_widget_queue_draw(widget);

    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL); // 创建图片资源对象
    // w, h是指定图片的宽度和高度
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);

    GdkPixmap *pixmap;
    /* 创建pixmap图像; 
	 * NULL：不需要蒙版; 
	 * 123： 0~255，透明到不透明
	 */
    gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);
    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);

    // 释放资源
    g_object_unref(src_pixbuf);
    g_object_unref(dst_pixbuf);
    g_object_unref(pixmap);
}

void ClickPic(GtkWidget *widget, GdkEventButton *event,BackGround *data)
{
    
    if (data->type == 1)
        ChangeBack(FriendWindow,300,600, "./bin/background/1.png");
    if (data->type == 2)
        ChangeBack(FriendWindow,300,600, "./bin/background/2.png");
    if (data->type == 3)
        ChangeBack(FriendWindow,300,600, "./bin/background/3.png");
    if (data->type == 4)
        ChangeBack(FriendWindow,300,600, "./bin/background/4.png");
    if (data->type == 5)
        ChangeBack(FriendWindow,300,600, "./bin/background/5.png");
    if (data->type == 6)
        ChangeBack(FriendWindow,300,600, "./bin/background/6.png");
    gtk_widget_destroy(data->view);
}

/**
 * @Author: 王可欣
 * @Description: 弹出修改背景的页面
 * @Param: 
 * @Return: 
 */
void EditBackground(GtkMenuItem *menuitem, gpointer data)
{

    //ChangePic(FriendWindow, 300, 600, "./bin/background/background3.jpg");
    //GdkEventButton *event_button = (GdkEventButton *)event;

    GtkWidget *background_window;
    GtkWidget *eventbox;
    GtkWidget *sbox1, *sbox2, *sbox3, *sbox4, *sbox5, *sbox6; 
    GtkWidget *table;
    GtkWidget *s1, *s2, *s3, *s4, *s5, *s6; 

    background_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    gtk_window_set_default_size(GTK_WINDOW(background_window), 280, 280);
    gtk_widget_set_size_request(background_window, 200, 100);
    gtk_window_set_position(GTK_WINDOW(background_window), GTK_WIN_POS_CENTER); 
    gtk_window_set_title(GTK_WINDOW(background_window), "修改主题");

    eventbox = gtk_event_box_new();
    // g_signal_connect(G_OBJECT(eventbox), "leave_notify_event", G_CALLBACK(DestoryStickerWindow), sticker_window);
    gtk_container_add(GTK_CONTAINER(background_window), eventbox);
    table = gtk_table_new(2, 3, FALSE);
    gtk_container_add(GTK_CONTAINER(eventbox), table);

    sbox1 = gtk_event_box_new();
    sbox2 = gtk_event_box_new();
    sbox3 = gtk_event_box_new();
    sbox4 = gtk_event_box_new();
    sbox5 = gtk_event_box_new();
    sbox6 = gtk_event_box_new();

    BackGround **spointer = (BackGround **)malloc(sizeof(BackGround *) * 6);

    BackGround *sinfo1 = (BackGround *)malloc(sizeof(BackGround));
    sinfo1->type = 1;
    sinfo1->view = background_window;

    BackGround *sinfo2 = (BackGround *)malloc(sizeof(BackGround));
    sinfo2->type = 2;
    sinfo2->view = background_window;

    BackGround *sinfo3 = (BackGround *)malloc(sizeof(BackGround));
    sinfo3->type = 3;
    sinfo3->view = background_window;

    BackGround *sinfo4 = (BackGround *)malloc(sizeof(BackGround));
    sinfo4->type = 4;
    sinfo4->view = background_window;

    BackGround *sinfo5 = (BackGround *)malloc(sizeof(BackGround));
    sinfo5->type = 5;
    sinfo5->view = background_window;

    BackGround *sinfo6 = (BackGround *)malloc(sizeof(BackGround));
    sinfo6->type = 6;
    sinfo6->view = background_window;

    spointer[0] = sinfo1;
    spointer[1] = sinfo2;
    spointer[2] = sinfo3;
    spointer[3] = sinfo4;
    spointer[4] = sinfo5;
    spointer[5] = sinfo6;

    g_signal_connect(G_OBJECT(sbox1), "button_press_event", G_CALLBACK(ClickPic), (gpointer)sinfo1);
    g_signal_connect(G_OBJECT(sbox2), "button_press_event", G_CALLBACK(ClickPic), (gpointer)sinfo2);
    g_signal_connect(G_OBJECT(sbox3), "button_press_event", G_CALLBACK(ClickPic), (gpointer)sinfo3);
    g_signal_connect(G_OBJECT(sbox4), "button_press_event", G_CALLBACK(ClickPic), (gpointer)sinfo4);
    g_signal_connect(G_OBJECT(sbox5), "button_press_event", G_CALLBACK(ClickPic), (gpointer)sinfo5);
    g_signal_connect(G_OBJECT(sbox6), "button_press_event", G_CALLBACK(ClickPic), (gpointer)sinfo6);

    s1 = gtk_image_new_from_file("./bin/preview/1.png");
    s2 = gtk_image_new_from_file("./bin/preview/2.png");
    s3 = gtk_image_new_from_file("./bin/preview/3.png");
    s4 = gtk_image_new_from_file("./bin/preview/4.png");
    s5 = gtk_image_new_from_file("./bin/preview/5.png");
    s6 = gtk_image_new_from_file("./bin/preview/6.png");

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

    gtk_widget_show_all(background_window);
}

/**
 * @Author: 王可欣
 * @Description: 
 * @Param: 
 * @Return: 
 */

int getTime()
{
    time_t now;
    struct tm *l_time;
    now = time((time_t *)NULL);
    l_time = localtime(&now); //取本地时间
    return l_time->tm_sec;
}

/**
 * @Author:何禾子
 * @Description:  实现窗口抖动
 * @Param: 
 * @Return: 
 */
void SwitchWindow(GtkMenuItem *menuitem, gpointer data, gpointer window)
{
    gint x, y, flag = 0;
    gtk_window_get_position(window, &x, &y);
  
    x = x + 50;
    y = y + 50;
    gtk_window_move(window, x, y);
    
    sleep(1);

    x = x - 40;
    y = y - 40;
    gtk_window_move(window, x, y);
    

}
