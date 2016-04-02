#ifndef _MY_H /*条件编译防止头文件被重复加载*/
#define _MY_H

/*-------头文件---------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define NAME    "admin"
#define PWD     "admin"

/********************
        结构声明
*********************/
/**教学基本信息*/
typedef struct TEACHER_WORK_NODE
{
    char   number[12];     /*编号ID*/
    char  year[12];    /*年份*/
    char  Class[15];               /*班级*/
    int    teaching_hours;        /*授课学时*/
    int    experimental_hours;        /*实验学时*/
    int    student_member;    /*学生人数*/
    char   program[12];    /*课程名*/
    struct TEACHER_WORK_NODE *next;/*指向下一个结点*/
    GtkTreeIter iter;       /*treeview中对应treeiter*/
} TEACHER_WORK_NODE;

/**工作量基本信息*/
typedef struct WORK_NODE
{
    char   number[12];     /*编号ID*/
    char year[12];               /*年份*/
    int working;       /*科研工作量*/
    int member;      /*指导毕设*/
    int  element ;                /*指导硕/博士*/
    int goal      ;                 /*总分*/
    struct WORK_NODE *next;  /*指向下一节点*/
    struct TEACHER_WORK_NODE * teacher_work_node;  /*指向教学工作基本信息结点的指针*/
    GtkTreeIter iter;           /*treeview中对应treeiter*/
} WORK_NODE;

/**教师基本信息*/
typedef struct TEACHER_NODE
{
    char  number[12];           /*编号ID*/
    char  name[20];            /*姓名*/
    char  company[30];                  /*单位*/
    char title[30];                        /*职称*/
    struct TEACHER_NODE *next;    /*指向下一结点*/
    struct   WORK_NODE* work_node; /*指向工作量基本信息结点的指针*/
    GtkTreeIter iter;           /*treeview中对应treeiter*/
} TEACHER_NODE;

struct transfer       /*传递数据参数*/
{
    GtkWidget *window;
    GtkWidget *entry[7];
    int type;
};
struct SORT_NODE/*排序结构*/
{
    int counts;
    char*str;
    struct SORT_NODE *next;
    GtkTreeIter iter;
};
struct LOGIN/*记录登录时输入的数据*/
{
    GtkWidget*entry[2];
    GtkWidget*label;
    GtkWidget*window;
};
/********************
       全局变量
*********************/
GtkWidget *window;          /*主窗口*/
GtkWidget *showlist;       /*右边显示区域*/
GtkListStore *liststore;
GtkListStore *lstore[3];      /*右边显示区域项目组*/
GtkTreeStore *treestore;          /*treeview储存*/
GtkWidget *treeview;        /*树状图列表*/
GtkTreeIter rootiter;      /*根节点*/
GtkTreeIter selectediter;  /*选中的位置*/

/*显示区域liststore组*/
GtkTreeIter TEACHER_iter[4];
GtkTreeIter WORK_iter[6];
GtkTreeIter TEACHER_WORK_iter[7];

TEACHER_NODE *gp_head;              /*主链表头指针*/
char **Str_Pointer[3];

/*mylib.c中已初始化的全局变量*/
extern char *Node_Str[];
extern int NODE_NUMBER[];
extern int count;
extern char *Teacher_Str[];
extern char *Work_Str[];
extern char *Teacher_Work_Str[];


enum //iter里的列号
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
/****函数声明*************/
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
