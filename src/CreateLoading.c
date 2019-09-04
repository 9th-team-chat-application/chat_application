/*
 * @Copyright: CS of BIT
 * @Author: hhz
 * @File name: 
 * @Version: 
 * @Date: 2019-09-01 19:43:01 -0700
 * @LastEditTime: 2019-09-04 21:00:04 +0800
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "interface.h"
#include "actions.h"
#include "DataTransformInterface.h"
static GtkWidget *entry1;
static GtkWidget *entry2;
static GtkWidget *CheckIDentry;
static GtkWidget *CheckQuest;
static GtkWidget *OldPassword;
static GtkWidget *NewPassword;

/**
 * @Author: 何禾子
 * @Description: 向数据库发送消息
 * @Param: 
 * @Return: 
 */
void SendDataBase(GtkWidget *button)
{
    g_print("222\n");
}

/**
 * @Author: 何禾子
 * @Description: 更改密码
 * @Param: 
 * @Return: 
 */
void ChangePassword(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *sbutton;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "更改密码");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    box = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    box1 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);
    box2 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 5);
    label1 = gtk_label_new("旧密码:");
    OldPassword = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1), label1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box1), OldPassword, FALSE, FALSE, 5);
    label2 = gtk_label_new("新密码:");
    NewPassword = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box2), label2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box2), NewPassword, FALSE, FALSE, 5);
    sbutton = gtk_button_new_with_label("登录");
    g_signal_connect(G_OBJECT(sbutton), "clicked",
                     G_CALLBACK(SendDataBase), NULL);
    g_signal_connect_swapped(G_OBJECT(sbutton), "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX(box), sbutton, FALSE, FALSE, 5);
    gtk_widget_set_size_request(G_OBJECT(sbutton), 30, 30);
    gtk_widget_show_all(window);
}

/**
 * @Author: 何禾子
 * @Description: 检查密保问题
 * @Param: 
 * @Return: 
 */
void CheckSecurityQuestion(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *nextbutton;
    char *title = "小蘑菇";
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "输入密保问题");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    box = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    label = gtk_label_new(title);
    CheckQuest = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), CheckQuest, FALSE, FALSE, 5);
    nextbutton = gtk_button_new_with_label("下一步");
    g_signal_connect(G_OBJECT(nextbutton), "clicked",
                     G_CALLBACK(ChangePassword), NULL);

    g_signal_connect_swapped(G_OBJECT(nextbutton), "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_box_pack_start(GTK_BOX(box), nextbutton, FALSE, FALSE, 5);
    gtk_widget_set_size_request(G_OBJECT(nextbutton), 30, 30);

    gtk_widget_show_all(window);
}

/**
 * @Author: 何禾子
 * @Description: 输入账号进行修改密码
 * @Param: 
 * @Return: 
 */
void InputID(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *nextbutton;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "输入账号");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    box = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    label = gtk_label_new("您的账号是:");
    CheckIDentry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), CheckIDentry, FALSE, FALSE, 5);
    nextbutton = gtk_button_new_with_label("下一步");
    g_signal_connect(G_OBJECT(nextbutton), "clicked",
                     G_CALLBACK(CheckSecurityQuestion), NULL);
    g_signal_connect_swapped(G_OBJECT(nextbutton), "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX(box), nextbutton, FALSE, FALSE, 5);
    gtk_widget_set_size_request(G_OBJECT(nextbutton), 30, 30);

    gtk_widget_show_all(window);
}



/**
 * @Author: 王可欣
 * @Description: 按回车键(未使用)
 * @Param: 
 * @Return: 
 */
void PressEnter(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Return)
    {
        const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry1));
        const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry2));
        gint i, flag = 0;
        for (i = 0; i < 10; i++)
        {
            if (*(username + i) == '\0')
                break;
            if (*(username + i) > '9' || *(username + i) < '0')
            {
                char *message = "账号含有非字符部分.";
                flag = 1;
                GtkWidget *dialog;
                dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                message);

                gtk_window_set_title(GTK_WINDOW(dialog), "提示");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                break;
            }
        }
        if (flag == 0)
        {
            gtk_widget_hide_all(LoadingWindow);
            FriendWindow = CreateMainWindow();
            g_print("用户名是:%s ", username);
            g_print("\n");
            g_print("密码是:%s ", password);
            g_print("\n");
        }
    }
 
}
/**
 * @Author: 何禾子
 * @Description: 点击登录按钮
 * @Param: data可以传错误类型
 * @Return: 
 */
