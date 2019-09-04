/*
 * @Copyright: CS of BIT
 * @Author: hhz
 * @File name: 
 * @Version: 
 * @Date: 2019-09-02 03:31:32 -0700
 * @LastEditTime: 2019-09-04 10:12:53 -0700
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "interface.h"
#include "mainprogram.h"
const gchar *list_item_data_key = "list_item_data";
//static int i = 1;
GtkWidget *list;
GtkWidget *gtklist;
void list_add(int i);

static void sigh_print_selection(GtkWidget *gtklist, gpointer func_data);

/**
 * @Author: 何禾子
 * @Description: 创建好友列表
 * @Param: 
 * @Return: 
 */
GtkWidget * CreateFriendlist(GtkWidget *page)
{
    GtkWidget *vbox;
    GtkWidget *view;
    GtkWidget *scrolled_window;
    GtkWidget *button;
    GList *dlist;
    guint i;

    vbox = gtk_vbox_new(FALSE, 0);
    
   // gtk_container_add(GTK_CONTAINER(window), vbox);
    //滚动条
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(vbox), scrolled_window);
    gtk_scrolled_window_set_policy(scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    gtklist = gtk_list_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), gtklist);
    g_signal_connect(G_OBJECT(gtklist), "selection_changed", G_CALLBACK(sigh_print_selection), NULL);
    //g_signal_connect(G_OBJECT(gtklist), "clicked", G_CALLBACK(sigh_print_selection), NULL);
/////////////传入数据
    for (i = 0; i < 100; i++)
    {
        list_add(i);
    }
////////////
    return vbox;
}

/**
 * @Author: 何禾子
 * @Description: 点击列表中好友的回调函数
 * @Param: 
 * @Return: 
 */
void sigh_print_selection(GtkWidget *gtklist, gpointer func_data)
{
    GList *dlist;
    dlist = GTK_LIST(gtklist)->selection;
    if (!dlist)
    {
        g_print("Selection cleared\n");
        return;
    }
    g_print("The selection is a ");
    while (dlist)
    {
        GtkWidget *TalkWindow;
        
        const gchar *item_data_string;
        item_data_string = g_object_get_data(G_OBJECT(dlist->data), list_item_data_key);
        g_print("%s ", item_data_string);
        
        TalkWindow=CreateTalkWindow(item_data_string);
        
        g_thread_create((GThreadFunc)auto_update_thread, NULL, FALSE, NULL);
        gtk_widget_show(TalkWindow);
        dlist = dlist->next;
    }
    g_print("\n");
}

/**
 * @Author: 何禾子
 * @Description: 在好友列表中增加函数
 * @Param: 
 * @Return: 
 */
void list_add(int i)
{
    GtkWidget *label;
    gchar buffer[64];
    GtkWidget *list_item;
    PangoFontDescription *desc;
    gchar *string;
    sprintf(buffer, "%d", i);
    //label=gtk_button_new_with_label(buffer);
    label = gtk_label_new(buffer);
    gtk_misc_set_alignment(GTK_MISC(label), 0.15, 0.6);
    desc = pango_font_description_from_string("16");
    gtk_widget_modify_font(label, desc);
    list_item = gtk_list_item_new();
    gtk_container_add(GTK_CONTAINER(list_item), label);
    gtk_widget_show(label);
    gtk_container_add(GTK_CONTAINER(gtklist), list_item);
    gtk_widget_show(list_item);
    gtk_label_get(GTK_LABEL(label), &string);
    g_object_set_data(G_OBJECT(list_item), list_item_data_key, string);
}