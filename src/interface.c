/*
 * @Copyright: CS of BIT
 * @Author: 王可欣
 * @File name: 
 * @Version: 
 * @Date: 2019-08-31 19:08:01 -0700
 * @LastEditTime: 2019-09-03 00:20:50 -0700
 * @LastEditors: 
 * @Description: 
 */
#include "head.h"
#include "callbacks.h"
#include "interface.h"

TextView SendText,SeeText;
GtkWidget *CreateSendToolbar(GtkWidget *window);
GtkWidget *CreateMainToolbar(GtkWidget *window);
static gboolean DropDocument();
static void ReceiveDrop(GtkWidget *widget, GdkDragContext *context,
                        gint x, gint y, GtkSelectionData *data, guint info, guint time, gpointer user_data);

/**
 * @Author: 王可欣
 * @Description: 好友列表（主界面）
 * @Param: 
 * @Return: 
 */
GtkWidget *CreateMainWindow(void)
{
    GtkWidget *MainWindow;
    GtkWidget *SelfBox;     //放置个人信息
    GtkWidget *SelfTextBox; //防止名字和ID部分
    GtkWidget *FrinedBox;   //好友列表
    GtkWidget *ScrollFriend;
    GtkWidget *SelfImage;
    GtkWidget *NickLable;
    GtkWidget *IDLable;
    GtkWidget *FriendBox;
    GtkWidget *PaneBetweenSelfAndFriend;
    GtkWidget *panel;
    GtkWidget *MainToolbar;
    GtkWidget *MainMenuBox;
    GtkWidget *MainBox; //竖版box
    GtkWidget *align;
    PangoFontDescription *desc;

    Self *SelfInfo = (Self *)malloc(sizeof(Self));
    SelfInfo->ID = "小明";
    SelfInfo->NickName = "ssssss";
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(MainWindow), "好友列表");
    g_signal_connect(G_OBJECT(MainWindow), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(GTK_WINDOW(MainWindow), FALSE);

    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 300, 600);
    SelfBox = gtk_hbox_new(FALSE, 0);
    // gtk_widget_set_size_request(GTK_BOX(SelfTextBox),30,20);

    SelfImage = gtk_image_new_from_file("./bin/pic/pic.png");
    gtk_container_add(GTK_CONTAINER(SelfBox), SelfImage);

    SelfTextBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(SelfBox), SelfTextBox);
    FrinedBox = gtk_vbox_new(FALSE, 0);

    IDLable = gtk_label_new(SelfInfo->ID);
    gtk_container_add(GTK_CONTAINER(SelfTextBox), IDLable);
    NickLable = gtk_label_new(SelfInfo->NickName);
    gtk_container_add(GTK_CONTAINER(SelfTextBox), NickLable);

    desc = pango_font_description_from_string("Simhei 24");
    gtk_widget_modify_font(IDLable, desc);

    gtk_widget_set_size_request(GTK_BOX(SelfBox), 300, 100);
    align = gtk_alignment_new(0, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(align), SelfBox);

    MainBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(MainBox), align);

    //好友列表
    FriendBox = CreateFriendlist();
    gtk_widget_set_size_request(GTK_BOX(FriendBox), 300, 520);
    gtk_container_add(GTK_CONTAINER(MainBox), FriendBox);

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
GtkWidget *CreateTalkWindow(void)
{
    GtkWidget *TalkWindow;
    GtkWidget *scrolledwinup, *scrolledwindown;
    GtkWidget *TalkMenuBox;
    GtkWidget *menubar;
    GtkWidget *toolbar, *buttonbox;
    GtkWidget *SendBtn;
    GtkWidget *hPaned, *vPaned, *cardPaned;
    TextView mylabelcard, oppolabelcard;

    TalkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(TalkWindow), "完整的应用程序窗口");
    gtk_window_set_default_size(GTK_WINDOW(TalkWindow), 800, 500);
    gtk_window_set_position(GTK_WINDOW(TalkWindow), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(TalkWindow), 10);

    hPaned = gtk_hpaned_new();
    gtk_paned_set_position(hPaned, 600);
    vPaned = gtk_vpaned_new();
    gtk_paned_set_position(vPaned, 350);
    gtk_paned_add1(GTK_PANED(hPaned), vPaned);
    buttonbox = gtk_hbox_new(FALSE, 0);

    //右侧好友资料卡与用户资料卡
    cardPaned = gtk_vpaned_new();
    gtk_paned_set_position(cardPaned, 250);
    gtk_paned_add2(GTK_PANED(hPaned), cardPaned);
    mylabelcard.view = gtk_text_view_new();
    mylabelcard.view_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mylabelcard.view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(mylabelcard.view), FALSE);
    oppolabelcard.view = gtk_text_view_new();
    oppolabelcard.view_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(oppolabelcard.view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(oppolabelcard.view), FALSE);
    gtk_paned_add1(GTK_PANED(cardPaned), oppolabelcard.view);
    gtk_paned_add2(GTK_PANED(cardPaned), mylabelcard.view);

    TalkMenuBox = gtk_vbox_new(FALSE, 0);
    gtk_paned_add2(GTK_PANED(vPaned), TalkMenuBox);

    toolbar = CreateSendToolbar(TalkWindow);
    gtk_box_pack_start(GTK_BOX(TalkMenuBox), toolbar, 0, 1, 0);

    scrolledwinup = gtk_scrolled_window_new(NULL, NULL);
    scrolledwindown = gtk_scrolled_window_new(NULL, NULL);
    SendText.view = gtk_text_view_new();
    SendText.view_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(SendText.view));
    SeeText.view = gtk_text_view_new();
    SeeText.view_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(SeeText.view));

    //创建指针保存聊天信息编辑窗口和显示窗口的位置
    FromToWin *chatwin = (FromToWin *)malloc(sizeof(FromToWin));
    chatwin->from = SendText.view_buffer;
    chatwin->to = SeeText.view_buffer;

    //左下，发送表情与文件的工具栏、文本编辑窗口、发送按钮
    gtk_box_pack_start(GTK_BOX(TalkMenuBox), scrolledwindown, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(scrolledwindown), SendText.view);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(SendText.view), TRUE);
    gtk_paned_add1(GTK_PANED(vPaned), scrolledwinup);
    gtk_container_add(GTK_CONTAINER(scrolledwinup), SeeText.view);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(SeeText.view), FALSE);

    // //拖拽
    GtkTargetEntry targets = {"text/uri-list", GTK_TARGET_OTHER_APP, 1};
    gtk_drag_dest_set(SendText.view, GTK_DEST_DEFAULT_DROP, &targets, 1, GDK_ACTION_COPY);
    g_signal_connect(G_OBJECT(SendText.view), "drag-data-received", G_CALLBACK(ReceiveDrop), NULL);
    g_signal_connect(G_OBJECT(SendText.view), "drag-drop", G_CALLBACK(DropDocument), NULL);

    //左下，发送表情与文件的工具栏、文本编辑窗口、发送按钮
    buttonbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(TalkMenuBox), buttonbox, FALSE, FALSE, 0);
    SendBtn = gtk_button_new_with_label("发送");
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
    GtkWidget *StickerIcon, *DocuIcon,* RecIcon;
    GtkWidget *sticker;
    GtkWidget* record;
    GtkToolItem *OpenDocu;


    toolbar = gtk_toolbar_new();
    StickerIcon = gtk_image_new_from_file("./bin/pic/pic.png");
    DocuIcon = gtk_image_new_from_file("./bin/pic/document.png");
    RecIcon=gtk_image_new_from_file("./bin/pic/record.png");
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    sticker = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "发送表情", "Private", StickerIcon,
                                      GTK_SIGNAL_FUNC(PressStickerBtn), &SendText);
    OpenDocu = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "打开文件", "Private", DocuIcon,
                                       GTK_SIGNAL_FUNC(OpenSelectDocument), NULL);
    record = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "消息记录", "Private", RecIcon,
                                     GTK_SIGNAL_FUNC(CheckMessageLog), NULL);

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
    GtkWidget *StickerIcon, *DocuIcon;
    GtkWidget *sticker;
    GtkToolItem *OpenDocu;

    toolbar = gtk_toolbar_new();
    StickerIcon = gtk_image_new_from_file("./bin/pic/setting.png");
    DocuIcon = gtk_image_new_from_file("./bin/pic/document.png");
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    sticker = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "", "设置", "Private", StickerIcon,
                                      GTK_SIGNAL_FUNC(BackToLoading), &window);
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
