
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "stack.h"
#define VERTEX_NUMBER 100
typedef struct func {
	int height;
}func;
typedef struct Edge_data {
	Edge_data* Edge_link;
	func func;
	int Name;
}Edge_data;
typedef struct vertex_data {
	int Name;
	vertex_data* vertex_link;
	vertex_data *link;
	bool flag;
	Edge_data*   Edge_link;
}vertex_data;
typedef struct Graph {
	vertex_data *head = NULL;
	vertex_data *tail = NULL;
	int length = 0;

}Graph;

Edge_data* Edge_malloc(int d, int height) {
	Edge_data *new_node = (Edge_data*)malloc(sizeof(Edge_data));
	new_node->Name = d;
	new_node->Edge_link = NULL;
	new_node->func.height = height;
	return new_node;
}

vertex_data* vertex_malloc(int d) {
	vertex_data *new_node = (vertex_data*)malloc(sizeof(vertex_data));
	new_node->Name = d;
	new_node->Edge_link = NULL;
	new_node->vertex_link = NULL;
	new_node->link = NULL;
	new_node->flag = false;
	return new_node;
}

vertex_data* find_int_data(Graph *A, int vertex_NAME) {
	vertex_data * p = (vertex_data*)malloc(sizeof(int));
	p = A->head;

	//���°Ÿ� ���� �Ҽ��� ����..
	while (p->Name != vertex_NAME && p != A->tail) {
		p = p->link;
	}
	if (p->Name == vertex_NAME)
		return p;
	else return NULL;
}


void insert_Edge_data(vertex_data *target, int Edge_Name, int height) {
	Edge_data *link = target->Edge_link; //Edge_link ���� error��ٸ� head�Ͱ��� �� �־��ֱ�.
	Edge_data * a = Edge_malloc(Edge_Name, height);
	if (link == NULL)target->Edge_link = a;
	else
	{
		a->Edge_link = target->Edge_link;
		target->Edge_link = a;
	}

}
void Add_Edge(Graph *A, int vertex_Name, int  Edge_data, int height)
{
	vertex_data *target = find_int_data(A, vertex_Name);
	insert_Edge_data(target, Edge_data, height);
}
void insert_node(Graph *A, vertex_data* new_node) {
	vertex_data *p = A->tail;

	A->length++;
	if (A->head == NULL && A->tail == NULL)
	{
		A->head = new_node;
		A->tail = new_node;
		new_node->vertex_link = A->head;
		new_node->link = A->tail;
	}//ù���� ���
	else//��������� ���ư��� ��
		//double list �� ���� �Ұ� ;;
	{

		new_node->vertex_link = A->tail;
		A->tail->link = new_node;
		new_node->link = A->tail;
		A->tail = new_node;
	}
}
//������� printf();
void display_vertex(Graph *A) {
	printf("\nstart_display_Vertex");
	vertex_data *link = A->head;

	while (link != A->tail) {

		printf("%d->", link->Name);
		link = link->link;
	}printf("%d->", link->Name);
	printf("finish_display_vertex");

}
void display_Edge(Graph *A, vertex_data *target) {

	printf("\nStart_display_Edge");
	Edge_data *link = target->Edge_link;
	printf("   %d��Edge:", target->Name);
	while (link != NULL) {
		printf("%d->", link->Name);
		link = link->Edge_link;
	}
	printf("Finish_display_Edge");

}

int flag(int *arrys, Edge_data* v) {
	int b = 0;

	while (arrys[b] != NULL) {
		if (arrys[b] == v->Name)
			break;
		else b++;
	}
	if (arrys[b] == v->Name)
		return false;
	else {
		arrys[b] = v->Name;
		return true;
	}
	//true ��?�������� insert(���������ʾҴ�������)
}//1,2,3,4,5  
 //using Q for Bre_SEARCHING

 //DFS�� ������� ������ ?;;
 //push pop �ʿ��Ѱ� 
