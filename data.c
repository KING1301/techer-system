#include "my.h"
/****************读取与存储*********************/
/**
*函数名：LoadList
*功能：读取数据文件中数据到链表中
*输入参数：phead 教师节点头指针的地址
*返回值：re 0空链
               4已加载教师信息
                12已加载教师信息和工作量信息
                28 已全部
*/
int LoadList(TEACHER_NODE **phead)
{
    TEACHER_NODE *hd=NULL,*pTeacher;
    WORK_NODE *pWork;
    TEACHER_WORK_NODE *pTeacher_Work;
    FILE *pFile;
    int re=0;
    if((pFile=fopen("teacher.dat","rb"))==NULL)
    {
        return re;
    }
    /*从数据文件中读取教师基本信息数据，存入以后进先出方式建立的主链中*/
    while(!feof(pFile))
    {
        pTeacher=(TEACHER_NODE*)calloc(1,sizeof(TEACHER_NODE));
        fread(pTeacher,sizeof(TEACHER_NODE),1,pFile);
        if(!feof(pFile))
        {
            pTeacher->work_node=NULL;
            pTeacher->next=hd;
            hd=pTeacher;
        }
    }
    fclose(pFile);
    if(hd==NULL)
    {
        return re;
    }
    *phead=hd;
    re +=4;
    if((pFile=fopen("work.dat","rb"))==NULL)
    {
        return re;
    }
    re +=8;

    /*从数据文件中读取工作量基本信息数据，存入主链对应结点的工作量基本信息支链中*/
    while(!feof(pFile))
    {
        /*创建结点，存放从数据文件中读出的工作量基本信息*/
        pWork=(WORK_NODE*)calloc(1,sizeof(WORK_NODE));
        fread(pWork,sizeof(WORK_NODE),1,pFile);
        if(!feof(pFile))
        {
            pWork->teacher_work_node=NULL;
            /*在主链上查找该编号ID对应的主链结点*/
            pTeacher=hd;
            while(pTeacher!=NULL&&strcmp(pTeacher->number,pWork->number))
            {
                pTeacher=pTeacher->next;
            }

            /*如果找到，则将结点以后进先出方式插入教师信息*/
            if(pTeacher!=NULL)
            {
                pWork->next=pTeacher->work_node;
                pTeacher->work_node=pWork;
            }
            else  /*如果未找到，则释放所创建结点的内存空间*/
            {
                free(pWork);
            }
        }

    }
    fclose(pFile);
    if((pFile=fopen("teacher_work.dat","rb"))==NULL)
    {
        return re;
    }
    re +=16;

    /*从数据文件读入教学工作基本信息数据，存入工作量基本信息支链对应结点的教学基本信息支链中*/
    while (!feof(pFile))
    {
        /*创建结点，存放从数据文件中读出的教学工作基本信息*/
        pTeacher_Work = (TEACHER_WORK_NODE *)calloc(1,sizeof(TEACHER_WORK_NODE));
        fread(pTeacher_Work, sizeof(TEACHER_WORK_NODE), 1, pFile);
        if(!feof(pFile))
        {
            /*查找工作量基本信息支链上对应教学基本信息结点*/
            pTeacher= hd;
            while (pTeacher!= NULL && strcmp(pTeacher->number,pTeacher_Work->number))
            {
                pTeacher=pTeacher->next;
            }
            if(pTeacher!=NULL)
            {
                pWork= pTeacher->work_node;
                while(pWork!=NULL&&strcmp(pWork->year,pTeacher_Work->year))
                {
                    pWork=pWork->next;
                }
                if(pWork!=NULL)
                {
                    pTeacher_Work->next=pWork->teacher_work_node;/*找到工作量节点则以后进先出方式创建教学基本信息链表*/
                    pWork->teacher_work_node=pTeacher_Work;
                }
                else
                {
                    free(pTeacher_Work);//如果未找到工作量信息，则释放
                }
            }
            else /*如果未找到教师信息，则释放所创建结点的内存空间*/
            {
                free(pTeacher_Work);
            }
        }
    }

    fclose(pFile);
    return re;
}
/*********************************************/
/**
*函数名：addtree
*功能：将链表中节点添加到树状列表中
*输入参数：
*返回值：
*/
void addtree()
{
    GtkTreeModel *model;
    TEACHER_NODE *p1;
    WORK_NODE *p2;
    TEACHER_WORK_NODE *p3;
    for(p1=gp_head; p1!=NULL; p1=p1->next)
    {
        gtk_tree_store_append(treestore,&p1->iter,&rootiter);   /*添加数据*/
        gtk_tree_store_set(treestore,&p1->iter,                 /*添加数据的文本显示*/
                           COLUMN,p1->number,
                           -1);
        for(p2=p1->work_node; p2!=NULL; p2=p2->next)
        {
            gtk_tree_store_append(treestore,&p2->iter,&p1->iter);
            gtk_tree_store_set(treestore,&p2->iter,
                               COLUMN,p2->year,
                               -1);
            for(p3=p2->teacher_work_node; p3!=NULL; p3=p3->next)
            {
                gtk_tree_store_append(treestore,&p3->iter,&p2->iter);
                gtk_tree_store_set(treestore,&p3->iter,
                                   COLUMN,p3->Class,
                                   -1);
            }
        }
    }
    model=GTK_TREE_MODEL(treestore);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
    g_object_unref(model);
}
/**********************************************/
/**
*函数名：LoadData
*功能：读取数据文件
*输入参数：
*返回值：
*/
int  LoadData(GtkWidget*button)
{

    int re;
    if(count==1)
    {
        dialog_info("数据已加载");
        return 0;
    }
    re=LoadList(&gp_head);
    if(re==0)
        dialog_info("不存在数据");
    else
    {
        if(re==4)
        {
            addtree();
            dialog_info("教师数据加载完成");
        }
        else
        {
            if(re==12)
            {
                addtree();
                dialog_info("教师数据工作量数据加载完成");
            }
            else
            {
                addtree();
                dialog_info("全部数据加载完成");
            }
        }
        count++;/*如果数据加载成功则记录*/
    }
    return 0;
}
/***********************************************/
/**
*函数名：Savelist
*功能：将链表中数据存储在数据文件中
*输入参数：phead教师节点头指针
*返回值：flag 记录了三个数据文件是否成功保存
*/
int SaveList(TEACHER_NODE *phead)
{
    FILE *fout1,*fout2,*fout3;
    TEACHER_NODE *p1=phead;
    WORK_NODE *p2;
    TEACHER_WORK_NODE *p3;
    int flag=0;
    if((fout1=fopen("teacher.dat","wb"))==NULL)
        return flag;
    flag+=4;
    if((fout2=fopen("work.dat","wb"))==NULL)
        return flag;
    flag+=8;
    if((fout3=fopen("teacher_work.dat","wb"))==NULL)
        return flag;
    flag+=16;
    while(p1!=NULL)
    {
        fwrite(p1,sizeof(TEACHER_NODE),1,fout1);
        p2=p1->work_node;
        while(p2!=NULL)
        {
            fwrite(p2,sizeof(WORK_NODE),1,fout2);
            p3=p2->teacher_work_node;
            while(p3!=NULL)
            {
                fwrite(p3,sizeof(TEACHER_WORK_NODE),1,fout3);
                p3=p3->next;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
    fclose(fout1);
    fclose(fout2);
    fclose(fout3);
    return (flag);
}
/******************************************************/
/**
*函数名：SaveData
*功能：存储数据文件
*输入参数：
*返回值：
*/
int SaveData(GtkWidget *button)
{
    int flag=0;
    flag=SaveList(gp_head);
    if(flag==28)
    {
        dialog_info("数据保存成功");
    }
    else
        dialog_info("数据保存失败");
    return (flag);
}

/******************************************/
/**
*函数名：quit_save
*功能：提示保存
*输入参数：
*返回值：
*/
void quit_save(GtkWidget *button)
{
    GtkWidget *dialog;
    int flag;
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_OK_CANCEL,
                                    "退出前是否保存当前数据？");
    flag=gtk_dialog_run(GTK_DIALOG(dialog));
    switch(flag)
    {
    case GTK_RESPONSE_OK:
        SaveList(gp_head);
    case GTK_RESPONSE_CANCEL:
        gtk_main_quit();
    default:
        ;
    }
    gtk_widget_destroy(dialog);
}
