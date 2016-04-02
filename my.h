#ifndef _MY_H /*���������ֹͷ�ļ����ظ�����*/
#define _MY_H

/*-------ͷ�ļ�---------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define NAME    "admin"
#define PWD     "admin"

/********************
        �ṹ����
*********************/
/**��ѧ������Ϣ*/
typedef struct TEACHER_WORK_NODE
{
    char   number[12];     /*���ID*/
    char  year[12];    /*���*/
    char  Class[15];               /*�༶*/
    int    teaching_hours;        /*�ڿ�ѧʱ*/
    int    experimental_hours;        /*ʵ��ѧʱ*/
    int    student_member;    /*ѧ������*/
    char   program[12];    /*�γ���*/
    struct TEACHER_WORK_NODE *next;/*ָ����һ�����*/
    GtkTreeIter iter;       /*treeview�ж�Ӧtreeiter*/
} TEACHER_WORK_NODE;

/**������������Ϣ*/
typedef struct WORK_NODE
{
    char   number[12];     /*���ID*/
    char year[12];               /*���*/
    int working;       /*���й�����*/
    int member;      /*ָ������*/
    int  element ;                /*ָ��˶/��ʿ*/
    int goal      ;                 /*�ܷ�*/
    struct WORK_NODE *next;  /*ָ����һ�ڵ�*/
    struct TEACHER_WORK_NODE * teacher_work_node;  /*ָ���ѧ����������Ϣ����ָ��*/
    GtkTreeIter iter;           /*treeview�ж�Ӧtreeiter*/
} WORK_NODE;

/**��ʦ������Ϣ*/
typedef struct TEACHER_NODE
{
    char  number[12];           /*���ID*/
    char  name[20];            /*����*/
    char  company[30];                  /*��λ*/
    char title[30];                        /*ְ��*/
    struct TEACHER_NODE *next;    /*ָ����һ���*/
    struct   WORK_NODE* work_node; /*ָ������������Ϣ����ָ��*/
    GtkTreeIter iter;           /*treeview�ж�Ӧtreeiter*/
} TEACHER_NODE;

struct transfer       /*�������ݲ���*/
{
    GtkWidget *window;
    GtkWidget *entry[7];
    int type;
};
struct SORT_NODE/*����ṹ*/
{
    int counts;
    char*str;
    struct SORT_NODE *next;
    GtkTreeIter iter;
};
struct LOGIN/*��¼��¼ʱ���������*/
{
    GtkWidget*entry[2];
    GtkWidget*label;
    GtkWidget*window;
};
/********************
       ȫ�ֱ���
*********************/
GtkWidget *window;          /*������*/
GtkWidget *showlist;       /*�ұ���ʾ����*/
GtkListStore *liststore;
GtkListStore *lstore[3];      /*�ұ���ʾ������Ŀ��*/
GtkTreeStore *treestore;          /*treeview����*/
GtkWidget *treeview;        /*��״ͼ�б�*/
GtkTreeIter rootiter;      /*���ڵ�*/
GtkTreeIter selectediter;  /*ѡ�е�λ��*/

/*��ʾ����liststore��*/
GtkTreeIter TEACHER_iter[4];
GtkTreeIter WORK_iter[6];
GtkTreeIter TEACHER_WORK_iter[7];

TEACHER_NODE *gp_head;              /*������ͷָ��*/
char **Str_Pointer[3];

/*mylib.c���ѳ�ʼ����ȫ�ֱ���*/
extern char *Node_Str[];
extern int NODE_NUMBER[];
extern int count;
extern char *Teacher_Str[];
extern char *Work_Str[];
extern char *Teacher_Work_Str[];


enum //iter����к�
{
    COLUMN = 0,
    COMMENT
} ;
enum
{
    TYPE_ROOT =1,
    TYPE_TEACHER,
    TYPE_WORK,
    TYPE_TEACHER_WORK
} ;
/****��������*************/
void init_login_window();
void entry_data(GtkWidget*button,int type);
void insert_info(GtkWidget *button,int type);
void edit_info(GtkWidget *button,int type);
void delete_info(GtkWidget *button,int type);
void query_info(GtkWidget *button,int type);
int LoadData(GtkWidget *button);
int SaveData(GtkWidget *button);
void quit_save(GtkWidget *button);
int Show_data(GtkTreeIter iter);
void statis_fund(GtkWidget *button);
void statis_working(GtkWidget *button);
void statis_time(GtkWidget *button);
void help_info(GtkWidget *button);
TEACHER_NODE *TEACHER_search(char *number);
WORK_NODE *WORK_search(char *year,WORK_NODE *pWORK);
TEACHER_WORK_NODE *TEACHER_WORK_search(char *Class,TEACHER_WORK_NODE *TEACHER_WORK);
void input_data(GtkWidget*button,struct transfer*nodec);
void insert_data(GtkWidget *button,struct transfer *nodec);
void edit_data(GtkWidget *button,struct transfer*nodec);
void delete_data(GtkWidget*button,struct transfer*nodec);
void query_data(GtkWidget*button,struct transfer*nodec);
void dialog_info(char *show);
void dialogdata(int type);
void close(GtkWidget*button,GtkWidget*window);

#endif
