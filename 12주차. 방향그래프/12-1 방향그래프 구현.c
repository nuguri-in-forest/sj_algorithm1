#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

//�����ͱ��� ����
typedef struct node
{
	struct node* next;
	int index;
}NODE;

typedef struct vertex
{
	char name;
	struct node* out_list;
	struct node* in_list;
	int indegree;
}VERTEX;

typedef struct edge
{
	int a;
	int b;
	int id;
}EDGE;



typedef struct Graph
{
	VERTEX* vertices;
	EDGE* edges;
}GraphType;


typedef struct queue
{
	int f;
	int r;
	int* queue;
}QUEUE;

int* toporder;
int n, m;
int* in;

QUEUE Q;
GraphType G; //����׷��� G ����


NODE* get_node(int i)
{
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->index = i;
	new->next = NULL;
	return new;
}

int index(char vname)
{
	//������ �ε����� ��ȯ�Ѵ�.
	for (int i = 1; i <= n; i++)
		if (G.vertices[i].name == vname)
			return i;
}
void insertAdj(NODE* node, int i)
{
	//H�� ù ��� ��ġ�� ���� i�� ���ҷ� �ϴ� ��� ����
	NODE* new = get_node(i);
	new->next = node->next;
	node->next = new;
}

void edgeMethod(int id, char aname, char bname)
{
	int a, b;
	a = index(aname);
	b = index(bname);

	G.edges[id].a = a;
	G.edges[id].b = b;

	insertAdj(G.vertices[a].out_list, id);
	insertAdj(G.vertices[b].in_list, id);

	G.vertices[b].indegree++;
	return;
}

void initqueue()
{
	Q.f = 0;
	Q.r = n - 1;
}

int isempty()
{
	if ((Q.r + 1) % n == Q.f)
		return 1;
	else
		return 0;
}

void enqueue(int v)
{
	Q.r = (Q.r + 1) % n;
	Q.queue[Q.r] = v;
}
int dequeue()
{
	int v;
	v = Q.queue[Q.f];
	Q.f = (Q.f + 1) % n;
	return v;
}

void topologicalSort()
{
	int* in, t, u, w, e;
	NODE* temp;
	in = (int*)malloc(sizeof(int) * n + 1);

	initqueue();

	for (int i = 1; i <= n; i++)
	{
		in[i] = G.vertices[i].indegree;
		if (in[i] == 0)
			enqueue(i);
	}
	t = 1;

	while (!isempty())
	{
		u = dequeue();
		toporder[t] = u;
		t++;
		temp = G.vertices[u].out_list->next;
		while (temp != NULL)
		{
			e = temp->index;
			w = G.edges[e].b;
			in[w]--;
			if (in[w] == 0)
				enqueue(w);
			temp = temp->next;
		}
	}

	if (t <= n)
		toporder[0] = 0;
	else
		toporder[0] = 1;

	return;
}

void buildGraph()
{
	char vname, aname, bname;

	scanf("%d", &n);
	getchar();
	//������ 1������ n������ ���
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n + 1);
	toporder = (int*)malloc(sizeof(int) * (n + 1));
	Q.queue = (int*)malloc(sizeof(int) * n);

	//�������� �� ����,���Ⱓ������Ʈ�� ����� �ʱ�ȭ

	for (int i = 1; i <= n; i++)
	{
		scanf("%c", &vname);
		getchar();
		G.vertices[i].name = vname;
		G.vertices[i].out_list = get_node(-1);
		G.vertices[i].in_list = get_node(-1);
		G.vertices[i].indegree = 0;
	}
	//�������� �Է¹ޱ�
	scanf("%d", &m);
	getchar();

	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	for (int i = 0; i < m; i++)
	{
		scanf("%c %c", &aname, &bname);//����(a,b)
		getchar();
		edgeMethod(i, aname, bname);
	}
}

int main()
{
	buildGraph();
	topologicalSort();
	if (toporder[0] == 0)
		printf("0");
	else
	{
		for (int i = 1; i <= n; i++)
			printf("%c ", G.vertices[toporder[i]].name);
	}
}






