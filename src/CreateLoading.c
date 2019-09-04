/*
 * @Copyright: CS of BIT
 * @Author: hhz
 * @File name: 
 * @Version: 
 * @Date: 2019-09-01 19:43:01 -0700
 * @LastEditTime: 2019-09-04 11:28:57 -0700
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "interface.h"
#include "actions.h"
static GtkWidget *entry1;
static GtkWidget *entry2;
static GtkWidget *CheckIDentry;
static GtkWidget *CheckQuest;
static GtkWidget *AgainPassword;
static GtkWidget *NewPassword;

void on_button_clicked(GtkWidget *button, gpointer window)
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry1));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry2));
    gint i, flag = 0;
    if (*username == '\0' || *password == '\0')
    {
        flag = 1;
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(window,
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "账号或密码为空.", "title");
        gtk_window_set_title(GTK_WINDOW(dialog), "提示");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    if (flag == 0)
        for (i = 0; i < 10; i++)
        {
            if (*(username + i) == '\0')
                break;
            if (*(username + i) > '9' || *(username + i) < '0')
            {
                flag = 1;
                GtkWidget *dialog;
                dialog = gtk_message_dialog_new(window,
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "账号含有非字符部分.", "title");
                gtk_window_set_title(GTK_WINDOW(dialog), "提示");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                gtk_entry_set_text(entry1, "");
                gtk_entry_set_text(entry2, "");
                break;
            }
        }
    if (flag == 0)
    {
        //sendDataToServer(username);
        local=username;
        //跳转到好友列表
        gtk_widget_hide_all(LoadingWindow);
        FriendWindow = CreateMainWindow();
    }
}
/**
 * @Author: hhz
 * @Description: 向数据库发送新密码
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void SendDataBase(GtkWidget *button, gpointer swindow)
{
    const gchar *newcode = gtk_entry_get_text(GTK_ENTRY(NewPassword));
    const gchar *againcode = gtk_entry_get_text(GTK_ENTRY(AgainPassword));
    gint i, flag = 0;
    if (*newcode == '\0' || *againcode == '\0')
    {
        flag = 1;
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(swindow,
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "密码为空.", "title");
        gtk_window_set_title(GTK_WINDOW(dialog), "提示");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    if (flag == 0)
    {
        gint len1 = 0;
        gint len2 = 0;
        for (i = 0; i < 20; i++)
        {
            if (*(newcode + i) != '\0')
                len1++;
        }
        for (i = 0; i < 20; i++)
        {
            if (*(againcode + i) != '\0')
                len2++;
        }
        if (len1 != len2)
            flag == 1;
        for (i = 0; i < 20; i++)
        {
            if (*(newcode + i) == '\0')
                break;
            if (*(newcode + i) != *(againcode + i) || flag == 1)
            {
                flag = 1;
                GtkWidget *dialog;
                dialog = gtk_message_dialog_new(swindow,
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "两次密码不一致.", "title");
                gtk_window_set_title(GTK_WINDOW(dialog), "提示");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                break;
            }
        }
    }
    if (flag == 0)
    {
        gtk_widget_hide(swindow);
    }
}

/**
 * @Author: hhz
 * @Description: 更改密码
 * @Param: 
 * @Return: 
 * @Throw: 
 */

void ChangePassword(GtkWidget *button, gpointer swindow)
{
    const gchar *checkq = gtk_entry_get_text(GTK_ENTRY(CheckQuest));
    gint flag = 0;
    if (*checkq == '\0')
    {
        flag = 1;
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(swindow,
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "答案为空.", "title");
        gtk_window_set_title(GTK_WINDOW(dialog), "提示");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    if (flag == 0)
    {
        //接口
    }
    if (flag == 0)
    {
        GtkWidget *window;
        GtkWidget *box;
        GtkWidget *box1;
        GtkWidget *box2;
        GtkWidget *label1;
        GtkWidget *label2;
        GtkWidget *sbutton;
        gtk_widget_hide(swindow);
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "更改密码");
        gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(window), 0);

        box = gtk_vbox_new(FALSE, 5);
        gtk_container_add(GTK_CONTAINER(window), box);
        box1 = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);
        box2 = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 5);
        label1 = gtk_label_new("新密码:");
        NewPassword = gtk_entry_new();
        gtk_entry_set_visibility(GTK_ENTRY(NewPassword), FALSE);
        gtk_box_pack_start(GTK_BOX(box1), label1, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(box1), NewPassword, FALSE, FALSE, 5);
        gtk_entry_set_max_length(NewPassword, 20);

        label2 = gtk_label_new("再输入:");
        AgainPassword = gtk_entry_new();
        gtk_entry_set_visibility(GTK_ENTRY(AgainPassword), FALSE);
        gtk_box_pack_start(GTK_BOX(box2), label2, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(box2), AgainPassword, FALSE, FALSE, 5);
        gtk_entry_set_max_length(AgainPassword, 20);

        sbutton = gtk_button_new_with_label("登录");
        g_signal_connect(G_OBJECT(sbutton), "clicked",
                         G_CALLBACK(SendDataBase), (gpointer)window);
        //g_signal_connect_swapped(G_OBJECT(sbutton), "clicked", G_CALLBACK(gtk_widget_destroy), window);
        gtk_box_pack_start(GTK_BOX(box), sbutton, FALSE, FALSE, 5);
        gtk_widget_set_size_request(G_OBJECT(sbutton), 30, 30);

        gtk_widget_show_all(window);
    }
}

