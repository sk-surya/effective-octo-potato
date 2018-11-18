#include <iostream>
#include <queue>

#define inf -1
#define weight 6
using namespace std;

struct node
{
	int value = 0;
	struct node *next = NULL;
};
typedef struct node NODE;

struct LList
{
	NODE *head = new NODE();
	struct node *tail;
};
typedef struct LList LLIST;

int v_count;
LLIST *Adj = NULL;
void addEdge(const int& v1, const int& v2)
{
	NODE *ptr = new NODE();
	ptr->value = v2;

	if (Adj[v1 - 1].head->value == 0) //value 0 means no neighbours yet
	{
		Adj[v1 - 1].head = ptr;
		Adj[v1 - 1].tail = Adj[v1 - 1].head;
	}
	else
	{
		Adj[v1 - 1].tail->next = ptr;
		Adj[v1 - 1].tail = ptr;
	}
}
void printAdj(void)
{
	//if zero is printed, it means no neighbours
	for (int i = 0; i < v_count; i++)
	{
		cout << "Adjacency list of " << i + 1 << " :" << endl;
		NODE *ptr = Adj[i].head;

		bool flag = 1;
		while (flag)	
		{
			cout << ptr->value;
			if (ptr->next == NULL)
				flag = 0;
			else
			{
				ptr = ptr->next;
				cout << ",";
			}
		}
		cout << endl;
	}
}

struct Graph {
	int *V;
	LLIST *Nei;
};
enum color { WHITE, GRAY, BLACK };
struct vertex {
	//int label = -1;
	int color = WHITE;
	int d = inf;
};
vertex * BFS(const Graph& G, const int& x)
{
	int s = x - 1;
	vertex *Vx = new vertex[v_count];
	Vx[s].color = GRAY;
	Vx[s].d = 0;

	queue<int> Q;
	Q.push(s);
	while (Q.empty() != true)
	{
		int u = Q.front();
		Q.pop();
		NODE *ptr = G.Nei[u].head;
		bool flag = 1;
		while (flag && ptr->value!=0)
		{
			int v = ptr->value - 1;
			if (Vx[v].color == WHITE)
			{
				Vx[v].color = GRAY;
				Vx[v].d = Vx[u].d + weight;
				Q.push(v);
			}
			if (ptr->next == NULL)
				flag = 0;
			else
				ptr = ptr->next;
		}
		Vx[u].color = BLACK;
	}
	return Vx;
}
int main()
{
	int queries, nodes, edges, v1, v2, source;
	cin >> queries;

	for (int q = 0; q < queries; q++)
	{
		cin >> nodes >> edges;
		v_count = nodes;

		int *Vertices = new int[nodes];
		Adj = new LLIST[v_count];

		for (int i = 0; i < edges; i++)
		{
			cin >> v1 >> v2;
			addEdge(v1, v2);
			addEdge(v2, v1);
		}

		cin >> source;
		Graph G;
		G.V = Vertices;
		G.Nei = Adj;
		vertex *Vs = BFS(G, source);
		for (int i = 0; i < v_count; i++)
		{
			if (i != source-1)
				cout << Vs[i].d << " ";
		}
		cout << endl;
		//printAdj();
	}
}
