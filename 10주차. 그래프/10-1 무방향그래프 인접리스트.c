#pragma warning(disable:4996)
#include <stdio.h>
#include<stdlib.h>

//자료구조설정
typedef struct node {
	int index;
	struct node* next;
}NODE;

typedef struct vertex {
	NODE* adj_list;
	int id;
}VERTEX;

typedef struct edge {
	int weight;
	int a;
	int b;
	int id;
}EDGE;

typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}Graphtype;

Graphtype G;
int m;//간선의 개수

//노드반환
NODE* get_node(int i) {
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->index = i;
	new->next = NULL;
	return new;
}

//간선의 반대정점 반환
int opposite(NODE* node, int a) {
	EDGE edge = G.edges[node->index];
	if (edge.a == a) {
		return edge.b;
	}
	else {
		return edge.a;
	}
}

void insertAdj(int id, int a, int b) {
	NODE* node = G.vertices[a].adj_list;//삽입할 부착간선의 헤드
	NODE* new = get_node(id);//인덱스 id번 간선

	int z1, z2;
	if (node->next == NULL) {
		G.vertices[a].adj_list->next = new;
	}
	else {
		while (node->next != NULL) {
			//2번째 수행을 잡을 z1설정
			z1 = opposite(node->next, a);
			if (z1 > b) {
				new->next = node->next;
				G.vertices[a].adj_list->next = new;
				return;
			}
			//3번째부터 끝까지 수행을 잡을z2설정 
			else if (node->next->next != NULL) {
				z2 = opposite(node->next->next, a);
				if (z2 > b) {
					new->next = node->next->next;
					node->next->next = new;
					return;
				}
			}

			node = node->next;
		}

	}
	node->next = new;
}
void edgeMethod(int id, int a, int b, int w) {
	G.edges[id].id = id;
	G.edges[id].a = a;
	G.edges[id].b = b;
	G.edges[id].weight = w;

	insertAdj(id, a, b);
	if (a != b) {
		insertAdj(id, b, a);
	}
}
void removeEdge(int a, int b, int target) {
	//prev가 없기때문에 노드두개를 같이 굴린다
	NODE* node1 = G.vertices[a].adj_list->next;
	NODE* node2 = G.vertices[a].adj_list->next->next;

	while (node1 != NULL) {
		//헤드노드는 쓰레기노드고
		//그다음노드 그니까 첫원소가 삭제될때는
		//헤드노드의 다음노드(첫원소)를 새로 설정해주어야함
		if (G.vertices[a].adj_list->next->index == target) {
			free(G.vertices[a].adj_list->next);
			G.vertices[a].adj_list->next = node2;
			return;
		}
		//즉 node2가 실제로 리스트를 순회하는 역할
		else if (node2->index == target) {
			node1->next = node2->next;
			free(node2);
			return;
		}
		node1 = node1->next;
		node2 = node2->next;
	}
}
void removeMethod(int a, int b, int target) {
	//먼저 간선정보 삭제
	//여기서 target은 간선의 id를 말함
	G.edges[target].id = -1;
	removeEdge(a, b, target);
	if (a != b) {
		removeEdge(b, a, target);
	}
}
void modifyMethod(int a, int b, int w) {
	//1.정점 a,b의 존재를 확인한다
	if (a <= 0 || a > 6) {
		printf("-1\n");
		return;
	}
	if (b <= 0 || b > 6) {
		printf("-1\n");
		return;
	}
	//2. 간선을 순회하면서 타겟간선 (a,b)의 인덱스를 찾는다
	//이때 a<b이므로 a,b중 작은것이 target_a, 큰 것이 target_b
	int target_index = -1, target_a, target_b;
	if (a < b) {
		target_a = a;
		target_b = b;
	}
	else {
		target_a = b;
		target_b = a;
	}
	//간선순회 및 타겟 간선 인덱스 찾기
	for (int i = 0; i < m; i++) {
		if (G.edges[i].a == target_a && G.edges[i].b == target_b && G.edges[i].id != -1) {
			target_index = i;
			break;
		}
	}

	//3.w의 값에 따라 변경,삭제,생성 명령을 수행한다
	//4.간선이 존재하는 경우
	if (target_index != -1) {
		if (w == 0) {
			removeMethod(a, b, target_index);
			return;
		}//간선이 존재하는데 w가 0이면 삭제
		else {//간선이 존재하는데 w가 0이 아니면 변경
			G.edges[target_index].weight = w;
		}
	}
	//5.간선이 존재하지 않는 경우
	else if (target_index == -1) {
		if (w == 0) {//아무것도 하지않음
			return;
		}
		else {//생성
			edgeMethod(m++, a, b, w);
			return;
		}
	}

}

void printAdj(int a) {
	if (a <= 0 || a > 6) {
		printf("-1\n");
		return;
	}
	NODE* head = G.vertices[a].adj_list;
	int z;
	int e;
	while (head->next != NULL) {
		z = opposite(head->next, a);//간선에서 a 반대편 정점z
		e = head->next->index;
		printf(" %d %d", G.vertices[z].id, G.edges[e].weight);
		head = head->next;
	}
	printf("\n");
}

void buildGraph() {
	//정점은 7개생성해서 1번부터 6번까지사용
	//간선은 최대 21개이므로 21개 생성
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * 7);
	G.edges = (EDGE*)malloc(sizeof(EDGE) * 21);

	//정점삽입 및 인접리스트 헤드노드 초기화
	for (int i = 1; i <= 6; i++) {
		G.vertices[i].id = i;
		G.vertices[i].adj_list = get_node(-1);
	}
	//그래프 그림에 따라 간선 삽입
	m = 0;//m은 간선의 현재개수
	edgeMethod(m++, 1, 2, 1);

	//1번간선
	edgeMethod(m++, 1, 3, 1);

	//2번간선
	edgeMethod(m++, 1, 4, 1);

	//3번간선
	edgeMethod(m++, 1, 6, 2);

	//4번간선
	edgeMethod(m++, 2, 3, 1);

	//5번간선
	edgeMethod(m++, 3, 5, 4);
	//6번간선
	edgeMethod(m++, 5, 5, 4);
	//7번간선
	edgeMethod(m++, 5, 6, 3);
}
int main() {
	//그래프 빌드를 먼저하고
	buildGraph();

	//대화형 프로그램 시작
	char com;

	while (1) {
		scanf("%c", &com);
		if (com == 'a') {
			int number;
			scanf("%d", &number);
			printAdj(number);
		}
		else if (com == 'm') {
			int a, b, w;
			scanf("%d %d %d", &a, &b, &w);
			modifyMethod(a, b, w);
		}
		else if (com == 'q') {
			break;
		}
		getchar();
	}
	return 0;
}