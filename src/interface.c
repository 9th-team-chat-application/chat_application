/*
 * @Copyright: CS of BIT
 * @Author: 王可欣
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 19:08:01 -0700
 * @LastEditTime: 2019-09-04 14:29:17 -0700
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "callbacks.h"
#include "interface.h"
#include "mainprogram.h"

TextView SendText, SeeText;
GtkWidget *CreateSendToolbar(GtkWidget *window);
GtkWidget *CreateMainToolbar(GtkWidget *window);
GtkWidget *CreateS(GtkWidget *window);
static gboolean DropDocument();
static void ReceiveDrop(GtkWidget *widget, GdkDragContext *context,
                        gint x, gint y, GtkSelectionData *data, guint info, guint time, gpointer user_data);

/**
 * @Author: 王可欣 何禾子
 * @Description: 好友列表（主界面）
 * @add Description:添加了个性签名,修改了上端界面,增加了群聊列表
 * @Param: 
 * @Return: 
 */

GtkWidget *CreateMainWindow(void)
{
    GtkWidget *MainWindow;
    GtkWidget *SelfBox; //放置个人信息
    GtkWidget *sep;
    GtkWidget *listsep;
    GtkWidget *SelfTextBox; //防止名字和ID部分
    GtkWidget *FriendBox;   //好友列表
    GtkWidget *ScrollFriend;
    GtkWidget *SelfImage;
    GtkWidget *NickLable;
    GtkWidget *IDLable;
    GtkWidget *MottoLable;
    GtkWidget *ListLable;
    GtkWidget *PaneBetweenSelfAndFriend;
    GtkWidget *panel;
    GtkWidget *MainToolbar;
    GtkWidget *MainMenuBox;
    GtkWidget *MainBox; //竖版box
    GtkWidget *align;
    PangoFontDescription *desc;
    PangoFontDescription *desc1;

    Self *SelfInfo = (Self *)malloc(sizeof(Self));
    SelfInfo->ID = "112078963";
    SelfInfo->NickName = "王可欣";
    SelfInfo->Motto = "风过了,花香还在";
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_move(MainWindow, 1000, 20);

    gtk_window_set_title(GTK_WINDOW(MainWindow), "好友列表");
    g_signal_connect(G_OBJECT(MainWindow), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(GTK_WINDOW(MainWindow), FALSE);

    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 300, 600);
    SelfBox = gtk_hbox_new(FALSE, 0);

    SelfImage = gtk_image_new_from_file("./bin/pic/head.png");
    gtk_box_pack_start(GTK_BOX(SelfBox), SelfImage, FALSE, FALSE, 1);
    sep = gtk_vseparator_new();
    gtk_box_pack_start(GTK_BOX(SelfBox), sep, FALSE, FALSE, 1);

    SelfTextBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(SelfBox), SelfTextBox);
    //昵称
    NickLable = gtk_label_new(SelfInfo->NickName);
    gtk_box_pack_start(GTK_BOX(SelfTextBox), NickLable, FALSE, FALSE, 1);
    //账号
    IDLable = gtk_label_new(SelfInfo->ID);
    gtk_box_pack_start(GTK_BOX(SelfTextBox), IDLable, FALSE, FALSE, 1);
    //个性签名
    MottoLable = gtk_label_new(SelfInfo->Motto);
    gtk_box_pack_start(GTK_BOX(SelfTextBox), MottoLable, FALSE, FALSE, 1);

    desc = pango_font_description_from_string("Simhei 25");
    gtk_widget_modify_font(NickLable, desc);
    desc1 = pango_font_description_from_string("Simhei 10");
    gtk_widget_modify_font(IDLable, desc1);
    gtk_widget_modify_font(MottoLable, desc1);

    gtk_widget_set_size_request(GTK_BOX(SelfBox), 300, 100);
    align = gtk_alignment_new(0, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(align), SelfBox);

    MainBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(MainBox), align);

    listsep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(MainBox), listsep, FALSE, FALSE, 1);

    GtkWidget *notebook;
    GtkWidget *friendlabel;
    GtkWidget *grouplabel;
    GtkWidget *GroupBox;
    GtkWidget *page;
    //GtkWidget *page1;
    notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(MainBox), notebook, FALSE, FALSE, 1);
    //好友列表
    page = gtk_vbox_new(FALSE, 0);
    FriendBox = gtk_vbox_new(FALSE, 0);
    FriendBox = CreateFriendlist(&page);
    gtk_widget_set_size_request(GTK_BOX(FriendBox), 250, 480);
    gtk_box_pack_start(GTK_BOX(page), FriendBox, FALSE, FALSE, 1);
    friendlabel = gtk_label_new("好友列表");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, friendlabel);
    //群聊列表
    page = gtk_vbox_new(FALSE, 0);
    // GroupBox = gtk_vbox_new(FALSE, 0);
    // GroupBox = CreateGrouplist(&page1);
    // gtk_widget_set_size_request(GTK_BOX(GroupBox), 250, 480);
    // gtk_box_pack_start(GTK_BOX(page1),GroupBox, FALSE, FALSE, 1);
    GroupBox = gtk_button_new_with_label("在线群聊");
    gtk_container_add(GTK_CONTAINER(page), GroupBox);
    g_signal_connect(G_OBJECT(GroupBox), "clicked",
                     G_CALLBACK(ClickedGroup), (gpointer)MainWindow);
    grouplabel = gtk_label_new("群聊列表");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page, grouplabel);

    //工具栏

    MainMenuBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(MainBox), MainMenuBox);

    MainToolbar = CreateMainToolbar(MainWindow);
    gtk_box_pack_start(GTK_BOX(MainMenuBox), MainToolbar, 0, 1, 0);

    gtk_container_add(GTK_CONTAINER(MainWindow), MainBox);
    gtk_widget_show_all(MainWindow);
    return MainWindow;
}

