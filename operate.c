#include "my.h"
/**
*函数名：TEACHER_search
*功能：按id搜索教师
*输入参数：number教师编号
*返回值：教师节点指针
*/
TEACHER_NODE *TEACHER_search(char *number)
{
    TEACHER_NODE *pSearch;
    int flag=1;
    pSearch=gp_head;
    while((flag=strcmp(number,pSearch->number))&&pSearch->next!=NULL)
    {
        pSearch=pSearch->next;
    }
    if(!flag)
        return(pSearch);
    else
    {
        dialog_info("无对应id教师！");
        return(NULL);
    }
}
/******************************************/
/**
*函数名：WORK_search
*功能：按照年份搜索工作量节点
*输入参数：year 年份，WORK 所在教师工作量节点指针
*返回值：工作量节点节点指针
*/
WORK_NODE *WORK_search(char *year,WORK_NODE *pWORK)
{
    if(pWORK==NULL)
    {
        dialog_info("未输入工作量信息");
        return NULL;
    }
    WORK_NODE *pSearch;
    pSearch=pWORK;
    int flag=1;
    while((flag=strcmp(year,pSearch->year))&&(pSearch->next)!=NULL)
    {
        pSearch=pSearch->next;
    }
    if(!flag)
        return(pSearch);
    else
    {
        dialog_info("无对应工作量！");
        return(NULL);
    }
}
/********************************************/
/**
*函数名：TEACHER_WORK_search
*功能：按Class搜索教学信息节点
*输入参数: Class,班级名，WORK 所属工作量节点指针
*返回值：教学信息节点节点指针
*/
TEACHER_WORK_NODE *TEACHER_WORK_search(char *Class,TEACHER_WORK_NODE *pTEACHER_WORK)
{
    if(pTEACHER_WORK==NULL)
    {
        dialog_info("未输入教学信息");
        return NULL;
    }
    TEACHER_WORK_NODE *pSearch;
    pSearch=pTEACHER_WORK;
    int flag=1;
    while((flag=strcmp(Class,pSearch->Class))&&pSearch->next!=NULL)
    {
        pSearch=pSearch->next;
    }
    if(!flag)
        return(pSearch);
    else
    {
        dialog_info("无对应教学信息！");
        return(NULL);
    }
}

