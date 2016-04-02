#include "my.h"
/********�رմ���**************/
/**
*��������close
*���ܣ��رմ���
*���������GtkWidget*window
*����ֵ����
*/
void close(GtkWidget*button,GtkWidget*window)
{
    gtk_widget_destroy(window);
}
/****************************************/
/*******��ʾ����***********/
/**
*��������Show_TEACHER
*���ܣ���ʾ��ʦ�ڵ�����
*���������char*name
*����ֵ��GtkListStore
*/
GtkListStore *Show_TEACHER(char *name)
{
    TEACHER_NODE *pTEACHER;
    pTEACHER=TEACHER_search(name);
    gtk_list_store_set(lstore[0], &TEACHER_iter[0],  /*ΪIstore��ӽ�ʦ�ڵ�����*/
                       COMMENT, pTEACHER->number,
                       -1);
    gtk_list_store_set(lstore[0], &TEACHER_iter[1],
                       COMMENT, pTEACHER->name,
                       -1);
    gtk_list_store_set(lstore[0], &TEACHER_iter[2],
                       COMMENT, pTEACHER->company,
                       -1);
    gtk_list_store_set(lstore[0], &TEACHER_iter[3],
                       COMMENT, pTEACHER->title,
                       -1);
    return(lstore[0]);
}
/*************************************************/
/**
*��������Show_WORK
*���ܣ���ʾ���ֽڵ�����
*���������char*name,char *P_name
*����ֵ��GtkListStore
*/
GtkListStore *Show_WORK(char *name,char *P_name)
{
    TEACHER_NODE *pTEACHER;
    pTEACHER=TEACHER_search(P_name);/*�ý�ʦID������ʦ�ڵ�*/
    WORK_NODE *pWORK;
    char str[15];
    pWORK=WORK_search(name,pTEACHER->work_node);/*�����year�����������ڵ�*/
    gtk_list_store_set(lstore[1], &WORK_iter[0],                    /*ΪIstore��ӹ������ڵ�����*/
                       COMMENT, pWORK->number,
                       -1);
    gtk_list_store_set(lstore[1], &WORK_iter[1],
                       COMMENT, pWORK->year,
                       -1);
    itoa(pWORK->working,str,10);
    gtk_list_store_set(lstore[1], &WORK_iter[2],
                       COMMENT, str,
                       -1);
    itoa(pWORK->member,str,10);
    gtk_list_store_set(lstore[1], &WORK_iter[3],
                       COMMENT, str,
                       -1);
    itoa(pWORK->element,str,10);
    gtk_list_store_set(lstore[1], &WORK_iter[4],
                       COMMENT,str,
                       -1);
    itoa(pWORK->goal,str,10);
    gtk_list_store_set(lstore[1], &WORK_iter[5],
                       COMMENT,str,
                       -1);
    return(lstore[1]);
}