void ClickedLoading(GtkWidget *button, gpointer data)
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry1));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry2));
    gint i, flag = 0;
    for (i = 0; i < 10; i++)
    {
        if (*(username + i) == '\0')
            break;
        if (*(username + i) > '9' || *(username + i) < '0')
        {
            char *message = "账号含有非字符部分.";
            flag = 1;
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(NULL,
                                            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            message);

            gtk_window_set_title(GTK_WINDOW(dialog), "提示");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            break;
        }
    }
    if (flag == 0)
    {
        // if (do_connect())
        // {
        //     g_thread_create((GThreadFunc)get_message, NULL, FALSE, NULL);
        // }
        // sendTextToServer(username);

        char ip[BUFFER_SIZE];
        memset(ip,0,sizeof(ip));
        getLocalIP(ip);
        printf("%s\n",ip);
        cJSON *data = cJSON_CreateObject();
        encodeLoginInfo(username, ip, password, data);
        sendTextToServer(data);
        cJSON_Delete(data);

        gtk_widget_hide_all(LoadingWindow);
        FriendWindow = CreateMainWindow();
        // g_print("用户名是:%s ", username);
        // g_print("\n");
        // g_print("密码是:%s ", password);
        // g_print("\n");
    }
}

/**
 * @Author: 何禾子
 * @Description:创建登录头像 
 * @Param: 
 * @Return: 
 */
GtkWidget *CreateLoadingImage(void)
{
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *button;
    GtkWidget *align;

    image = gtk_image_new_from_file("./bin/pic/130pixel.png");
    box = gtk_hbox_new(FALSE, 0);
    //gtk_image_set_pixel_size(image,50);
    gtk_container_set_border_width(GTK_CONTAINER(box), 20);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);
    gtk_widget_set_size_request(GTK_BOX(box), 150, 150);
    gtk_widget_show(image);
    align = gtk_alignment_new(0, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(align), box);
    gtk_widget_show(box);
    return align;
}

/**
 * @Author: 何禾子
 * @Description: 加载登录界面
 * @Param: 
 * @Return: 
 */
GtkWidget *CreateLoading(void)
{
    GtkWidget *window;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *buttonlabelbox;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *buttonlabel1;
    GtkWidget *buttonlabel2;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *sep;
    GtkWidget *sep1;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "登录窗口");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_widget_set_size_request(GTK_WINDOW(window), 360, 165);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    //显示头像
    button1 = CreateLoadingImage();
    gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 5);
    //分隔线
    sep1 = gtk_vseparator_new();
    gtk_box_pack_start(GTK_BOX(hbox), sep1, FALSE, FALSE, 5);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 5);
    box1 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), box1, FALSE, FALSE, 5);
    box2 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), box2, FALSE, FALSE, 5);

    entry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1), entry1, FALSE, FALSE, 5);

    entry2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
    gtk_box_pack_start(GTK_BOX(box2), entry2, FALSE, FALSE, 5);

    //修改密码\忘记密码
    buttonlabelbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), buttonlabelbox, FALSE, FALSE, 1);
    buttonlabel1 = gtk_button_new_with_label("忘记密码");
    buttonlabel2 = gtk_button_new_with_label("修改密码");
    gtk_box_pack_start(GTK_BOX(buttonlabelbox), buttonlabel1, FALSE, FALSE, 7);
    gtk_box_pack_start(GTK_BOX(buttonlabelbox), buttonlabel2, FALSE, FALSE, 5);
    g_signal_connect(GTK_LABEL(buttonlabel1), "clicked", G_CALLBACK(InputID), (gpointer)window);
    g_signal_connect(GTK_LABEL(buttonlabel2), "clicked", G_CALLBACK(InputID), (gpointer)window);
    gtk_button_set_relief(GTK_BUTTON(buttonlabel1), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(buttonlabel2), GTK_RELIEF_NONE);

    //登录按钮
    button = gtk_button_new_with_label("登录");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(ClickedLoading), NULL);

    //g_signal_connect(G_OBJECT(window), "key_press_event",G_CALLBACK(PressEnter), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    gtk_widget_set_size_request(G_OBJECT(button), 50, 50);
    gtk_widget_show_all(window);
    return window;
}