/***********录入节点*******************/
/**************************************************/
/**
*函数名：input_work
*功能：添加工作量节点函数，由input中情况3调用
*输入参数：pNew 指向新节点的指针
*返回值：对应教师基本信息节点指针
*/
TEACHER_NODE *input_work(WORK_NODE *pNew)
{
    TEACHER_NODE *pTEACHER;
    WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(pTEACHER);/*未找到对应教师则结束函数*/
    if(pTEACHER->work_node==NULL)/*如果插入的是头节点，则直接插入*/
    {
        pTEACHER->work_node=pNew;
        pNew->next=NULL;
    }

    else
    {
        pSEARCH=pTEACHER->work_node;
        while(pSEARCH->next!=NULL)
            pSEARCH=pSEARCH->next;
        pSEARCH->next=pNew;
        pNew->next=NULL;
    }

    return(pTEACHER);
}
/****************************************************/
/**
*函数名：input_teacher_work
*功能：添加教学基本信息节点函数，由input中情况4调用
*输入参数：pNew 指向新节点的指针
*返回值：对应工作量节点指针
*/
WORK_NODE *input_teacher_work(TEACHER_WORK_NODE *pNew)
{
    TEACHER_NODE*pTEACHER;
    WORK_NODE *pWORK;
    TEACHER_WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(NULL);/*未找到教师则结束函数*/
    pWORK=WORK_search(pNew->year,pTEACHER->work_node);
    if(pWORK==NULL)
        return(NULL); /*未找到工作量则结束函数*/
    if(pWORK->teacher_work_node==NULL)
    {
        pWORK->teacher_work_node=pNew;
        pNew->next=NULL;
    }


    else
    {
        pSEARCH=pWORK->teacher_work_node;
        while(pSEARCH->next!=NULL)
            pSEARCH=pSEARCH->next;
        pSEARCH->next=pNew;
        pNew->next=NULL;
    }
    return(pWORK);

}
/******************************************/
/**
*函数名：input_data
*功能：录入节点
*输入参数：struct transfer*nodec
*返回值：无
*/
void input_data(GtkWidget*button,struct transfer*nodec)
{
    GtkTreeModel *model;
    int error=0;
    char *str;
    switch(nodec->type)
    {
    case 3:/*输入教师基本信息*/
    {
        TEACHER_NODE *pNew;
        TEACHER_NODE*pSEARCH;
        pNew = (TEACHER_NODE *)calloc(1, sizeof(TEACHER_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->name,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        strcpy(pNew->company,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        strcpy(pNew->title,str);
        pNew->work_node=NULL;
        if(gp_head==NULL)
        {
            gp_head=pNew;
            pNew->next=NULL;
        }
        else
        {
            pSEARCH=gp_head;
            while(pSEARCH->next!=NULL)
                pSEARCH=pSEARCH->next;
            pSEARCH->next=pNew;
            pNew->next=NULL;
        }
        gtk_tree_store_append(treestore,&pNew->iter,&rootiter);
        gtk_tree_store_set(treestore,&pNew->iter,COLUMN,pNew->number,-1);
        break;
    }
    case 4:/*输入工作量节点*/
    {
        TEACHER_NODE*pTeacher;
        WORK_NODE*pNew;
        pNew = (WORK_NODE*)calloc(1, sizeof(WORK_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->year,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        pNew->working=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        pNew->member=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
        pNew->element=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
        pNew->goal=atoi(str);
        pNew->teacher_work_node=NULL;
        if((pTeacher=input_work(pNew))!=NULL) /*使用input_Work函数*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pTeacher->iter);/*添加数据*/
            gtk_tree_store_set(treestore,&pNew->iter,COLUMN,pNew->year,-1); /*添加数据的文本显示*/
        }
        else
        {
            error=1;
            free(pNew);
        }

        break;
    }
    case 5:/*输入教学工作信息结点*/
    {
        WORK_NODE*pWork;
        TEACHER_WORK_NODE *pNew;
        pNew = (TEACHER_WORK_NODE *)calloc(1,sizeof(TEACHER_WORK_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->year,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        strcpy(pNew->Class,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        pNew->teaching_hours=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
        pNew->experimental_hours=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
        pNew->student_member=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
        strcpy(pNew->program,str);
        if((pWork=input_teacher_work(pNew))!=NULL) /*使用input_Teacher_Work函数*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pWork->iter);/*添加数据*/
            gtk_tree_store_set(treestore,&pNew->iter,COLUMN,pNew->Class,-1);       /*添加数据的文本显示*/
        }
        else
        {
            error=1;
            free(pNew);
        }

        break;
    }
    default:
        dialog_info("数据非法!");
    }
    if(error==0)
    {
        model=GTK_TREE_MODEL(treestore);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);/*连接model和view*/
    }
    else
    {
        dialog_info("失败!");

    }
    gtk_widget_destroy(nodec->window);
    /*弹出选择提示框*/
    dialogdata(nodec->type);
    free(nodec);

}
/***************************************/
/****************插入节点***************/
/**
*函数名：insert_WORK
*功能：插入工作量节点函数，由insert_data中情况3调用
*输入参数：pNew 指向新节点的指针
*返回值：对应教师节点指针
*/
TEACHER_NODE *insert_WORK(WORK_NODE *pNew)
{
    TEACHER_NODE *pTEACHER;
    WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(NULL);/*未找到对应教师则结束函数*/
    if(pTEACHER->work_node==NULL)
    {
        pTEACHER->work_node=pNew;
        pNew->next=NULL;
    }

    else
    {
        pSEARCH=pTEACHER->work_node;
        while(pSEARCH->next!=NULL)
            pSEARCH=pSEARCH->next;
        pSEARCH->next=pNew;
        pNew->next=NULL;

    }
    return(pTEACHER);
}
/********************************************/
/**
*函数名：insert_TEACHER_WORK
*功能：插入教学信息节点函数，由insert_data中情况4调用
*输入参数：pNew 指向新节点的指针
*返回值：对应教学信息节点指针
*/
WORK_NODE *insert_TEACHER_WORK(TEACHER_WORK_NODE *pNew)
{
    TEACHER_NODE *pTEACHER;
    WORK_NODE *pWORK;
    TEACHER_WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(NULL);/*未找到对应教师则结束函数*/

    pWORK=WORK_search(pNew->year,pTEACHER->work_node);
    if(pWORK==NULL)
        return(NULL);/*未找到对应工作量则结束函数*/
    if(pWORK->teacher_work_node==NULL)
    {
        pWORK->teacher_work_node=pNew;
        pNew->next=NULL;
    }

    else
    {
        pSEARCH=pWORK->teacher_work_node;
        while(pSEARCH->next!=NULL)
            pSEARCH=pSEARCH->next;
        pSEARCH->next=pNew;
        pNew->next=NULL;
    }
    return(pWORK);
}
/**********************************************/
/**
*函数名：insert_data
*功能：插入3种节点统一函数，由insert_info确定按钮调用
*输入参数：
*返回值：无
*/
void insert_data(GtkWidget *button,struct transfer *nodec)
{
    GtkTreeModel *model;
    int error=0;
    char *str;
    switch(nodec->type)
    {
    case 3:/*插入教师节点*/
    {
        TEACHER_NODE *pNew;
        TEACHER_NODE*pSEARCH;
        pNew = (TEACHER_NODE *)calloc(1, sizeof(TEACHER_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->name,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        strcpy(pNew->company,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        strcpy(pNew->title,str);
        pNew->next=NULL;
        if(gp_head==NULL)
        {
            gp_head=pNew;
            pNew->next=NULL;
        }

        else
        {
            pSEARCH=gp_head;
            while(pSEARCH->next!=NULL)
                pSEARCH=pSEARCH->next;
            pSEARCH->next=pNew;
        }
        gtk_tree_store_append(treestore,&pNew->iter,&rootiter);
        gtk_tree_store_set(treestore,&pNew->iter,
                           COLUMN,pNew->number,
                           -1);
        break;
    }
    case 4:/*插入工作量节点*/
    {
        TEACHER_NODE *pTEACHER;
        WORK_NODE *pNew;
        pNew = (WORK_NODE *)calloc(1, sizeof(WORK_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->year,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        pNew->working=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        pNew->member=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
        pNew->element=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
        pNew->goal=atoi(str);
        pNew->teacher_work_node=NULL;
        if((pTEACHER=insert_WORK(pNew))!=NULL) /*使用insert_WORK函数*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pTEACHER->iter);/*添加数据*/
            gtk_tree_store_set(treestore,&pNew->iter,        /*添加数据的文本显示*/
                               COLUMN,pNew->year,
                               -1);
        }
        else
        {
            error=1;
            free(pNew);
        }

        break;
    }
    case 5:/*插入教学信息节点*/
    {
        WORK_NODE *pWORK;
        TEACHER_WORK_NODE *pNew;
        pNew = (TEACHER_WORK_NODE *)calloc(1,sizeof(TEACHER_WORK_NODE));/*获取输入框输入的信息*/
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->year,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        strcpy(pNew->Class,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        pNew->teaching_hours=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
        pNew->experimental_hours=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
        pNew->student_member=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
        strcpy(pNew->program,str);


        if((pWORK=insert_TEACHER_WORK(pNew))!=NULL) /*使用insert_TEACHER_WORK函数*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pWORK->iter);/*添加数据*/
            gtk_tree_store_set(treestore,&pNew->iter,        /*添加数据的文本显示*/
                               COLUMN,pNew->Class,
                               -1);
        }
        else
        {
            error=1;
            free(pNew);
        }

        break;
    }
    default:
        dialog_info("插入失败!");
    }
    if(error==0)
    {
        model=GTK_TREE_MODEL(treestore);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);/*连接model和view*/
        dialog_info("插入成功！");
    }
    gtk_widget_destroy(nodec->window);
    free(nodec);
}
/*******************************************/
/**************编辑节点*******************/
/**
*函数名：edit_data
*功能：编辑节点
*输入参数：
*返回值：无
*/
void  edit_data(GtkWidget *button,struct transfer *nodec)
{
    GtkTreeIter iter;
    char *str;
    int error=0;
    switch(nodec->type)
    {
    case 3:/*编辑教师节点*/
    {
        TEACHER_NODE *pNew;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        pNew=TEACHER_search(str);
        if(pNew==NULL)
        {
            error=1;
            break;
        }
        iter=pNew->iter;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->name,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        strcpy(pNew->company,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        strcpy(pNew->title,str);
        break;
    }
    case 4:
    {
        TEACHER_NODE*pTEACHER;
        WORK_NODE*pNew;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        pTEACHER=TEACHER_search(str);
        if(pTEACHER==NULL)
        {
            error=1;
            break;
        }
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        pNew=WORK_search(str,pTEACHER->work_node);
        if(pNew==NULL)
        {
            error=1;
            break;
        }
        iter=pNew->iter;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->year,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        pNew->working=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        pNew->member=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
        pNew->element=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
        pNew->goal=atoi(str);
        break;
    }
    case 5:
    {
        TEACHER_NODE*pTEACHER;
        WORK_NODE*pWORK;
        TEACHER_WORK_NODE*pNew;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
        pTEACHER=TEACHER_search(str);
        if(pTEACHER==NULL)
        {
            error=1;
            break;
        }
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        pWORK=WORK_search(str,pTEACHER->work_node);
        if(pWORK==NULL)
        {
            error=1;
            break;
        }
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        pNew=TEACHER_WORK_search(str,pWORK->teacher_work_node);
        if(pNew==NULL)
        {
            error=1;
            break;
        }
        iter=pNew->iter;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
        strcpy(pNew->number,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        strcpy(pNew->year,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        strcpy(pNew->Class,str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[3]));
        pNew->teaching_hours=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[4]));
        pNew->experimental_hours=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[5]));
        pNew->student_member=atoi(str);
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[6]));
        strcpy(pNew->program,str);
        break;
    }
    }
    if(error==0)
    {
        dialog_info("修改成功");
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(treestore));
        expand_iter(iter);
    }
    gtk_widget_destroy(nodec->window);
    free(nodec);
}
/***************************************/
/****************删除节点**********************/
/**
*函数名：delete_teacher
*功能：删除教师信息节点
*输入参数：struct transfer*nodec
*返回值：int 1为有错，0为正常
*/
int delete_teacher(struct transfer*nodec)
{
    int error=0;
    char*str;
    TEACHER_NODE *pSEARCH,*pPRE;
    WORK_NODE*p1;
    TEACHER_WORK_NODE*p2;
    int flag=1;
    pSEARCH=gp_head;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框输入的信息*/
    if(!(flag=strcmp(str,pSEARCH->number)))/*找到对应的教师节点并删除教师节点下的工作量节点和教学信息节点*/
    {
        p1=pSEARCH->work_node;
        while(p1!=NULL)
        {
            p2=p1->teacher_work_node;
            while(p2!=NULL)
            {
                p1->teacher_work_node=p2->next;
                free(p2);
                p2=p1->teacher_work_node;
            }
            pSEARCH->work_node=p1->next;
            free(p1);
            p1=pSEARCH->work_node;
        }
        gp_head=gp_head->next;
        gtk_tree_store_remove(treestore,&pSEARCH->iter);  /*删除树状列表对应iter*/
        free(pSEARCH);/*释放教师节点内存*/
        dialog_info("删除成功");
        return 0;
    }
    do
    {
        pPRE=pSEARCH;
        pSEARCH=pSEARCH->next;
        if(pSEARCH==NULL)
            break;
    }
    while((flag=strcmp(str,pSEARCH->number)));
    if(!flag)
    {
        p1=pSEARCH->work_node;
        while(p1!=NULL)
        {
            p2=p1->teacher_work_node;
            while(p2!=NULL)
            {
                p1->teacher_work_node=p2->next;
                free(p2);
                p2=p1->teacher_work_node;
            }
            pSEARCH->work_node=p1->next;
            free(p1);
            p1=pSEARCH->work_node;
        }
        pPRE->next=pSEARCH->next;  /*将前一节点直接连至后一节点*/
        gtk_tree_store_remove(treestore,&pSEARCH->iter);/*删除树状列表对应iter*/
        free(pSEARCH);
    }
    else
    {
        dialog_info("无对应教师！");
        return(1);
    }
    if(error==0)
        dialog_info("删除成功！");
    return 0;
}
/*******************************************/
/**
*函数名：delete_work
*功能：删除工作量信息节点
*输入参数：struct transfer*nodec
*返回值：int 1为有错，0为正常
*/
int delete_work(struct transfer*nodec)
{
    int flag=1,error=0;
    char *str;
    TEACHER_NODE *pTEACHER;
    WORK_NODE *pSEARCH,*pPRE;
    TEACHER_WORK_NODE*p1;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
    pTEACHER=TEACHER_search(str); /*调用TEACHER_search函数搜索对应教师节点*/
    if(pTEACHER==NULL)
        return 1;
    pSEARCH=pTEACHER->work_node;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
    if(!(flag=strcmp(str,pSEARCH->year)))
    {
        p1=pSEARCH->teacher_work_node;
        while(p1!=NULL)
        {
            pSEARCH->teacher_work_node=p1->next;
            free(p1);
            p1=pSEARCH->teacher_work_node;
        }
        pTEACHER->work_node=pSEARCH->next;
        gtk_tree_store_remove(treestore,&pSEARCH->iter);
        free(pSEARCH);
        dialog_info("删除成功");
        return 0;
    }

    do
    {
        pPRE=pSEARCH;
        pSEARCH=pSEARCH->next;
        if(pSEARCH==NULL)
            break;
    }
    while((flag=strcmp(str,pSEARCH->year)));
    if(!flag)
    {
        p1=pSEARCH->teacher_work_node;
        while(p1!=NULL)
        {
            pSEARCH->teacher_work_node=p1->next;
            free(p1);
            p1=pSEARCH->teacher_work_node;
        }
        pPRE->next=pSEARCH->next;
        gtk_tree_store_remove(treestore,&pSEARCH->iter);
        free(pSEARCH);
    }
    else
    {
        dialog_info("无对应工作量！");
        gtk_widget_destroy(nodec->window);
        return(1);
    }
    if(error==0)
        dialog_info("删除成功！");
    return 0;
}
/**********************************************************/
/**
*函数名：delete_teacher_work
*功能：删除教学信息节点
8输入参数：struct transfer*nodec
*返回值：int 1为有错，0为正常
*/
int delete_teacher_work(struct transfer*nodec)
{
    int flag=1,error=0;
    TEACHER_NODE *pTEACHER;
    WORK_NODE *pWORK;
    TEACHER_WORK_NODE *pSEARCH,*pPRE;
    char*str;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
    pTEACHER=TEACHER_search(str);
    if(pTEACHER==NULL)
        return 1;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
    pWORK=WORK_search(str,pTEACHER->work_node);
    if(pWORK==NULL)
        return 0;
    pSEARCH=pWORK->teacher_work_node;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
    if(!(flag=strcmp(str,pSEARCH->Class)))
    {
        pWORK->teacher_work_node=pSEARCH->next;
        gtk_tree_store_remove(treestore,&pSEARCH->iter);
        free(pSEARCH);
        dialog_info("删除成功");
        return 0;
    }
    do
    {
        pPRE=pSEARCH;
        pSEARCH=pSEARCH->next;
        if(pSEARCH==NULL)
            break;
    }
    while((flag=strcmp(str,pSEARCH->Class)));
    if(!flag)
    {
        pPRE->next=pSEARCH->next;
        gtk_tree_store_remove(treestore,&pSEARCH->iter);
        free(pSEARCH);
    }
    else
    {
        dialog_info("无对应教学基本人员！");
        return(1);
    }
    if(error==0)
        dialog_info("删除成功！");
    return 0;
}
/******************************************/
/**
*函数名：delete_data
*功能：struct transfer*nodec
*输入参数:
*返回值：无
*/
void delete_data(GtkWidget*button,struct transfer*nodec)
{
    switch(nodec->type)
    {
    case 0:
    {
        delete_teacher(nodec);
        break;
    }

    case 1:
    {
        delete_work(nodec);
        break;
    }
    case 2:
    {
        delete_teacher_work(nodec);
        break;
    }
    default:
        ;
    }
    gtk_widget_destroy(nodec->window);
    free(nodec);
}
/******************************************************/
/******************查询节点*******************/
/**
*函数名：expand_iter
*功能：展开并跳转至指定iter
*输入参数：iter treeview中的一个目标iter
*返回值：无
*/
void expand_iter(GtkTreeIter iter)
{
    GtkTreeModel *model;
    GtkTreeSelection *select;
    GtkTreePath *path;
    select = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    path = gtk_tree_model_get_path(model,&iter);
    gtk_tree_view_expand_to_path(GTK_TREE_VIEW(treeview),path);
    gtk_tree_selection_select_iter(select,&iter);
    Show_data(iter);
}

/****************************************************/
/**
*函数名：query_data
*功能：查询基本信息
*输入参数：struct transfer*nodec
*返回值：无
*/
void query_data(GtkWidget*button,struct transfer*nodec)
{
    char *str;
    TEACHER_NODE *pTEACHER;
    WORK_NODE *pWORK;
    TEACHER_WORK_NODE*pTEACHER_WORK;
    switch(nodec->type)
    {
    case 0:
    {
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框数据*/
        pTEACHER=TEACHER_search(str);
        if(pTEACHER!=NULL)
        {
            expand_iter(pTEACHER->iter);
        }
        break;
    }
    case 1:
    {
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框数据*/
        pTEACHER=TEACHER_search(str);
        if(pTEACHER==NULL)
            break;

        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        pWORK=WORK_search(str,pTEACHER->work_node);
        if(pWORK!=NULL)
        {
            expand_iter(pWORK->iter);
        }
        break;
    }
    case 2:
    {
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*获取输入框数据*/
        pTEACHER=TEACHER_search(str);
        if(pTEACHER==NULL)
            break;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[1]));
        pWORK=WORK_search(str,pTEACHER->work_node);
        if(pWORK==NULL)
            break;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[2]));
        pTEACHER_WORK=TEACHER_WORK_search(str,pWORK->teacher_work_node);
        if(pTEACHER_WORK!=NULL)
        {
            expand_iter(pTEACHER_WORK->iter);
        }
        break;
    }
    }
    gtk_widget_destroy(nodec->window);
    free(nodec);
}
/**********************************************/
/**********************统计****************************/
/**
*函数名：Statis_table
*功能：弹出一个统计框
*输入参数：title 统计框标题,col1 第一列标题,col2 第二列标题,model 传入的model
*返回值：无
*/
void Statis_table(char *title,char *col1,char *col2,GtkListStore *model)
{
    GtkWidget *statis_window;
    GtkWidget *b_ok;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *list;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn  *column;
    GtkWidget *swin;
    statis_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (statis_window), 0);
    gtk_window_set_title (GTK_WINDOW (statis_window), title);
    gtk_window_set_position (GTK_WINDOW (statis_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(statis_window), 400, 400);

    list = gtk_tree_view_new();      /*创建view等待与传入的model连接*/

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(col1,
             renderer, "text", COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
    column = gtk_tree_view_column_new_with_attributes(col2,
             renderer, "text", COMMENT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    gtk_tree_view_set_model(GTK_TREE_VIEW (list),
                            GTK_TREE_MODEL(model));

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(statis_window), vbox);

    swin = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(swin),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(swin),
                                         GTK_SHADOW_ETCHED_IN);
    gtk_box_pack_start(GTK_BOX(vbox), swin, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER (swin), list);
    hbox=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
    b_ok=gtk_button_new_with_label("确定");
    g_signal_connect(G_OBJECT(b_ok),"clicked",G_CALLBACK(close),statis_window);
    gtk_box_pack_start(GTK_BOX(hbox),b_ok,TRUE,FALSE,0);
    gtk_widget_show_all(statis_window);
}
/***************************************************/
/**
*函数名：statis_fund
*功能：统计历年科研量并排序，调用Statis_table显示统计结果
*输入参数：
*返回值：无
*/
void statis_fund(GtkWidget *button)
{

    struct SORT_NODE *p,*head=NULL;
    TEACHER_NODE*p1;
    WORK_NODE*p2;
    GtkListStore *store;
    store = gtk_list_store_new(2,
                               G_TYPE_STRING,
                               G_TYPE_INT
                              );
    for(p1=gp_head; p1!=NULL; p1=p1->next)
    {
        if(p1->work_node!=NULL)
        {
            p=(struct SORT_NODE *)malloc(sizeof(struct SORT_NODE));
            p->str=p1->name;
            p->counts=0;
            for(p2=p1->work_node; p2!=NULL; p2=p2->next)
            {
                p->counts+=p2->working;
            }
            p->next=head;
            head=p;
        }
    }
    if(head==NULL)
    {
        dialog_info("无统计数据");
        return 0;
    }
    struct SORT_NODE*node_prior,*node_after,*node_cur,*node_temp;/*选择排序法*/
    node_prior=head;
    node_temp=(struct SORT_NODE*)malloc(sizeof(struct SORT_NODE));/*交换节点信息的临时节点*/
    while(node_prior->next!=NULL)
    {
        node_cur=node_prior;
        node_after=node_prior->next;
        while(node_after!=NULL)
        {
            if(node_cur->counts<node_after->counts)
            {
                node_cur=node_after;
            }
            node_after=node_after->next;
        }
        if(node_cur!=node_prior)/*交换节点信息，指针域不变*/
        {
            *node_temp=*node_prior;
            *node_prior=*node_cur;
            node_prior->next=node_temp->next;
            node_temp->next=node_cur->next;
            *node_cur=*node_temp;
        }
        node_prior=node_prior->next;
    }
    free(node_temp);
    p=head;
    while(p!=NULL)
    {
        gtk_list_store_append(store,&p->iter);/*添加信息到store中*/
        gtk_list_store_set(store,&p->iter,
                           COLUMN,p->str,
                           COMMENT,p->counts,
                           -1);
        p=p->next;
    }
    while(p!=NULL)/*释放统计链表内存*/
    {
        free(p);
        p=p->next;
    }

    Statis_table("科研排名",
                 "姓名",
                 "科研量",
                 store);
}
/*****************************************************/
/**
*函数名：statis_working
*功能：统计历年教学学时并排序，调用Statis_table显示统计结果
*输入参数：
*返回值：无
*/
void statis_working(GtkWidget *button)
{
    struct SORT_NODE *p,*head=NULL;
    TEACHER_NODE*p1;
    WORK_NODE*p2;
    TEACHER_WORK_NODE*p3;
    GtkListStore *store;
    store = gtk_list_store_new(2,
                               G_TYPE_STRING,
                               G_TYPE_INT
                              );
    for(p1=gp_head; p1!=NULL; p1=p1->next)
    {
        for(p2=p1->work_node; p2!=NULL; p2=p2->next)
        {
            if(p2->teacher_work_node!=NULL)
            {
                p=(struct SORT_NODE *)malloc(sizeof(struct SORT_NODE));
                p->str=p1->name;
                p->counts=0;
                for(p3=p2->teacher_work_node; p3!=NULL; p3=p3->next)
                {
                    p->counts+=p3->experimental_hours+p3->teaching_hours;/*计算教师学时*/
                }
                p->next=head;
                head=p;
            }
        }
    }
    if(head==NULL)
    {
        dialog_info("无统计数据");
        return 0;
    }
    struct SORT_NODE*node_prior,*node_after,*node_cur,*node_temp;/*选择排序法排序*/
    node_prior=head;
    node_temp=(struct SORT_NODE*)malloc(sizeof(struct SORT_NODE));/*排序时交换节点信息时的临时节点*/
    while(node_prior->next!=NULL)
    {
        node_cur=node_prior;
        node_after=node_prior->next;
        while(node_after!=NULL)
        {
            if(node_cur->counts<node_after->counts)
            {
                node_cur=node_after;
            }
            node_after=node_after->next;
        }
        if(node_cur!=node_prior)
        {
            *node_temp=*node_prior;/*交换节点信息，指针域不变换*/
            *node_prior=*node_cur;
            node_prior->next=node_temp->next;
            node_temp->next=node_cur->next;
            *node_cur=*node_temp;
        }
        node_prior=node_prior->next;
    }
    free(node_temp);
    p=head;
    while(p!=NULL)
    {
        gtk_list_store_append(store,&p->iter);/*添加信息到store中*/
        gtk_list_store_set(store,&p->iter,
                           COLUMN,p->str,
                           COMMENT,p->counts,
                           -1);
        p=p->next;
    }
    p=head;
    while(p!=NULL)/*释放统计链表内存*/
    {
        free(p);
        p=p->next;
    }
    Statis_table("工作量排名",/*调用Statis_info函数显示结果*/
                 "姓名",
                 "工作量",
                 store);

}
/**
*函数名：statis_time
*功能：统计各年度学时不足64学时的教师，调用Statis_table显示统计结果
*输入参数：
*返回值：无
*/
void statis_time(GtkWidget *button)
{
    GtkTreeIter iter;
    TEACHER_NODE *pTEACHER;
    WORK_NODE *pWORK;
    TEACHER_WORK_NODE*pTEACHER_WORK;
    GtkListStore *store;
    pTEACHER=gp_head;
    int hours;
    store = gtk_list_store_new(2,
                               G_TYPE_STRING,
                               G_TYPE_STRING
                              );
    while(pTEACHER!=NULL)
    {
        pWORK=pTEACHER->work_node;
        while(pWORK!=NULL)
        {
            pTEACHER_WORK=pWORK->teacher_work_node;
            if(pTEACHER_WORK!=NULL)
            {
                hours=0;
                while(pTEACHER_WORK!=NULL)
                {
                    hours=hours+pTEACHER_WORK->experimental_hours+pTEACHER_WORK->teaching_hours;
                    pTEACHER_WORK=pTEACHER_WORK->next;
                }
                if(hours<64)
                {
                    gtk_list_store_append(store,&iter);
                    gtk_list_store_set(store,&iter,
                                       COLUMN,"年份",
                                       COMMENT,pWORK->year,
                                       -1);
                    gtk_list_store_append(store,&iter);
                    gtk_list_store_set(store,&iter,
                                       COLUMN,pTEACHER->number,
                                       COMMENT,pTEACHER->name,
                                       -1);
                }
            }

            pWORK=pWORK->next;
        }

        pTEACHER=pTEACHER->next;

    }
    Statis_table("不足64学时的教师",
                 "编号",
                 "姓名",
                 store);
}
/****************************************/
/**
*函数名：help_info
*功能： 弹出软件信息
*输入参数：
*返回值：无
*/
void help_info(GtkWidget *button)
{
    dialog_info("TEACHER SYSTEM is a teacher information management system");
}

