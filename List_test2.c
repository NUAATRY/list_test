#include "stdio.h"

#define container_of(ptr,type,member) \
		(type *)((char *)ptr - (unsigned int)&((type *)0)->member)


struct node_t{
	struct node_t *next;
};

struct person{
	char *name;
	int age;
	struct node_t node;
};//定义一个结构体成员

struct list{
	char *name;
	struct node_t head;
};//定义一个链表

void InitList(struct list * plist,char *name)
{
	plist->name = name;
	plist->head.next = NULL;
}//初始化链表

void AddItemToList(struct list *plist, struct node_t *new_node)
{
	struct node_t *last = &plist->head;
	while (last->next){
		last = last->next;
	}
	last->next = new_node;
	new_node->next = NULL;
}//增加一个结构体成员，只能加在链表的最后面

void AddItemAfter(struct node_t *pre,struct node_t *new_node)
{
	new_node->next = pre->next;
	pre->next = new_node;
}//加入结构体成员，加在中间的某个位置，前提需要已知前一个节点



void DelItemFromList(struct list *plist, struct node_t *node)
{
	struct node_t *per = &plist->head;
	while (per != NULL && per->next != node){
		per = per->next;
	}
	if(per == NULL)
		return;
	if(per->next == node)
		per->next = node->next;
}//删除链表中的某个结构体成员，需要传入结构体成员地址

int CmpPersonAge(struct node_t *pre,struct node_t *next)
{
	struct person *p;
	struct person *n;

	p = container_of(pre,struct person,node);
	n = container_of(next,struct person,node);
	if(p->age < n->age)
		return -1;
	else
		return 0;
}


void SortList(struct list *plist)
{
	struct node_t *pre1 = &plist->head;
	struct node_t *pre2;
	struct node_t *cur = plist->head.next;
	struct node_t *next;
	struct node_t *temp;
	while (cur){
		pre2 = cur;
		next = cur->next;
		while(next){
			if(CmpPersonAge(cur,next) == 0){
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
	struct node_t *node = plist->head.next;
	struct person *p;
	while (node != NULL)
	{
		p = container_of(node,struct person,node);
		printf("person %d : %s is %d %x\r\n",i++,p->name,p->age,p->node.next);
		node = node->next;
	}
}//对链表进行打印


int main()
{
    printf("List_test!!!!!!\r\n");

	struct list list_A;//定义链表
	struct person p[]={
		{"p0",23,{NULL}},
		{"p1",12,{NULL}},
		{"p2",43,{NULL}},
		{"p3",54,{NULL}},
		{"p4",3,{NULL}},
		{"p5",76,{NULL}},
		{"p6",32,{NULL}},
		{"p7",87,{NULL}},
		{"p8",45,{NULL}},
		{"p9",76,{NULL}},
		{NULL,0,{NULL}}
	};//定义结构体成员信息

	InitList(&list_A,"class_A");//初始化链表
	int i = 0;
	while(p[i].name != NULL){
		AddItemToList(&list_A,&p[i].node);
		i++;
	}//将结构体成员加载到链表中
	PrintList(&list_A);
	printf("\r\n");

	DelItemFromList(&list_A,&p[3].node);//删除链表成员4
	PrintList(&list_A);
	printf("\r\n");

	SortList(&list_A);//链表排序
	PrintList(&list_A);
	printf("\r\n");
	
    return 0;
}