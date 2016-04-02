#include "my.h"
/**********界面初始化**********/
/***********************************/
/**初始化菜单栏*/
void init_menubar(GtkWidget *menubar)
{
    /**"文件"菜单*/
    GtkWidget *file_M;
    GtkWidget *file_menu;
    GtkWidget *file[4];
    file_M = gtk_menu_item_new_with_label("文件");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_M);

    file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_M), file_menu);

    file[0]= gtk_menu_item_new_with_label("录入");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file[0]);
    file[1]= gtk_menu_item_new_with_label("读取");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file[1]);
    file[2]= gtk_menu_item_new_with_label("存储");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file[2]);
    file[3]= gtk_menu_item_new_with_label("退出");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file[3]);
    g_signal_connect(G_OBJECT(file[0]), "activate",
                     G_CALLBACK(entry_data), 3);
    g_signal_connect(G_OBJECT(file[1]), "activate",
                     G_CALLBACK(LoadData), NULL);
    g_signal_connect(G_OBJECT(file[2]), "activate",
                     G_CALLBACK(SaveData), NULL);
    g_signal_connect(G_OBJECT(file[3]), "activate",
                     G_CALLBACK(quit_save), NULL);
    /**"插入"菜单*/
    GtkWidget *insert_M;
    GtkWidget *insert_menu;
    GtkWidget *insert[3];
    insert_M = gtk_menu_item_new_with_label("插入");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), insert_M);
    insert_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(insert_M), insert_menu);

    insert[0] = gtk_menu_item_new_with_label("插入教师");
    gtk_menu_shell_append(GTK_MENU_SHELL(insert_menu), insert[0]);
    insert[1] = gtk_menu_item_new_with_label("插入工作量");
    gtk_menu_shell_append(GTK_MENU_SHELL(insert_menu), insert[1]);
    insert[2] = gtk_menu_item_new_with_label("插入教学信息");
    gtk_menu_shell_append(GTK_MENU_SHELL(insert_menu), insert[2]);

    g_signal_connect(G_OBJECT(insert[0]), "activate",
                     G_CALLBACK(insert_info), 3);/*调用insert_info函数弹出一个插入输入框*/
    g_signal_connect(G_OBJECT(insert[1]), "activate",
                     G_CALLBACK(insert_info), 4);
    g_signal_connect(G_OBJECT(insert[2]), "activate",
                     G_CALLBACK(insert_info), 5);
    /**"修改"菜单*/
    GtkWidget *Edit_M;
    GtkWidget *Edit_menu;
    GtkWidget *Edit[3];
    Edit_M = gtk_menu_item_new_with_label("修改");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), Edit_M);

    Edit_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(Edit_M), Edit_menu);

    Edit[0] = gtk_menu_item_new_with_label("修改教师");
    gtk_menu_shell_append(GTK_MENU_SHELL(Edit_menu), Edit[0]);
    Edit[1] = gtk_menu_item_new_with_label("修改工作量");
    gtk_menu_shell_append(GTK_MENU_SHELL(Edit_menu), Edit[1]);
    Edit[2] = gtk_menu_item_new_with_label("修改教学信息");
    gtk_menu_shell_append(GTK_MENU_SHELL(Edit_menu), Edit[2]);

    g_signal_connect(G_OBJECT(Edit[0]), "activate",
                     G_CALLBACK(edit_info), 3);    /*调用函数弹出输入框*/
    g_signal_connect(G_OBJECT(Edit[1]), "activate",
                     G_CALLBACK(edit_info), 4);
    g_signal_connect(G_OBJECT(Edit[2]), "activate",
                     G_CALLBACK(edit_info), 5);
    /**"删除"菜单*/
    GtkWidget *Delete_M;
    GtkWidget *delete_menu;
    GtkWidget *delete[3];
    Delete_M = gtk_menu_item_new_with_label("删除");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), Delete_M);

    delete_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(Delete_M), delete_menu);

    delete[0] = gtk_menu_item_new_with_label("删除教师");
    gtk_menu_shell_append(GTK_MENU_SHELL(delete_menu), delete[0]);
    delete[1] = gtk_menu_item_new_with_label("删除工作量");
    gtk_menu_shell_append(GTK_MENU_SHELL(delete_menu), delete[1]);
    delete[2] = gtk_menu_item_new_with_label("删除教学信息");
    gtk_menu_shell_append(GTK_MENU_SHELL(delete_menu), delete[2]);

    g_signal_connect(G_OBJECT(delete[0]), "activate",
                     G_CALLBACK(delete_info), 0);
    g_signal_connect(G_OBJECT(delete[1]), "activate",
                     G_CALLBACK(delete_info), 1);
    g_signal_connect(G_OBJECT(delete[2]), "activate",
                     G_CALLBACK(delete_info), 2);

    /**"查询"菜单*/
    GtkWidget *query_M;
    GtkWidget *query_menu;
    GtkWidget *query[3];
    query_M = gtk_menu_item_new_with_label("查询");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), query_M);

    query_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(query_M), query_menu);

    query[0] = gtk_menu_item_new_with_label("查询教师");
    gtk_menu_shell_append(GTK_MENU_SHELL(query_menu), query[0]);
    query[1] = gtk_menu_item_new_with_label("查询工作量");
    gtk_menu_shell_append(GTK_MENU_SHELL(query_menu), query[1]);
    query[2] = gtk_menu_item_new_with_label("查询教学信息");
    gtk_menu_shell_append(GTK_MENU_SHELL(query_menu), query[2]);

    g_signal_connect(G_OBJECT(query[0]), "activate",
                     G_CALLBACK(query_info), 0);
    g_signal_connect(G_OBJECT(query[1]), "activate",
                     G_CALLBACK(query_info), 1);
    g_signal_connect(G_OBJECT(query[2]), "activate",
                     G_CALLBACK(query_info), 2);
    /**"统计"子菜单*/
    GtkWidget *statistics_M;
    GtkWidget *statistics_menu;
    GtkWidget *statistics[3];
    statistics_M = gtk_menu_item_new_with_label("统计");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), statistics_M);
    statistics_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(statistics_M), statistics_menu);

    statistics[0] = gtk_menu_item_new_with_label("教师科研经费排名");
    gtk_menu_shell_append(GTK_MENU_SHELL(statistics_menu), statistics[0]);
    statistics[1] = gtk_menu_item_new_with_label("教师教学学时排名");
    gtk_menu_shell_append(GTK_MENU_SHELL(statistics_menu), statistics[1]);
    statistics[2] = gtk_menu_item_new_with_label("教学学时不足64学时教师");
    gtk_menu_shell_append(GTK_MENU_SHELL(statistics_menu), statistics[2]);

    g_signal_connect(G_OBJECT(statistics[0]), "activate",
                     G_CALLBACK(statis_fund), NULL);
    g_signal_connect(G_OBJECT(statistics[1]), "activate",
                     G_CALLBACK(statis_working), NULL);
    g_signal_connect(G_OBJECT(statistics[2]), "activate",
                     G_CALLBACK(statis_time), NULL);

    /**"帮助"菜单*/
    GtkWidget *help;
    GtkWidget *helpmenu;
    GtkWidget *about;

    help = gtk_menu_item_new_with_label("帮助");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);

    helpmenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);

    about = gtk_menu_item_new_with_label("关于");
    gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);

    g_signal_connect(G_OBJECT(about), "activate",
                     G_CALLBACK(help_info), NULL);
}
/**********************************************/
/**初始化treeview*/
void init_treeview(void)
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;
    GtkTreeModel *model;

    treeview = gtk_tree_view_new();

    col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "目录");
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer,
                                       "text", COLUMN);

    /*添加model和rootiter*/
    treestore= gtk_tree_store_new(1,
                                  G_TYPE_STRING);
    gtk_tree_store_append(treestore, &rootiter, NULL);
    gtk_tree_store_set(treestore, &rootiter,
                       COLUMN, "TEACHER_SYSTEM",
                       -1);

    model=GTK_TREE_MODEL(treestore);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
}
/***********************************************/
/**初始化显示区域*/
void init_showlist(GtkWidget *list)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    int i,j;
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("类型",
             renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    column = gtk_tree_view_column_new_with_attributes("内容",
             renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    GtkTreeIter *Node_iter[3];
    Node_iter[0]=TEACHER_iter;
    Node_iter[1]=WORK_iter;
    Node_iter[2]=TEACHER_WORK_iter;

    for(i=0; i<3; i++)
    {

        lstore[i] = gtk_list_store_new(2,
                                       G_TYPE_STRING,
                                       G_TYPE_STRING
                                      );
        for(j=0; j<NODE_NUMBER[i+3]; j++)
        {
            gtk_list_store_append(lstore[i], &Node_iter[i][j]);
            gtk_list_store_set(lstore[i], &Node_iter[i][j],
                               COLUMN, Str_Pointer[i][j],
                               -1);
        }

    }
    gtk_tree_view_set_model(GTK_TREE_VIEW(list),
                            GTK_TREE_MODEL(lstore[0]));
}
/*******************************************/
/**改变显示区域*/
void  changed(GtkWidget *widget)
{
    GtkTreeModel *model;
    if (gtk_tree_selection_get_selected(
                GTK_TREE_SELECTION(widget), &model, &selectediter))
    {
        Show_data(selectediter);
    }
}
/**********************************/
/****登录窗口*******/
/**
*函数名：gtk_win_destroy
*功能：登陆框点击取消按钮关闭窗口
*输入参数：
*返回值：无
**/
void gtk_win_destroy(GtkWidget *widget,gpointer data)
{
    gtk_main_quit();
}
/**
*函数名：test
*功能：登录验证函数，点击login按钮时调用
*输入参数：struct LOGIN *login
*返回值：无
**/
void test(GtkWidget *widget,struct LOGIN *login)
{
    gchar *name;
    gchar *pwd;
    //获取输入的信息
    name = gtk_entry_get_text(GTK_ENTRY(login->entry[0]));
    pwd = gtk_entry_get_text(GTK_ENTRY(login->entry[1]));
    if((strcmp(name,NAME) == 0) && (strcmp(pwd,PWD) == 0))
    {
        gtk_label_set_text(GTK_LABEL(login->label),"欢迎");
        gtk_widget_show_all(window);
        gtk_widget_hide(login->window);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(login->label),"用户名或密码错误");
    }
    free(login);
}
/**
*函数名：init_login_widget
*功能：登录框初始化函数
*输入参数：
*返回值：无
**/
void init_login_window()
{
    GtkWidget *login_window; /*登陆窗口*/
    GtkWidget *tips; /*信息提示的标签*/
    GtkWidget *b_login; /*登陆和退出按钮*/
    GtkWidget *b_exit;
    GtkWidget *entry_username; /*用于输入用户名和密码的输入框*/
    GtkWidget *entry_pwd;
    GtkWidget *usename; /*显示username文本框和password文本框提示*/
    GtkWidget *pwd;
    GtkWidget *vbox; /*垂直盒子，包含以下三个水平盒子*/
    GtkWidget *hbox1; /*用户名提示标签和用户名文本框*/
    GtkWidget *hbox2;/*密码提示标签和密码文本框*/
    GtkWidget *hbox3;/*按钮盒子*/
    struct LOGIN *login;
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(login_window), GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (GTK_WINDOW(login_window),1);
    tips = gtk_label_new("欢迎登陆");
    b_login = gtk_button_new_with_label("登陆");
    b_exit = gtk_button_new_with_label("退出");
    entry_username = gtk_entry_new();
    entry_pwd = gtk_entry_new();
    usename = gtk_label_new("用户名 :");
    pwd = gtk_label_new("密码:");
    vbox = gtk_vbox_new(FALSE,20);
    hbox1 = gtk_hbox_new(FALSE,20);
    hbox2 = gtk_hbox_new(FALSE,20);
    hbox3 = gtk_hbox_new(FALSE,20);
    /*设置窗口参数*/
    gtk_window_set_title(GTK_WINDOW(login_window),"TEACHER SYSTEM");
    gtk_window_set_resizable(GTK_WINDOW(login_window),FALSE);
    /*设置布局盒子*/
    gtk_box_pack_start(GTK_BOX(hbox1),usename,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox1),entry_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox2),pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox2),entry_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox3),b_login,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox3),b_exit,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),tips,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),hbox1,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),hbox2,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox),hbox3,TRUE,FALSE,10);
    /*设置密码框不可见*/
    gtk_entry_set_visibility(GTK_ENTRY(entry_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entry_pwd),'*');
    login=(struct LOGIN*)malloc(sizeof(struct LOGIN));
    login->entry[0]=entry_username;
    login->entry[1]=entry_pwd;
    login->window=login_window;
    login->label=tips;
    g_signal_connect(GTK_OBJECT(b_login),"clicked",G_CALLBACK(test),login);
    g_signal_connect(GTK_OBJECT(login_window),"destroy",G_CALLBACK(gtk_win_destroy),NULL);
    g_signal_connect(GTK_OBJECT(b_exit),"clicked",G_CALLBACK(gtk_win_destroy),NULL);
    gtk_container_add(GTK_CONTAINER(login_window),vbox);
    gtk_widget_show_all(login_window);
}