/**
 * @Author: hhz
 * @Description: 检查密保问题
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void CheckSecurityQuestion(GtkWidget *button, gpointer swindow)
{
    const gchar *checkid = gtk_entry_get_text(GTK_ENTRY(CheckIDentry));
    gint flag = 0;
    if (*checkid == '\0')
    {
        flag = 1;
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(swindow,
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "账号为空.", "title");
        gtk_window_set_title(GTK_WINDOW(dialog), "提示");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    if (flag == 0)
    {
        GtkWidget *window;
        GtkWidget *box;
        GtkWidget *label;
        GtkWidget *nextbutton;
        char *title = "小蘑菇";
        gtk_widget_hide(swindow);
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "输入密保问题");
        gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
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
                         G_CALLBACK(ChangePassword), (gpointer)window);
        //g_signal_connect_swapped(G_OBJECT(nextbutton), "clicked", G_CALLBACK(gtk_widget_destroy), window);
        gtk_box_pack_start(GTK_BOX(box), nextbutton, FALSE, FALSE, 5);
        gtk_widget_set_size_request(G_OBJECT(nextbutton), 30, 30);

        gtk_widget_show_all(window);
    }
}
/**
 * @Author: hhz
 * @Description: 输入账号进行修改密码
 * @Param: 
 * @Return: 
 * @Throw: 
 */
void InputID(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *nextbutton;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "输入账号");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    box = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    label = gtk_label_new("您的账号是:");
    CheckIDentry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), CheckIDentry, FALSE, FALSE, 5);
    gtk_entry_set_max_length(CheckIDentry, 10);
    nextbutton = gtk_button_new_with_label("下一步");
    g_signal_connect(G_OBJECT(nextbutton), "clicked",
                     G_CALLBACK(CheckSecurityQuestion), (gpointer)window);
    //g_signal_connect_swapped(G_OBJECT(nextbutton), "clicked", G_CALLBACK(gtk_widget_hide), window);
    gtk_box_pack_start(GTK_BOX(box), nextbutton, FALSE, FALSE, 5);
    gtk_widget_set_size_request(G_OBJECT(nextbutton), 30, 30);

    gtk_widget_show_all(window);
}
/**
 * @Author: hhz
 * @Description: 显示头像
 * @Param: 
 * @Return: 
 * @Throw: 
 */
GtkWidget *create_button1(void)
{
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *button;
    GtkWidget *align;

    image = gtk_image_new_from_file("./pic/饼干.png");
    box = gtk_hbox_new(FALSE, 0);
    //gtk_image_set_pixel_size(image,50);
    gtk_container_set_border_width(GTK_CONTAINER(box), 10);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);
    gtk_widget_set_size_request(GTK_BOX(box), 130, 130);
    gtk_widget_show(image);
    align = gtk_alignment_new(0, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(align), box);
    gtk_widget_show(box);
    return align;
}

/**
 * @Author: hhz
 * @Description: 可视化密码
 * @Param: 
 * @Return: 
 * @Throw: 
 */
GtkWidget *Buttoneye(void)
{
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *label;
    GtkWidget *button;
    image = gtk_image_new_from_file("./pic/眼睛.png");
    box = gtk_vbox_new(FALSE, 2);
    gtk_container_set_border_width(GTK_CONTAINER(box), 5);
    gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
    gtk_widget_show(image);
    button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button), box);
    gtk_widget_show(box);
    return button;
}
void PasswordVisible(GtkWidget *button, gpointer swindow)
{
    gtk_entry_set_visibility(GTK_ENTRY(entry2), TRUE);
}

/**
 * @Author: hhz
 * @Description: 一键清除
 * @Param: 
 * @Return: 
 * @Throw: 
 */