vertex_data *find_Edge_node(Edge_data *E,vertex_data *V,int *table,Graph *A) {

	while (E != NULL) {
		if (flag(table, E))//true ���ο� ���
			break;
		else
			E = V->Edge_link;
	}
	if (E == NULL)return NULL;else
	return find_int_data(A, E->Name);
	//NULL ������ Edge_node �� ���ų� vertex_node �� ������;
}
//pop data �� ���� int �� ���ʿ䰡 ����...�ּҸ� return �Ҽ��� �մ�.
Edge_data *finding_Edge(Graph *A , Edge_data *E ) {
	while (find_int_data(A, E->Name)->flag == true && E != NULL) {
		E = E->Edge_link;
	}
	return E;
}
bool see_the_vertex_Edge_flag_all(Graph *A,vertex_data *v) {
	Edge_data *E = v->Edge_link;
	bool result = true;
	while (E != NULL)
	{
		if (find_int_data(A, E->Name)->flag == false)
		{
			result = false;
			break;
		}
		E = E->Edge_link;
	}
	return result;

}
void DFS(Graph *A) {
	printf("Start DFS");

	int* table = (int*)malloc(sizeof(int));
	vertex_data *v = A->head;
	Edge_data *E = v->Edge_link;
	stack a;
	int pop_int;
	//NULL �ϋ�  ���μ����� stack �ε� ��ü������ stack ���� ���......
	//head ->pushing
	//
	push(v->Name, &a);
	while (true) {

		while (E != NULL) {
			v = find_int_data(A, E->Name);
			if (v->flag == false)
			{	
				push(v->Name, &a); 
				v->flag = true;
 				E = v->Edge_link;
			}
			else { E = E->Edge_link; }
		}	
		if (is_empty_stack(&a))break;
		else if(see_the_vertex_Edge_flag_all(A,
			find_int_data(A, peek(&a)))) //function inserting 
			pop_int = pop(&a);
		else pop_int = peek(&a);
		//pop�Ҷ� ����� �س��� pushing

			v = find_int_data(A, pop_int);
			E = v->Edge_link;
	
	}

	
	//������ NULL find int data
		//��κ��� ����� �����尡 �̿�ȴ�.�ϴ� ��͹�ĸ��� �ٸ��� ������� ��͹�����ΰ��ٴ�.

	free(table);
		printf("Finish DFS");
	}

void BFS(Graph *A) {
	printf("\n Start BFS");
	vertex_data *p = A->head;	Queue q;
	Edge_data *x = p->Edge_link;
	int d;
	enqueue(&q, A->head->Name);
	
	while (!is_empty(&q)) {
		d = dequeue(&q);
		printf("%d->", d);
		if (find_int_data(A, d) == NULL)x == NULL;
		else
			x = find_int_data(A, d)->Edge_link;
		//flag ��� fucntion���γ����� flg�� �̿�.
		while (x != NULL) {
			if (find_int_data(A, x->Name)->flag == false)
			{
				enqueue(&q, x->Name);
				find_int_data(A, x->Name)->flag = true;
			}
			x = x->Edge_link;

		}
	}
	printf("Finishing BFS");
}

int main()
{

	Graph A;

	int d = 0;
	while (1) {
		printf("vertex_Name�� �Է��ϼ��� ���Է� �Ͻ��� 111�� �����ø� �����ϴ�.");
		scanf_s("%d", &d);
		if (d != 111)
		{
			insert_node(&A, vertex_malloc(d));
		}


		else 	 break;

	}
	display_vertex(&A);
	Add_Edge(&A, 1, 2, 30);
	Add_Edge(&A, 1, 3, 20);

	Add_Edge(&A, 1, 8, 20);
	Add_Edge(&A, 1, 9, 20);

	Add_Edge(&A, 9, 3, 20);
	Add_Edge(&A, 9, 4, 20);

	Add_Edge(&A, 2, 4, 10);
	Add_Edge(&A, 2, 5, 10);

	Add_Edge(&A, 3, 4, 10);
	Add_Edge(&A, 3, 6, 10);

	Add_Edge(&A, 4, 6, 10);
	Add_Edge(&A, 4, 5, 10);
	Add_Edge(&A, 4, 7, 10);
	

	Add_Edge(&A, 5, 7, 10);

	Add_Edge(&A, 6, 7, 10);

	display_Edge(&A, find_int_data(&A, 1));
	printf("\n");
	DFS(&A);
	//BFS(&A);

}