/**main函数*/
/*****************************************************/

int main( int argc, char *argv[])
{
    GtkWidget *vbox = NULL;
    GtkWidget *hbox;

    GtkWidget *menubar;
    GtkWidget *scrolled;
    GtkTreeSelection *selection;

    gtk_init(&argc, &argv);

    Str_Pointer[0]=Teacher_Str;
    Str_Pointer[1]=Work_Str;
    Str_Pointer[2]=Teacher_Work_Str;


    /**主窗口*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 530);
    gtk_window_set_title(GTK_WINDOW(window), "教师信息管理系统 ");
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    //gtk_widget_realize (window);
    g_signal_connect (G_OBJECT(window), "destroy",
                      G_CALLBACK(quit_save), NULL);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    /**菜单栏*/
    menubar = gtk_menu_bar_new();
    init_menubar(menubar);
    gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,0);
    /**滚动条*/
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER(vbox), hbox);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(scrolled),
                                         GTK_SHADOW_ETCHED_IN);
    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER(hbox), vbox);
    gtk_widget_set_usize(GTK_WIDGET(vbox),200,500);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 4);

    /**gtktree目录*/
    init_treeview();/*初始化treeview*/
    gtk_container_add(GTK_CONTAINER (scrolled), treeview);

    /**显示区域*/
    showlist = gtk_tree_view_new();
    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (hbox), vbox);
    gtk_widget_set_usize(GTK_WIDGET(vbox),500,500);
    gtk_box_pack_start(GTK_BOX(vbox), showlist, TRUE, TRUE, 5);
    init_showlist(showlist);/*初始化showlist*/
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    g_signal_connect(selection, "changed",
                     G_CALLBACK(changed), NULL);
    /**登陆窗口*/
    init_login_window();
    gtk_main();
    return 0;
}