GtkWidget *ButtonDelete(void)
{
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *label;
    GtkWidget *button;
    image = gtk_image_new_from_file("./pic/叉.png");
    box = gtk_vbox_new(FALSE, 2);
    gtk_container_set_border_width(GTK_CONTAINER(box), 5);
    gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
    gtk_widget_show(image);
    button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button), box);
    gtk_widget_show(box);
    return button;
}
void IDDelete(GtkWidget *button, gpointer swindow)
{
    gtk_entry_set_text(entry1, "");
}

/**
 * @Author: hhz
 * @Description: 显示上方logo
 * @Param: 
 * @Return: 
 * @Throw: 
 */
GtkWidget *ButtonLogo(void)
{
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *button;
    GtkWidget *align;

    image = gtk_image_new_from_file("./pic/shalou.gif");//login.gif
    box = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(box), 2);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);
    gtk_widget_set_size_request(GTK_BOX(box),450, 260);
    gtk_widget_show(image);
    align = gtk_alignment_new(0, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(align), box);
    gtk_widget_show(box);
    return align;
}

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
    GtkWidget *eyebutton;
    GtkWidget *deletebutton;
    GtkWidget *logobutton;
    GtkWidget *sep;
    GtkWidget *sep1;
    GtkWidget *titlebox;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "BBChat");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_widget_set_size_request(GTK_WINDOW(window),340, 440);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    

    //显示logo名
    titlebox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), titlebox);
    logobutton = ButtonLogo();
    gtk_box_pack_start(GTK_BOX(titlebox), logobutton, FALSE, FALSE, 1);
    sep = gtk_vseparator_new();
    gtk_box_pack_start(GTK_BOX(titlebox), sep, FALSE, FALSE, 1);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(titlebox), hbox, FALSE, FALSE, 1);
    
    //显示头像
    button1 = create_button1();
    gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 1);
    
    //分隔线
    sep1 = gtk_vseparator_new();
    gtk_box_pack_start(GTK_BOX(hbox), sep1, FALSE, FALSE, 1);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 1);
    box1 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), box1, FALSE, FALSE, 1);
    box2 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), box2, FALSE, FALSE, 1);
    //账号
    entry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1), entry1, TRUE, TRUE, 2);
    gtk_entry_set_max_length(entry1, 10);
    //一键删除
    deletebutton = ButtonDelete();
    gtk_box_pack_start(GTK_BOX(box1), deletebutton, FALSE, FALSE, 1);
    g_signal_connect(G_OBJECT(deletebutton), "clicked",
                     G_CALLBACK(IDDelete), (gpointer)window);
    gtk_button_set_relief(GTK_BUTTON(deletebutton), GTK_RELIEF_NONE);
    //密码
    entry2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
    gtk_box_pack_start(GTK_BOX(box2), entry2, TRUE, TRUE, 2);
    gtk_entry_set_max_length(entry2, 20);
    //显示密码
    eyebutton = Buttoneye();
    gtk_box_pack_start(GTK_BOX(box2), eyebutton, FALSE, FALSE, 1);
    g_signal_connect(G_OBJECT(eyebutton), "clicked",
                     G_CALLBACK(PasswordVisible), (gpointer)window);
    gtk_button_set_relief(GTK_BUTTON(eyebutton), GTK_RELIEF_NONE);
    

    //修改密码\忘记密码
    buttonlabelbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), buttonlabelbox, TRUE,TRUE, 1);
    buttonlabel1 = gtk_button_new_with_label("忘记密码");
    buttonlabel2 = gtk_button_new_with_label("修改密码");
    gtk_box_pack_start(GTK_BOX(buttonlabelbox), buttonlabel1, TRUE,TRUE, 4);
    gtk_box_pack_start(GTK_BOX(buttonlabelbox), buttonlabel2, TRUE,TRUE, 2);
    g_signal_connect(GTK_LABEL(buttonlabel1), "clicked", G_CALLBACK(InputID), (gpointer)window);
    g_signal_connect(GTK_LABEL(buttonlabel2), "clicked", G_CALLBACK(InputID), (gpointer)window);
    gtk_button_set_relief(GTK_BUTTON(buttonlabel1), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(buttonlabel2), GTK_RELIEF_NONE);

    //登录按钮
    button = gtk_button_new_with_label("登录");
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(on_button_clicked), (gpointer)window);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE,TRUE, 5);
    gtk_widget_set_size_request(G_OBJECT(button), 50, 30);

    gtk_widget_show_all(window);
    return window;
}