/**
 * @Author: 王可欣，邓方晴
 * @Description: 创建主窗口
 * @Param: 
 * @Return: 
 */
GtkWidget *CreateTalkWindow(char *name)
{
    GtkWidget *TalkWindow;
    GtkWidget *scrolledwinup, *scrolledwindown;
    GtkWidget *TalkMenuBox;
    GtkWidget *menubar;
    GtkWidget *toolbar, *buttonbox;
    GtkWidget *SendBtn;
    GtkWidget *hPaned, *vPaned, *cardPaned;
    GtkWidget *mylabelcard, *oppolabelcard;
    GtkWidget *mylabel, *friendlabel;

    TalkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(TalkWindow), name);

    gtk_window_set_default_size(GTK_WINDOW(TalkWindow), 800, 500);
    gtk_window_set_position(GTK_WINDOW(TalkWindow), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(TalkWindow), 10);

    hPaned = gtk_hpaned_new();
    gtk_paned_set_position(hPaned, 600);
    vPaned = gtk_vpaned_new();
    gtk_paned_set_position(vPaned, 300);
    gtk_paned_add1(GTK_PANED(hPaned), vPaned);
    buttonbox = gtk_hbox_new(FALSE, 0);

    //右侧好友资料卡与用户资料卡
    cardPaned = gtk_vbox_new(FALSE, 10);
    //gtk_paned_set_position(cardPaned,250);
    gtk_paned_add2(GTK_PANED(hPaned), cardPaned);
    mylabelcard = gtk_frame_new("个人资料卡");
    oppolabelcard = gtk_frame_new("好友资料卡");
    gtk_widget_set_size_request(mylabelcard, 150, 230);
    gtk_frame_set_label_align(GTK_FRAME(mylabelcard), 0.5, 0);
    gtk_widget_set_size_request(oppolabelcard, 150, 230);
    gtk_frame_set_label_align(GTK_FRAME(oppolabelcard), 0.5, 0);

    gtk_box_pack_start(GTK_BOX(cardPaned), oppolabelcard, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cardPaned), mylabelcard, FALSE, FALSE, 0);
    gtk_frame_set_shadow_type(GTK_FRAME(oppolabelcard), GTK_SHADOW_ETCHED_OUT);
    gtk_frame_set_shadow_type(GTK_FRAME(mylabelcard), GTK_SHADOW_ETCHED_OUT);
    mylabel = gtk_label_new("ID: \nIP: \n状态：　在线\n");
    gtk_container_add(GTK_CONTAINER(mylabelcard), mylabel);
    friendlabel = gtk_label_new("ID: \nIP: \n状态：　在线\n");
    gtk_container_add(GTK_CONTAINER(oppolabelcard), friendlabel);

    TalkMenuBox = gtk_vbox_new(FALSE, 0);
    gtk_paned_add2(GTK_PANED(vPaned), TalkMenuBox);

    toolbar = CreateSendToolbar(TalkWindow);
    gtk_box_pack_start(GTK_BOX(TalkMenuBox), toolbar, 0, 1, 0);

    scrolledwinup = gtk_scrolled_window_new(NULL, NULL);
    scrolledwindown = gtk_scrolled_window_new(NULL, NULL);

    GtkTextTagTable *tagtableshare = gtk_text_tag_table_new();
    SendText.view_buffer = gtk_text_buffer_new(tagtableshare);
    SendText.view = gtk_text_view_new_with_buffer(SendText.view_buffer);
    SeeText.view_buffer = gtk_text_buffer_new(tagtableshare);
    SeeText.view = gtk_text_view_new_with_buffer(SeeText.view_buffer);

    //创建指针保存聊天信息编辑窗口和显示窗口的位置
    chatwin = (FromToWin *)malloc(sizeof(FromToWin));
    chatwin->from = SendText.view_buffer;
    chatwin->to = SeeText.view_buffer;
    chatwin->edit = SendText.view;
    chatwin->show = SeeText.view;

    //左下，发送表情与文件的工具栏、文本编辑窗口、发送按钮
    gtk_box_pack_start(GTK_BOX(TalkMenuBox), scrolledwindown, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(scrolledwindown), SendText.view);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(SendText.view), TRUE);
    gtk_paned_add1(GTK_PANED(vPaned), scrolledwinup);
    gtk_container_add(GTK_CONTAINER(scrolledwinup), SeeText.view);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(SeeText.view), FALSE);
    gtk_text_view_set_cursor_visible(SeeText.view, FALSE);
    
    //设置消息显示窗口中文本的字体颜色
    gtk_text_buffer_create_tag(SeeText.view_buffer,"AutoWrap","wrap_mode",GTK_WRAP_WORD,NULL);//自动换行
    gtk_text_buffer_create_tag(SeeText.view_buffer,"BLUE","foreground", "blue", NULL);//创建蓝色前景标记
    gtk_text_buffer_create_tag(SeeText.view_buffer,"GREEN","foreground", "green", NULL);//创建蓝色前景标记

    // //拖拽
    GtkTargetEntry targets = {"text/uri-list", GTK_TARGET_OTHER_APP, 1};
    gtk_drag_dest_set(SendText.view, GTK_DEST_DEFAULT_DROP, &targets, 1, GDK_ACTION_COPY);
    g_signal_connect(G_OBJECT(SendText.view), "drag-data-received", G_CALLBACK(ReceiveDrop), NULL);
    g_signal_connect(G_OBJECT(SendText.view), "drag-drop", G_CALLBACK(DropDocument), NULL);

    //左下，发送表情与文件的工具栏、文本编辑窗口、发送按钮
    buttonbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(TalkMenuBox), buttonbox, FALSE, FALSE, 0);
    SendBtn = gtk_button_new_with_label("发送");
    chatwin->target = name;
    g_signal_connect(G_OBJECT(SendBtn), "clicked", G_CALLBACK(on_send), (gpointer)chatwin);

    gtk_box_pack_end(buttonbox, SendBtn, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(TalkWindow), hPaned);

    gtk_widget_show_all(TalkWindow);
    return TalkWindow;
}