/*******************************************************/
/**
*��������Show_TEACHER_WORK
*���ܣ���ʾ���ֽڵ�����
*���������char*name,char *P_name,char *PP_name
*����ֵ��GtkListStore
*/
GtkListStore *Show_TEACHER_WORK(char *name,char *P_name,char *PP_name)
{
    TEACHER_NODE *pTEACHER;
    pTEACHER=TEACHER_search(PP_name);/*�ñ��ID������ʦ�ڵ�*/
    WORK_NODE *pWORK;
    pWORK=WORK_search(P_name,pTEACHER->work_node);
    TEACHER_WORK_NODE *pTEACHER_WORK;
    pTEACHER_WORK=TEACHER_WORK_search(name,pWORK->teacher_work_node);/*�ð༶class������ѧ��Ϣ�ڵ�*/
    char str[15];
    gtk_list_store_set(lstore[2], &TEACHER_WORK_iter[0], /*ΪIstore��ӽ�ѧ��Ϣ�ڵ�����*/
                       COMMENT, pTEACHER_WORK->number,
                       -1);
    gtk_list_store_set(lstore[2], &TEACHER_WORK_iter[1],
                       COMMENT, pTEACHER_WORK->year,
                       -1);
    gtk_list_store_set(lstore[2], &TEACHER_WORK_iter[2],
                       COMMENT, pTEACHER_WORK->Class,
                       -1);
    itoa(pTEACHER_WORK->teaching_hours,str,10);
    gtk_list_store_set(lstore[2], &TEACHER_WORK_iter[3],
                       COMMENT,str,
                       -1);
    itoa(pTEACHER_WORK->experimental_hours,str,10);
    gtk_list_store_set(lstore[2], &TEACHER_WORK_iter[4],
                       COMMENT,str,
                       -1);
    itoa(pTEACHER_WORK->student_member,str,10);
    gtk_list_store_set(lstore[2], &TEACHER_WORK_iter[5],
                       COMMENT,str,
                       -1);
    gtk_list_store_set(lstore[2], &TEACHER_WORK_iter[6],
                       COMMENT, pTEACHER_WORK->program,
                       -1);
    return(lstore[2]);
}
/***********************************/
/**
*��������Show_data
*���ܣ���ѡ�еĽڵ���Ϣ����ʾ������ʾ����
*���������iter
*����ֵ����
*/
int Show_data(GtkTreeIter iter)
{
    GtkTreeModel *model;
    GtkTreePath *path;

    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    path= gtk_tree_model_get_path(model, &iter);
    char *name;
    gtk_tree_model_get (model,&iter,           /*��ȡ�ڵ�name*/
                        COLUMN,&name,
                        -1);
    switch(gtk_tree_path_get_depth (path))/*�жϽڵ�����*/
    {
    case TYPE_ROOT:
        return 1;
    case TYPE_TEACHER:
        liststore=Show_TEACHER(name);
        break;
    case TYPE_WORK:
    {
        char *P_name;
        gtk_tree_path_up(path);/*��ȡ��һ�����ڵ�path*/
        gtk_tree_model_get_iter(model,&iter,path);/*��ȡ��һ�����ڵ�iter*/
        gtk_tree_model_get (model,&iter,
                            COLUMN,&P_name,/*��ȡ��һ�����ڵ�name*/
                            -1);
        liststore=Show_WORK(name,P_name);
        break;
    }
    case TYPE_TEACHER_WORK:
    {
        char *P_name,*PP_name;
        gtk_tree_path_up(path);
        gtk_tree_model_get_iter(model,&iter,path);
        gtk_tree_model_get (model,&iter,
                            COLUMN,&P_name,
                            -1);
        gtk_tree_path_up(path);
        gtk_tree_model_get_iter(model,&iter,path);
        gtk_tree_model_get (model,&iter,
                            COLUMN,&PP_name,
                            -1);
        liststore=Show_TEACHER_WORK(name,P_name,PP_name);
        break;
    }
    default :
        return 0;
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(showlist),
                            GTK_TREE_MODEL(liststore));
    return 1;
}
/*****************************************/
/****** ��������**********/
/**
*��������dialog_info
*���ܣ�����һ����Ϣ��
*���������show Ҫ��ʾ���ַ���
*����ֵ����
*/
void dialog_info(char *show)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    show, "title");
    gtk_window_set_title(GTK_WINDOW(dialog), "֪ͨ");
    gtk_window_set_keep_above (GTK_WINDOW(dialog),1);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
/*********************************************/
/***************************�����********************************/
/**********¼�������*************/

