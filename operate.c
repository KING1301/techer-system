#include "my.h"
/**
*��������TEACHER_search
*���ܣ���id������ʦ
*���������number��ʦ���
*����ֵ����ʦ�ڵ�ָ��
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
        dialog_info("�޶�Ӧid��ʦ��");
        return(NULL);
    }
}
/******************************************/
/**
*��������WORK_search
*���ܣ�������������������ڵ�
*���������year ��ݣ�WORK ���ڽ�ʦ�������ڵ�ָ��
*����ֵ���������ڵ�ڵ�ָ��
*/
WORK_NODE *WORK_search(char *year,WORK_NODE *pWORK)
{
    if(pWORK==NULL)
    {
        dialog_info("δ���빤������Ϣ");
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
        dialog_info("�޶�Ӧ��������");
        return(NULL);
    }
}
/********************************************/
/**
*��������TEACHER_WORK_search
*���ܣ���Class������ѧ��Ϣ�ڵ�
*�������: Class,�༶����WORK �����������ڵ�ָ��
*����ֵ����ѧ��Ϣ�ڵ�ڵ�ָ��
*/
TEACHER_WORK_NODE *TEACHER_WORK_search(char *Class,TEACHER_WORK_NODE *pTEACHER_WORK)
{
    if(pTEACHER_WORK==NULL)
    {
        dialog_info("δ�����ѧ��Ϣ");
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
        dialog_info("�޶�Ӧ��ѧ��Ϣ��");
        return(NULL);
    }
}