/**
 * @Author: 王可欣,邓方晴
 * @Description: 创建一个toolbar
 * @Param: 
 * @Return: 
 */
GtkWidget *CreateSendToolbar(GtkWidget *window)
{

    GtkWidget *toolbar;
    GtkWidget *StickerIcon, *DocuIcon, *RecIcon, *SwitchIcon;
    GtkWidget *sticker;
    GtkWidget *record;
    GtkToolItem *OpenDocu;

    toolbar = gtk_toolbar_new();
    StickerIcon = gtk_image_new_from_file("./bin/pic/pic.png");
    DocuIcon = gtk_image_new_from_file("./bin/pic/document.png");
    RecIcon = gtk_image_new_from_file("./bin/pic/record.png");
    SwitchIcon = gtk_image_new_from_file("./bin/pic/switchWindow.png");
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    sticker = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "发送表情", "Private", StickerIcon,
                                      GTK_SIGNAL_FUNC(PressStickerBtn), &SendText);
    OpenDocu = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "打开文件", "Private", DocuIcon,
                                       GTK_SIGNAL_FUNC(OpenSelectDocument), NULL);
    record = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "消息记录", "Private", RecIcon,
                                     GTK_SIGNAL_FUNC(CheckMessageLog), NULL);
    record = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "窗口抖动", "Private", SwitchIcon,
                                     GTK_SIGNAL_FUNC(SwitchWindow), (gpointer)window);

    return toolbar;
}

