#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct {
    char no[10];    //8位学号
	char name[20];  //姓名
	char classID[20];   //班级
	int score;      //成绩
} Student;
typedef struct Node {
    Student data;	
    struct Node *next; //指针域
} LNode;

//初始化一个学生信息链表，根据指定学生人数，逐个输入学生信息
void CreatStuList(LNode *&list) {
	list = NULL;
    int n;
    printf("请输入学生人数: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        LNode* newNode = (LNode*)malloc(sizeof(LNode));
        printf("请输入第%d个学生的信息(学号 姓名 班级 成绩): ", i+1);
        scanf("%s %s %s %d", newNode->data.no, newNode->data.name,newNode->data.classID, &newNode->data.score);
        newNode->next = list;
        list = newNode;
    }   	
}

//逐个显示学生表中所有学生的相关信息
void show(LNode *list) {
	LNode* p = list;
    int i = 1;
    printf("\n学生信息如下:\n");
    printf("序号\t学号\t姓名\t班级\t成绩\n");
    while (p != NULL) {
        printf("%d\t%s\t%s\t%s\t%d\n", i++, p->data.no, p->data.name, p->data.classID, p->data.score);
        p = p->next;
    }
}

/*根据姓名进行查找，若存在则输出此学生的信息，并返回逻辑序号，否则输出“无此人”并返回0 */
int findByName(LNode *list, char name[]) {
	LNode* p = list;
    int pos = 1;
    while (p != NULL) {
        if (strcmp(p->data.name, name) == 0) {
            printf("找到学生: %s\t%s\t%s\t%d\n", p->data.no, p->data.name, p->data.classID, p->data.score);
            return pos;
        }
        p = p->next;
        pos++;
    }
    printf("无此人\n");
    return 0;  
}

//输出逻辑序号pos对应的学生信息（学号，姓名，班级，成绩）
bool Position(LNode *list, int pos) {
	LNode* p= list;
	int i = 1;
    while (p != NULL && i < pos) {
        p = p->next;
        i++;
    }
    if (p == NULL || pos < 1) {
        printf("位置无效\n");
        return false;
    }
    printf("位置%d的学生信息: %s\t%s\t%s\t%d\n", pos, p->data.no, p->data.name, p->data.classID, p->data.score);
    return true;
}

//给定一个学生信息，插入到表中指定的位置
bool PInsert(LNode *&list, int pos,Student &stu) {
	if (pos < 1) return false;
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data = stu;
    
    if (pos == 1) {
        newNode->next = list;
        list = newNode;
        return true;
    }
    
    LNode* p = list;
    int i = 1;
    while (p != NULL && i < pos-1) {
        p = p->next;
        i++;
    }
    
    if (p == NULL) return false;
    newNode->next = p->next;
    p->next = newNode;
    return true;
}

// 删除指定位置的学生记录
bool Delete(LNode *&list, int pos,Student &stu) {
   if (list == NULL || pos < 1) return false;
    
    LNode* p = list;
    if (pos == 1) {
        list = list->next;
        stu = p->data;
        free(p);
        return true;
    }
    
    int i = 1;
    while (p->next != NULL && i < pos-1) {
        p = p->next;
        i++;
    }
    
    if (p->next == NULL) return false;
    
    LNode* q = p->next;
    p->next = q->next;
    stu = q->data;
    free(q);
    return true;
	
}
//统计表中学生人数
int Count(LNode *list) {
	int count = 0;
    LNode* p = list;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
	   
}
//释放链表
void DestroyList(LNode *&list) {
	LNode* p = list;
    while (p != NULL) {
        LNode* q = p->next;
        free(p);
        p = q;
    }
    list = NULL;
    
}
void menu()  
{
    printf("\n1: 显示学生信息\n");
	printf("2: 根据姓名进行查找\n");
	printf("3: 根据指定的位置输出相应的学生信息\n");
	printf("4: 插入一个学生\n");
	printf("5: 删除一个学生\n");
	printf("6: 统计表中学生个数\n");
	printf("7: 退出\n");
	printf("\n请选择:");	
}
int main()
{
	LNode *list;
	char name[20];
	int pos,sel,flag=1;
    Student stu;
    printf("\n初始化一个学生信息链表\n");
    CreatStuList(list);
	
	while(flag==1){		
		menu();		
		scanf("%d",&sel);
		
		switch(sel){				
			case 1:
				show(list);break;
			case 2:
				printf("\n请输入要查学生的姓名：");
				scanf("%s",name);
				findByName(list,name);break;
			case 3:
				printf("\n请输入要查学生的逻辑序号：");
				scanf("%d",&pos);
				if(!Position(list,pos)) 
					printf("该逻辑序号不存在\n");break;
			case 4:
				printf("\n请输入一个新学生的插入位置（逻辑序号）：");
				scanf("%d",&pos);
				printf("\n请输入新学生的信息（学号，姓名，班级，成绩）：");
				scanf("%s",stu.no);
				scanf("%s",stu.name);
				scanf("%s",stu.classID);
				scanf("%d",&stu.score);
				if(!PInsert(list,pos,stu)) 
					printf("插入失败！");
				else 
					printf("插入成功！");
				show(list); break;
			case 5:
				printf("\n请输入要删除学生的位置（逻辑序号）：");
				scanf("%d",&pos);
				if(!Delete(list,pos,stu)) 
					printf("删除失败！");
				else{
					printf("删除学生：%s %s %s %d\n",stu.no,stu.name,stu.classID,stu.score);
					printf("删除成功！删除后表信息如下：");
				} 					
				show(list); break;
			case 6:
				printf("\n学生表中学生的人数为：%d\n",Count(list));break;			
			case 7:
				DestroyList(list);flag=0;
		}	 	
	}	
	return 1;
}
