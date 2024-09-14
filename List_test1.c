#include "stdio.h"

struct person{
	char *name;
	int age;
	struct person *next;
};//定义一个结构体成员

struct list{
	char *name;
	struct person head;
};//定义一个链表

void AddItemToList(struct list *plist, struct person *new_person)
{
	struct person *last = &plist->head;
	while (last->next){
		last = last->next;
	}
	last->next = new_person;
	new_person->next = NULL;
}//增加一个结构体成员，只能加在链表的最后面

void DelItemFromList(struct list *plist, struct person *person)
{
	struct person *per = &plist->head;
	while (per != NULL && per->next != person){
		per = per->next;
	}
	if(per == NULL)
		return;
	if(per->next == person)
		per->next = person->next;
}//删除链表中的某个结构体成员，需要传入结构体成员地址

void AddItemAfter(struct person *pre,struct person *new_person)
{
	new_person->next = pre->next;
	pre->next = new_person;
}//加入结构体成员，加在中间的某个位置，前提需要已知前一个节点


void SortList(struct list *plist)
{
	struct person *pre1 = &plist->head;
	struct person *pre2;
	struct person *cur = plist->head.next;
	struct person *next;
	struct person *temp;
	while (cur){
		pre2 = cur;
		next = cur->next;
		while(next){
			if(cur->age > next->age){
				//删除节点cur
				DelItemFromList(plist,cur);
				//删除节点next
				DelItemFromList(plist,next);
				//在pre1后面插入next
				AddItemAfter(pre1,next);
				//在pre2后面插入cur
				if(pre2 == cur) //如果出现连续两个节点交换的情况
					AddItemAfter(next,cur);
				else
					AddItemAfter(pre2,cur);
				//指针互换
				temp = cur;
				cur = next;
				next = temp;
			}
			pre2 = next;
			next = next->next;
		}
		pre1 = cur;
		cur = cur->next;
	}
}//对链表进行排序（快速排序法）

void PrintList(struct list *plist)
{
	int i = 0;
	struct person *p = plist->head.next;
	while (p != NULL)
	{
		printf("person %d : %s is %d \r\n",i++,p->name,p->age);
		p = p->next;
	}
}//对链表进行打印


void InitList(struct list * plist,char *name)
{
	plist->name = name;
	plist->head.next = NULL;
}//初始化链表


int main()
{
    printf("List_test!!!!!!\r\n");

	struct list list_A;//定义链表
	struct person p[]={
		{"p0",23,NULL},
		{"p1",12,NULL},
		{"p2",43,NULL},
		{"p3",54,NULL},
		{"p4",3,NULL},
		{"p5",76,NULL},
		{"p6",32,NULL},
		{"p7",87,NULL},
		{"p8",45,NULL},
		{"p9",76,NULL},
		{NULL,0,NULL}
	};//定义结构体成员信息

	InitList(&list_A,"class_A");//初始化链表
	int i = 0;
	while(p[i].name != NULL){
		AddItemToList(&list_A,&p[i]);
		i++;
	}//将结构体成员加载到链表中
	PrintList(&list_A);
	printf("\r\n");

	DelItemFromList(&list_A,&p[3]);//删除链表成员4
	PrintList(&list_A);
	printf("\r\n");

	SortList(&list_A);//链表排序
	PrintList(&list_A);
	printf("\r\n");
	
    return 0;
}