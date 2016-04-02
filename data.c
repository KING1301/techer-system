#include "my.h"
/****************��ȡ��洢*********************/
/**
*��������LoadList
*���ܣ���ȡ�����ļ������ݵ�������
*���������phead ��ʦ�ڵ�ͷָ��ĵ�ַ
*����ֵ��re 0����
               4�Ѽ��ؽ�ʦ��Ϣ
                12�Ѽ��ؽ�ʦ��Ϣ�͹�������Ϣ
                28 ��ȫ��
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
    /*�������ļ��ж�ȡ��ʦ������Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
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

    /*�������ļ��ж�ȡ������������Ϣ���ݣ�����������Ӧ���Ĺ�����������Ϣ֧����*/
    while(!feof(pFile))
    {
        /*������㣬��Ŵ������ļ��ж����Ĺ�����������Ϣ*/
        pWork=(WORK_NODE*)calloc(1,sizeof(WORK_NODE));
        fread(pWork,sizeof(WORK_NODE),1,pFile);
        if(!feof(pFile))
        {
            pWork->teacher_work_node=NULL;
            /*�������ϲ��Ҹñ��ID��Ӧ���������*/
            pTeacher=hd;
            while(pTeacher!=NULL&&strcmp(pTeacher->number,pWork->number))
            {
                pTeacher=pTeacher->next;
            }

            /*����ҵ����򽫽���Ժ���ȳ���ʽ�����ʦ��Ϣ*/
            if(pTeacher!=NULL)
            {
                pWork->next=pTeacher->work_node;
                pTeacher->work_node=pWork;
            }
            else  /*���δ�ҵ������ͷ������������ڴ�ռ�*/
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

    /*�������ļ������ѧ����������Ϣ���ݣ����빤����������Ϣ֧����Ӧ���Ľ�ѧ������Ϣ֧����*/
    while (!feof(pFile))
    {
        /*������㣬��Ŵ������ļ��ж����Ľ�ѧ����������Ϣ*/
        pTeacher_Work = (TEACHER_WORK_NODE *)calloc(1,sizeof(TEACHER_WORK_NODE));
        fread(pTeacher_Work, sizeof(TEACHER_WORK_NODE), 1, pFile);
        if(!feof(pFile))
        {
            /*���ҹ�����������Ϣ֧���϶�Ӧ��ѧ������Ϣ���*/
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
                    pTeacher_Work->next=pWork->teacher_work_node;/*�ҵ��������ڵ����Ժ���ȳ���ʽ������ѧ������Ϣ����*/
                    pWork->teacher_work_node=pTeacher_Work;
                }
                else
                {
                    free(pTeacher_Work);//���δ�ҵ���������Ϣ�����ͷ�
                }
            }
            else /*���δ�ҵ���ʦ��Ϣ�����ͷ������������ڴ�ռ�*/
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
*��������addtree
*���ܣ��������нڵ���ӵ���״�б���
*���������
*����ֵ��
*/
void addtree()
{
    GtkTreeModel *model;
    TEACHER_NODE *p1;
    WORK_NODE *p2;
    TEACHER_WORK_NODE *p3;
    for(p1=gp_head; p1!=NULL; p1=p1->next)
    {
        gtk_tree_store_append(treestore,&p1->iter,&rootiter);   /*�������*/
        gtk_tree_store_set(treestore,&p1->iter,                 /*������ݵ��ı���ʾ*/
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
*��������LoadData
*���ܣ���ȡ�����ļ�
*���������
*����ֵ��
*/
int  LoadData(GtkWidget*button)
{

    int re;
    if(count==1)
    {
        dialog_info("�����Ѽ���");
        return 0;
    }
    re=LoadList(&gp_head);
    if(re==0)
        dialog_info("����������");
    else
    {
        if(re==4)
        {
            addtree();
            dialog_info("��ʦ���ݼ������");
        }
        else
        {
            if(re==12)
            {
                addtree();
                dialog_info("��ʦ���ݹ��������ݼ������");
            }
            else
            {
                addtree();
                dialog_info("ȫ�����ݼ������");
            }
        }
        count++;/*������ݼ��سɹ����¼*/
    }
    return 0;
}
/***********************************************/
/**
*��������Savelist
*���ܣ������������ݴ洢�������ļ���
*���������phead��ʦ�ڵ�ͷָ��
*����ֵ��flag ��¼�����������ļ��Ƿ�ɹ�����
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
*��������SaveData
*���ܣ��洢�����ļ�
*���������
*����ֵ��
*/
int SaveData(GtkWidget *button)
{
    int flag=0;
    flag=SaveList(gp_head);
    if(flag==28)
    {
        dialog_info("���ݱ���ɹ�");
    }
    else
        dialog_info("���ݱ���ʧ��");
    return (flag);
}

/******************************************/
/**
*��������quit_save
*���ܣ���ʾ����
*���������
*����ֵ��
*/
void quit_save(GtkWidget *button)
{
    GtkWidget *dialog;
    int flag;
    dialog = gtk_message_dialog_new((gpointer)window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_OK_CANCEL,
                                    "�˳�ǰ�Ƿ񱣴浱ǰ���ݣ�");
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