/********************************/
/**
*��������entry_info
*���ܣ�����һ�������
*���������int type
*����ֵ����
*/
void entry_info(int type)
{
    GtkWidget *entry_window;
    GtkWidget *label,*b_ok,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry[7];
    struct transfer *nodec;
    int i;
    entry_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(entry_window,350,300);
    gtk_window_set_title(GTK_WINDOW(entry_window),"����ڵ�����");
    g_signal_connect(G_OBJECT(entry_window),"destroy",
                     G_CALLBACK(gtk_widget_destroy),NULL);
    gtk_window_set_position(GTK_WINDOW(entry_window),GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (GTK_WINDOW(entry_window),1);
    vbox = gtk_vbox_new (FALSE, 12);
    gtk_container_add (GTK_CONTAINER (entry_window), vbox);
    /*���ݲ����ṹ*/
    nodec=(struct transfer*)malloc(sizeof(struct transfer));
    table = gtk_table_new(NODE_NUMBER[type]+1,7,TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);
    for(i=0; i<NODE_NUMBER[type]; i++)
    {
        label = gtk_label_new(Str_Pointer[type-3][i]);
        gtk_table_attach(GTK_TABLE(table),label,1,3,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        entry[i] = gtk_entry_new();
        gtk_table_attach(GTK_TABLE(table),entry[i],3,7,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        nodec->entry[i]=entry[i];
    }
    nodec->window = entry_window;
    nodec->type=type;
    b_ok=gtk_button_new_with_label("ȷ��");
    g_signal_connect(G_OBJECT(b_ok),"clicked",G_CALLBACK(input_data),nodec);
    gtk_table_attach(GTK_TABLE(table),b_ok,1,2,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    b_cancel=gtk_button_new_with_label("ȡ��");
    g_signal_connect(G_OBJECT(b_cancel),"clicked",G_CALLBACK(close),entry_window);
    gtk_table_attach(GTK_TABLE(table),b_cancel,5,6,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    gtk_widget_show_all(entry_window);
}
/*********************************************/
void entry_data(GtkWidget*button,int type)//¼�밴ť����
{
    entry_info(type);
}
/***********************************/
/************�Ի���*************/
/**
*��������dialogdata
*���ܣ�����һ��ѡ�񴰿�
*���������int type
*����ֵ����
*/
void dialogdata(int type)
{
    GtkWidget *dialog;
    int flag;
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_OK_CANCEL,
                                    "�Ƿ�������һ�ڵ���Ϣ��");
    gtk_window_set_title(GTK_WINDOW(dialog), "����ڵ�");
    flag=gtk_dialog_run(GTK_DIALOG(dialog));
    switch(flag)
    {
    case GTK_RESPONSE_OK:
    {
        entry_info(type);
        break;
    }
    case GTK_RESPONSE_CANCEL:
    {
        if(type==5)
            break;
        else
            entry_info(type+1);
        break;
    }
    }
    gtk_widget_destroy(dialog);
}

/*****************************************************/
/**************�����**************/
/**
*��������insert_info
*���ܣ�����һ�������
*���������int type
*����ֵ����
*/
void insert_info(GtkWidget *button,int type)
{
    GtkWidget *entry_window;
    GtkWidget *label,*b_ok,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry[7];
    struct transfer*nodec;
    int i;

    entry_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(entry_window,350,300);
    gtk_window_set_title(GTK_WINDOW(entry_window),"�������ڵ�����");
    g_signal_connect(G_OBJECT(entry_window),"destroy",
                     G_CALLBACK(gtk_widget_destroy),NULL);
    gtk_window_set_position(GTK_WINDOW(entry_window),GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (GTK_WINDOW(entry_window),1);

    vbox = gtk_vbox_new (FALSE, 12);
    gtk_container_add (GTK_CONTAINER (entry_window), vbox);
    /*������Ҫ�����ṹ*/
    nodec=(struct transfer *)malloc(sizeof(struct transfer));

    table = gtk_table_new(NODE_NUMBER[type]+1,7,TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);

    for(i=0; i<NODE_NUMBER[type]; i++)
    {
        label = gtk_label_new(Str_Pointer[type-3][i]);
        gtk_table_attach(GTK_TABLE(table),label,1,3,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        entry[i] = gtk_entry_new();
        gtk_table_attach(GTK_TABLE(table),entry[i],3,7,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        nodec->entry[i]=entry[i];
    }

    nodec->window = entry_window;
    nodec->type=type;

    b_ok=gtk_button_new_with_label("ȷ��");
    g_signal_connect(G_OBJECT(b_ok),"clicked",G_CALLBACK(insert_data),nodec);
    gtk_table_attach(GTK_TABLE(table),b_ok,1,2,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    b_cancel=gtk_button_new_with_label("ȡ��");
    g_signal_connect(G_OBJECT(b_cancel),"clicked",G_CALLBACK(close),entry_window);
    gtk_table_attach(GTK_TABLE(table),b_cancel,5,6,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    gtk_widget_show_all(entry_window);
}
/***********************************************/
/*************�༭��**************/
/**
*��������edit_info
*���ܣ�����һ���༭��
*���������int type
*����ֵ����
*/
void edit_info(GtkWidget *button,int type)
{
    GtkWidget *edit_window;
    GtkWidget *label,*b_ok,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry[7];
    struct transfer *nodec;
    int i;
    edit_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(edit_window,400,300);
    gtk_window_set_title(GTK_WINDOW(edit_window),"������޸Ľڵ�����");
    g_signal_connect(G_OBJECT(edit_window),"destroy",
                     G_CALLBACK(gtk_widget_destroy),NULL);
    gtk_window_set_position(GTK_WINDOW(edit_window),GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new (FALSE, 12);
    gtk_container_add (GTK_CONTAINER (edit_window), vbox);

    nodec=(struct transfer *)malloc(sizeof(struct transfer));

    table = gtk_table_new(NODE_NUMBER[type]+1,7,TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);

    for(i=0; i<NODE_NUMBER[type]; i++)
    {
        label = gtk_label_new((Str_Pointer[type-3][i]));
        gtk_table_attach(GTK_TABLE(table),label,1,3,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        entry[i] = gtk_entry_new();
        gtk_table_attach(GTK_TABLE(table),entry[i],3,7,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        nodec->entry[i]=entry[i];
    }
    nodec->window = edit_window;
    nodec->type=type;

    b_ok=gtk_button_new_with_label("ȷ��");
    g_signal_connect(G_OBJECT(b_ok),"clicked",G_CALLBACK(edit_data),nodec);
    gtk_table_attach(GTK_TABLE(table),b_ok,1,2,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    b_cancel=gtk_button_new_with_label("ȡ��");
    g_signal_connect(G_OBJECT(b_cancel),"clicked",G_CALLBACK(close),edit_window);
    gtk_table_attach(GTK_TABLE(table),b_cancel,5,6,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    gtk_widget_show_all(edit_window);
};
/**********************************************************/
/***************ɾ����****************/
/**
*��������delete_info
*���ܣ�����һ��ɾ����
*���������int type
*����ֵ����
*/
void delete_info(GtkWidget *button,int type)
{
    GtkWidget *entry_window;
    GtkWidget *label,*b_ok,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry[7];
    struct transfer *nodec;
    int i;
    entry_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(entry_window,350,300);
    gtk_window_set_title(GTK_WINDOW(entry_window),"�����ɾ���ڵ�����");
    g_signal_connect(G_OBJECT(entry_window),"destroy",
                     G_CALLBACK(gtk_widget_destroy),NULL);
    gtk_window_set_position(GTK_WINDOW(entry_window),GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (GTK_WINDOW(entry_window),1);

    vbox = gtk_vbox_new (FALSE, 12);
    gtk_container_add (GTK_CONTAINER (entry_window), vbox);
    /*���ݲ����ṹ*/
    nodec=(struct transfer *)malloc(sizeof(struct transfer));
    table = gtk_table_new(NODE_NUMBER[type]+1,7,TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);

    for(i=0; i<NODE_NUMBER[type]; i++)
    {
        label = gtk_label_new(Str_Pointer[type][i]);
        gtk_table_attach(GTK_TABLE(table),label,1,3,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        entry[i] = gtk_entry_new();
        gtk_table_attach(GTK_TABLE(table),entry[i],3,7,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        nodec->entry[i]=entry[i];
    }
    nodec->window = entry_window;
    nodec->type=type;
    b_ok=gtk_button_new_with_label("ȷ��");
    g_signal_connect(G_OBJECT(b_ok),"clicked",G_CALLBACK(delete_data),nodec);
    gtk_table_attach(GTK_TABLE(table),b_ok,1,2,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    b_cancel=gtk_button_new_with_label("ȡ��");
    g_signal_connect(G_OBJECT(b_cancel),"clicked",G_CALLBACK(close),entry_window);
    gtk_table_attach(GTK_TABLE(table),b_cancel,5,6,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    gtk_widget_show_all(entry_window);
}
/*************************************************/
/**************��ѯ��****************/
/**
*��������query_info
*���ܣ����ݲ�ѯ��
*��������� int type
*����ֵ����
*/
void query_info(GtkWidget *button,int type)
{
    GtkWidget *entry_window;
    GtkWidget *label,*b_ok,*b_cancel;
    GtkWidget *table;
    GtkWidget *vbox;
    GtkWidget *entry[7];
    struct transfer*nodec;
    int i;
    entry_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(entry_window,350,300);
    gtk_window_set_title(GTK_WINDOW(entry_window),"��ѯ");
    g_signal_connect(G_OBJECT(entry_window),"destroy",
                     G_CALLBACK(gtk_widget_destroy),NULL);
    gtk_window_set_position(GTK_WINDOW(entry_window),GTK_WIN_POS_CENTER);
    gtk_window_set_keep_above (GTK_WINDOW(entry_window),1);

    vbox = gtk_vbox_new (FALSE, 12);
    gtk_container_add (GTK_CONTAINER (entry_window), vbox);
    /*���ݲ����ṹ*/
    nodec=(struct transfer *)malloc(sizeof(struct transfer));

    table = gtk_table_new(NODE_NUMBER[type]+1,7,TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 10);

    for(i=0; i<NODE_NUMBER[type]; i++)
    {
        label = gtk_label_new(Str_Pointer[type][i]);
        gtk_table_attach(GTK_TABLE(table),label,1,3,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        entry[i] = gtk_entry_new();
        gtk_table_attach(GTK_TABLE(table),entry[i],3,7,i,i+1,
                         GTK_EXPAND, GTK_EXPAND,0,0);
        nodec->entry[i]=entry[i];
    }

    nodec->window = entry_window;
    nodec->type=type;
    b_ok=gtk_button_new_with_label("ȷ��");
    g_signal_connect(G_OBJECT(b_ok),"clicked",G_CALLBACK(query_data),nodec);
    gtk_table_attach(GTK_TABLE(table),b_ok,1,2,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    b_cancel=gtk_button_new_with_label("ȡ��");
    g_signal_connect(G_OBJECT(b_cancel),"clicked",G_CALLBACK(close),entry_window);
    gtk_table_attach(GTK_TABLE(table),b_cancel,5,6,NODE_NUMBER[type],NODE_NUMBER[type]+1,
                     GTK_EXPAND, GTK_EXPAND,0,0);
    gtk_widget_show_all(entry_window);
}
/**********************************************************/



