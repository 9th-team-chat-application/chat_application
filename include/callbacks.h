/*
 * @Copyright: CS of BIT
 * @Author: 王可欣
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 06:01:47 -0700
 * @LastEditTime: 2019-09-03 03:59:56 -0700
 * @LastEditors: Please set LastEditors
 */
#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__


//显示表情的结构体

gboolean on_window_delete_event (GtkWidget* widget,GdkEvent *event,gpointer data);
void CheckMessageLog(GtkWidget *widget, GdkEvent *event);
void BackToLoading (GtkMenuItem* menuitem, gpointer data);
void OpenSelectDocument (GtkMenuItem* menuitem, gpointer data);
void PressStickerBtn(GtkWidget *widget, GdkEvent *event, struct text_view_info *viewinfo);
void destory_sticker_window(GtkWidget *widget,GdkEventCrossing *event,GtkWidget* data);
void on_cancel (GtkButton *button,gpointer data);
void on_ok (GtkButton* button, gpointer data);

#endif