/***********¼��ڵ�*******************/
/**************************************************/
/**
*��������input_work
*���ܣ���ӹ������ڵ㺯������input�����3����
*���������pNew ָ���½ڵ��ָ��
*����ֵ����Ӧ��ʦ������Ϣ�ڵ�ָ��
*/
TEACHER_NODE *input_work(WORK_NODE *pNew)
{
    TEACHER_NODE *pTEACHER;
    WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(pTEACHER);/*δ�ҵ���Ӧ��ʦ���������*/
    if(pTEACHER->work_node==NULL)/*����������ͷ�ڵ㣬��ֱ�Ӳ���*/
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
*��������input_teacher_work
*���ܣ���ӽ�ѧ������Ϣ�ڵ㺯������input�����4����
*���������pNew ָ���½ڵ��ָ��
*����ֵ����Ӧ�������ڵ�ָ��
*/
WORK_NODE *input_teacher_work(TEACHER_WORK_NODE *pNew)
{
    TEACHER_NODE*pTEACHER;
    WORK_NODE *pWORK;
    TEACHER_WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(NULL);/*δ�ҵ���ʦ���������*/
    pWORK=WORK_search(pNew->year,pTEACHER->work_node);
    if(pWORK==NULL)
        return(NULL); /*δ�ҵ����������������*/
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
*��������input_data
*���ܣ�¼��ڵ�
*���������struct transfer*nodec
*����ֵ����
*/
void input_data(GtkWidget*button,struct transfer*nodec)
{
    GtkTreeModel *model;
    int error=0;
    char *str;
    switch(nodec->type)
    {
    case 3:/*�����ʦ������Ϣ*/
    {
        TEACHER_NODE *pNew;
        TEACHER_NODE*pSEARCH;
        pNew = (TEACHER_NODE *)calloc(1, sizeof(TEACHER_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
    case 4:/*���빤�����ڵ�*/
    {
        TEACHER_NODE*pTeacher;
        WORK_NODE*pNew;
        pNew = (WORK_NODE*)calloc(1, sizeof(WORK_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
        if((pTeacher=input_work(pNew))!=NULL) /*ʹ��input_Work����*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pTeacher->iter);/*�������*/
            gtk_tree_store_set(treestore,&pNew->iter,COLUMN,pNew->year,-1); /*������ݵ��ı���ʾ*/
        }
        else
        {
            error=1;
            free(pNew);
        }

        break;
    }
    case 5:/*�����ѧ������Ϣ���*/
    {
        WORK_NODE*pWork;
        TEACHER_WORK_NODE *pNew;
        pNew = (TEACHER_WORK_NODE *)calloc(1,sizeof(TEACHER_WORK_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
        if((pWork=input_teacher_work(pNew))!=NULL) /*ʹ��input_Teacher_Work����*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pWork->iter);/*�������*/
            gtk_tree_store_set(treestore,&pNew->iter,COLUMN,pNew->Class,-1);       /*������ݵ��ı���ʾ*/
        }
        else
        {
            error=1;
            free(pNew);
        }

        break;
    }
    default:
        dialog_info("���ݷǷ�!");
    }
    if(error==0)
    {
        model=GTK_TREE_MODEL(treestore);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);/*����model��view*/
    }
    else
    {
        dialog_info("ʧ��!");

    }
    gtk_widget_destroy(nodec->window);
    /*����ѡ����ʾ��*/
    dialogdata(nodec->type);
    free(nodec);

}
/***************************************/
/****************����ڵ�***************/
/**
*��������insert_WORK
*���ܣ����빤�����ڵ㺯������insert_data�����3����
*���������pNew ָ���½ڵ��ָ��
*����ֵ����Ӧ��ʦ�ڵ�ָ��
*/
TEACHER_NODE *insert_WORK(WORK_NODE *pNew)
{
    TEACHER_NODE *pTEACHER;
    WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(NULL);/*δ�ҵ���Ӧ��ʦ���������*/
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
*��������insert_TEACHER_WORK
*���ܣ������ѧ��Ϣ�ڵ㺯������insert_data�����4����
*���������pNew ָ���½ڵ��ָ��
*����ֵ����Ӧ��ѧ��Ϣ�ڵ�ָ��
*/
WORK_NODE *insert_TEACHER_WORK(TEACHER_WORK_NODE *pNew)
{
    TEACHER_NODE *pTEACHER;
    WORK_NODE *pWORK;
    TEACHER_WORK_NODE*pSEARCH;
    pTEACHER=TEACHER_search(pNew->number);
    if(pTEACHER==NULL)
        return(NULL);/*δ�ҵ���Ӧ��ʦ���������*/

    pWORK=WORK_search(pNew->year,pTEACHER->work_node);
    if(pWORK==NULL)
        return(NULL);/*δ�ҵ���Ӧ���������������*/
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
*��������insert_data
*���ܣ�����3�ֽڵ�ͳһ��������insert_infoȷ����ť����
*���������
*����ֵ����
*/
void insert_data(GtkWidget *button,struct transfer *nodec)
{
    GtkTreeModel *model;
    int error=0;
    char *str;
    switch(nodec->type)
    {
    case 3:/*�����ʦ�ڵ�*/
    {
        TEACHER_NODE *pNew;
        TEACHER_NODE*pSEARCH;
        pNew = (TEACHER_NODE *)calloc(1, sizeof(TEACHER_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
    case 4:/*���빤�����ڵ�*/
    {
        TEACHER_NODE *pTEACHER;
        WORK_NODE *pNew;
        pNew = (WORK_NODE *)calloc(1, sizeof(WORK_NODE));
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
        if((pTEACHER=insert_WORK(pNew))!=NULL) /*ʹ��insert_WORK����*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pTEACHER->iter);/*�������*/
            gtk_tree_store_set(treestore,&pNew->iter,        /*������ݵ��ı���ʾ*/
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
    case 5:/*�����ѧ��Ϣ�ڵ�*/
    {
        WORK_NODE *pWORK;
        TEACHER_WORK_NODE *pNew;
        pNew = (TEACHER_WORK_NODE *)calloc(1,sizeof(TEACHER_WORK_NODE));/*��ȡ������������Ϣ*/
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


        if((pWORK=insert_TEACHER_WORK(pNew))!=NULL) /*ʹ��insert_TEACHER_WORK����*/
        {
            gtk_tree_store_append(treestore,&pNew->iter,&pWORK->iter);/*�������*/
            gtk_tree_store_set(treestore,&pNew->iter,        /*������ݵ��ı���ʾ*/
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
        dialog_info("����ʧ��!");
    }
    if(error==0)
    {
        model=GTK_TREE_MODEL(treestore);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);/*����model��view*/
        dialog_info("����ɹ���");
    }
    gtk_widget_destroy(nodec->window);
    free(nodec);
}
/*******************************************/
/**************�༭�ڵ�*******************/
/**
*��������edit_data
*���ܣ��༭�ڵ�
*���������
*����ֵ����
*/
void  edit_data(GtkWidget *button,struct transfer *nodec)
{
    GtkTreeIter iter;
    char *str;
    int error=0;
    switch(nodec->type)
    {
    case 3:/*�༭��ʦ�ڵ�*/
    {
        TEACHER_NODE *pNew;
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
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
        dialog_info("�޸ĳɹ�");
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(treestore));
        expand_iter(iter);
    }
    gtk_widget_destroy(nodec->window);
    free(nodec);
}
/***************************************/
/****************ɾ���ڵ�**********************/
/**
*��������delete_teacher
*���ܣ�ɾ����ʦ��Ϣ�ڵ�
*���������struct transfer*nodec
*����ֵ��int 1Ϊ�д�0Ϊ����
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
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ������������Ϣ*/
    if(!(flag=strcmp(str,pSEARCH->number)))/*�ҵ���Ӧ�Ľ�ʦ�ڵ㲢ɾ����ʦ�ڵ��µĹ������ڵ�ͽ�ѧ��Ϣ�ڵ�*/
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
        gtk_tree_store_remove(treestore,&pSEARCH->iter);  /*ɾ����״�б��Ӧiter*/
        free(pSEARCH);/*�ͷŽ�ʦ�ڵ��ڴ�*/
        dialog_info("ɾ���ɹ�");
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
        pPRE->next=pSEARCH->next;  /*��ǰһ�ڵ�ֱ��������һ�ڵ�*/
        gtk_tree_store_remove(treestore,&pSEARCH->iter);/*ɾ����״�б��Ӧiter*/
        free(pSEARCH);
    }
    else
    {
        dialog_info("�޶�Ӧ��ʦ��");
        return(1);
    }
    if(error==0)
        dialog_info("ɾ���ɹ���");
    return 0;
}
/*******************************************/
/**
*��������delete_work
*���ܣ�ɾ����������Ϣ�ڵ�
*���������struct transfer*nodec
*����ֵ��int 1Ϊ�д�0Ϊ����
*/
int delete_work(struct transfer*nodec)
{
    int flag=1,error=0;
    char *str;
    TEACHER_NODE *pTEACHER;
    WORK_NODE *pSEARCH,*pPRE;
    TEACHER_WORK_NODE*p1;
    str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));
    pTEACHER=TEACHER_search(str); /*����TEACHER_search����������Ӧ��ʦ�ڵ�*/
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
        dialog_info("ɾ���ɹ�");
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
        dialog_info("�޶�Ӧ��������");
        gtk_widget_destroy(nodec->window);
        return(1);
    }
    if(error==0)
        dialog_info("ɾ���ɹ���");
    return 0;
}
/**********************************************************/
/**
*��������delete_teacher_work
*���ܣ�ɾ����ѧ��Ϣ�ڵ�
8���������struct transfer*nodec
*����ֵ��int 1Ϊ�д�0Ϊ����
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
        dialog_info("ɾ���ɹ�");
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
        dialog_info("�޶�Ӧ��ѧ������Ա��");
        return(1);
    }
    if(error==0)
        dialog_info("ɾ���ɹ���");
    return 0;
}
/******************************************/
/**
*��������delete_data
*���ܣ�struct transfer*nodec
*�������:
*����ֵ����
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
/******************��ѯ�ڵ�*******************/
/**
*��������expand_iter
*���ܣ�չ������ת��ָ��iter
*���������iter treeview�е�һ��Ŀ��iter
*����ֵ����
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
*��������query_data
*���ܣ���ѯ������Ϣ
*���������struct transfer*nodec
*����ֵ����
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
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ���������*/
        pTEACHER=TEACHER_search(str);
        if(pTEACHER!=NULL)
        {
            expand_iter(pTEACHER->iter);
        }
        break;
    }
    case 1:
    {
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ���������*/
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
        str=(char*)gtk_entry_get_text(GTK_ENTRY(nodec->entry[0]));/*��ȡ���������*/
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
/**********************ͳ��****************************/
/**
*��������Statis_table
*���ܣ�����һ��ͳ�ƿ�
*���������title ͳ�ƿ����,col1 ��һ�б���,col2 �ڶ��б���,model �����model
*����ֵ����
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

    list = gtk_tree_view_new();      /*����view�ȴ��봫���model����*/

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
    b_ok=gtk_button_new_with_label("ȷ��");
    g_signal_connect(G_OBJECT(b_ok),"clicked",G_CALLBACK(close),statis_window);
    gtk_box_pack_start(GTK_BOX(hbox),b_ok,TRUE,FALSE,0);
    gtk_widget_show_all(statis_window);
}
/***************************************************/
/**
*��������statis_fund
*���ܣ�ͳ����������������򣬵���Statis_table��ʾͳ�ƽ��
*���������
*����ֵ����
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
        dialog_info("��ͳ������");
        return 0;
    }
    struct SORT_NODE*node_prior,*node_after,*node_cur,*node_temp;/*ѡ������*/
    node_prior=head;
    node_temp=(struct SORT_NODE*)malloc(sizeof(struct SORT_NODE));/*�����ڵ���Ϣ����ʱ�ڵ�*/
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
        if(node_cur!=node_prior)/*�����ڵ���Ϣ��ָ���򲻱�*/
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
        gtk_list_store_append(store,&p->iter);/*�����Ϣ��store��*/
        gtk_list_store_set(store,&p->iter,
                           COLUMN,p->str,
                           COMMENT,p->counts,
                           -1);
        p=p->next;
    }
    while(p!=NULL)/*�ͷ�ͳ�������ڴ�*/
    {
        free(p);
        p=p->next;
    }

    Statis_table("��������",
                 "����",
                 "������",
                 store);
}
/*****************************************************/
/**
*��������statis_working
*���ܣ�ͳ�������ѧѧʱ�����򣬵���Statis_table��ʾͳ�ƽ��
*���������
*����ֵ����
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
                    p->counts+=p3->experimental_hours+p3->teaching_hours;/*�����ʦѧʱ*/
                }
                p->next=head;
                head=p;
            }
        }
    }
    if(head==NULL)
    {
        dialog_info("��ͳ������");
        return 0;
    }
    struct SORT_NODE*node_prior,*node_after,*node_cur,*node_temp;/*ѡ����������*/
    node_prior=head;
    node_temp=(struct SORT_NODE*)malloc(sizeof(struct SORT_NODE));/*����ʱ�����ڵ���Ϣʱ����ʱ�ڵ�*/
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
            *node_temp=*node_prior;/*�����ڵ���Ϣ��ָ���򲻱任*/
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
        gtk_list_store_append(store,&p->iter);/*�����Ϣ��store��*/
        gtk_list_store_set(store,&p->iter,
                           COLUMN,p->str,
                           COMMENT,p->counts,
                           -1);
        p=p->next;
    }
    p=head;
    while(p!=NULL)/*�ͷ�ͳ�������ڴ�*/
    {
        free(p);
        p=p->next;
    }
    Statis_table("����������",/*����Statis_info������ʾ���*/
                 "����",
                 "������",
                 store);

}
/**
*��������statis_time
*���ܣ�ͳ�Ƹ����ѧʱ����64ѧʱ�Ľ�ʦ������Statis_table��ʾͳ�ƽ��
*���������
*����ֵ����
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
                                       COLUMN,"���",
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
    Statis_table("����64ѧʱ�Ľ�ʦ",
                 "���",
                 "����",
                 store);
}
/****************************************/
/**
*��������help_info
*���ܣ� ���������Ϣ
*���������
*����ֵ����
*/
void help_info(GtkWidget *button)
{
    dialog_info("TEACHER SYSTEM is a teacher information management system");
}