/**
 * @Author: 王可欣
 * @Description: 创建主页菜单栏
 * @Param: 
 * @Return: 
 */
GtkWidget *CreateMainToolbar(GtkWidget *window)
{
    GtkWidget *toolbar;
    GtkWidget *EditIcon, *SettingIcon, *PaintIcon, *SwitchIcon;
    GtkWidget *setting, *edit;
    GtkToolItem *OpenDocu;

    toolbar = gtk_toolbar_new();
    SettingIcon = gtk_image_new_from_file("./bin/pic/switch.png");
    EditIcon = gtk_image_new_from_file("./bin/pic/edit.png");
    PaintIcon = gtk_image_new_from_file("./bin/pic/paint.png");

    setting = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "切换账号", "Private", SettingIcon,
                                      GTK_SIGNAL_FUNC(BackToLoading), NULL);
    edit = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "修改资料", "Private", EditIcon,
                                   GTK_SIGNAL_FUNC(EditInformation), NULL);
    edit = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "修改主题", "Private", PaintIcon,
                                   GTK_SIGNAL_FUNC(EditBackground), NULL);
    // edit = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "修改主题", "Private", PaintIcon,
    //                                GTK_SIGNAL_FUNC(EditBackground), NULL);
    return toolbar;
}

/**
 * @Author: 王可欣
 * @Description: 防止ReceiveDrop调用两次
 * @Param: 
 * @Return: 
 */
static gboolean DropDocument()
{
    return TRUE;
}

/**
 * @Author: 王可欣
 * @Description: 识别拖拽进来的文件
 * @Param: 
 * @Return: 
 */
static void ReceiveDrop(GtkWidget *widget, GdkDragContext *context,
                        gint x, gint y, GtkSelectionData *data, guint info, guint time, gpointer user_data)
{
    GdkAtom atom = gtk_selection_data_get_data_type(data);
    if (gtk_targets_include_uri(&atom, 1))
    {
        gchar **uris = gtk_selection_data_get_uris(data);
        gint i = 0;
        while (uris[i] != NULL || uris[i] != '\0')
        {
            //文件储存地址
            g_printf("%s\n", uris[i]);
            i++;
        }
        g_strfreev(uris);
    }
    gtk_drag_finish(context, TRUE, TRUE, time);
}
