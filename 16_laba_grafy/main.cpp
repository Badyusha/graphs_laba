#include <cstdlib>
#include <iostream>
#include <vector> 

using namespace std;

int removedEdges = 0, removedVertex = 0;


// ��������� ��� ������������� ������ ��������� ����
struct AdjListNode
{
	int dest;
	struct AdjListNode* next;
};

// ��������� ��� ������������� ������ ���������
struct AdjList
{
	struct AdjListNode* head; // ��������� �� �������� ���� ������
};

// ��������� ��� ������������� �����. ���� ������������ ����� ������ �� ������� ���������.
// ������ ������� ����� V (����� ������ � �����)
struct Graph
{
	int V;
	struct AdjList* array;
};

// ��������������� ������� ��� �������� ���� ������ ������ ���������
struct AdjListNode* newAdjListNode(int dest)
{
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

// ��������� �������, ������� ������� ���� � V ���������
struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;

	// �������� ������� ������� ���������. ������ ������� ����� V
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	// ������������� ������� ������ ��������� ��� �������, ������ ������ = NULL
	int i;
	for (i = 0; i < V; ++i) {

		graph->array[i].head = new AdjListNode;
		graph->array[i].head->next = new AdjListNode;
		graph->array[i].head->next = NULL;
		graph->array[i].head = NULL;
	}
	return graph;
}

// ������� ��� ���������� ����� ����� ��������� src � dest
void addEdge(struct Graph* graph, int src, int dest)
{
	// ������� ����� ���� ��������� ��� dest � ��������� ��� � ������ src
	struct AdjListNode* newNode = newAdjListNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// ��� ��� ���� �����������������, ��������� ����� ����� �� dest � src
	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
	graph->array[dest].head->next = NULL;
}

// ������� ��� �������� ����� ����� ��������� src � dest
void removeEdge(struct Graph* graph, int src, int dest)
{
	struct AdjListNode* curr = graph->array[src].head;
	struct AdjListNode* prev = NULL;

	// ������� �����, ������� ����� �������
	while (curr != NULL && curr->dest != dest)
	{
		prev = curr;
		curr = curr->next;
	}

	// ���� ����� ����� �������, ������� ���
	if (curr != NULL)
	{
		// ���� ����� ��������� � ������ ������
		if (prev == NULL)
			graph->array[src].head = curr->next;
		else
			prev->next = curr->next;

		free(curr);
	}
	curr = NULL;
}

// ������� ��� �������� ������� v �� �����
void removeVertex(struct Graph* graph, int v)
{
	if (removedVertex) {
		cout << "\n������� ��� �������!\n";
		return;
	}

	// ������� ��� �����, ��������� � �������� v
	struct AdjListNode* curr = graph->array[v].head;

	int dest = curr->dest;
	// ������� ����� �� ������ ��������� � �������� v
	removeEdge(graph, v, dest);
	curr = curr->next;

	// ����������� ������, ���������� ��� ������ ��������� � �������� v
	free(graph->array[v].head);

	// �������� ��������� �� �������� ���� ������ ��������� � �������� v
	graph->array[v].head = NULL;
	cout << "\n�������!\n" << endl;
}

// ������� ��� ������ �����
void printGraph(struct Graph* graph)
{
	cout << "\n\t������� ���� ������������� ������� �� 0!" << endl;
	for (int v = 0; v < graph->V; ++v)
	{
		struct AdjListNode* pCrawl = graph->array[v].head;
		cout << "\n������ ��������� ������� " << v << "\nhead ";
		while (pCrawl)
		{
			cout << "-> " << pCrawl->dest;
			pCrawl = pCrawl->next;
		}
		cout << endl;
	}
}

void removeEdges(struct Graph* graph)
{
	if (removedEdges) {
		cout << "\n����� ��� �������!\n";
		return;
	}
	// �������� ����� ����� ��������� 1 � 2
	removeEdge(graph, 1, 2);

	// �������� ����� ����� ��������� 1 � 6
	removeEdge(graph, 1, 6);

	// �������� ����� ����� ��������� 6 � 8
	removeEdge(graph, 6, 8);

	// �������� ����� ����� ��������� 3 � 5
	removeEdge(graph, 3, 5);

	// �������� ����� ����� ��������� 3 � 6
	removeEdge(graph, 3, 6);
	++removedEdges;
	cout << "\n�������!\n" << endl;
}

int checkNumber(int val) {
	while (!(cin >> val)) {
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "\nInvalid value!\n";
		cout << "Try again: ";
	}
	return val;
}

int** createAdjacencyMatrix(struct Graph* graph)
{
	int V = graph->V;

	// ������� ���������� ������� � �������� V x V � ��������� �� ������
	int** matrix = new int* [V];
	for (int i = 0; i < V; ++i) {
		matrix[i] = new int[V];
		for (int j = 0; j < V; ++j) {
			matrix[i][j] = 0;
		}
	}

	// ��������� ������� ��������� �� ������ ������ ���������
	for (int v = 0; v < V; ++v) {
		struct AdjListNode* pCrawl = graph->array[v].head;
		while (pCrawl) {
			int dest = pCrawl->dest;
			matrix[v][dest] = 1;
			matrix[dest][v] = 1; // ��� ������������������ �����
			pCrawl = pCrawl->next;
		}
	}

	return matrix;
}

void main()
{
	system("chcp 1251");
	system("cls");

	// ������� ���� � 8 ���������
	struct Graph* graph = createGraph(8);

	// ��������� ����� � ����
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 7);
	addEdge(graph, 0, 5);
	addEdge(graph, 1, 5);
	addEdge(graph, 1, 2);
	addEdge(graph, 2, 4);
	addEdge(graph, 2, 5);
	addEdge(graph, 2, 3);
	addEdge(graph, 3, 4);
	addEdge(graph, 3, 6);
	addEdge(graph, 4, 5);
	addEdge(graph, 4, 6);
	addEdge(graph, 5, 6);
	addEdge(graph, 5, 7);
	addEdge(graph, 6, 7);

	while (1) {
		cout << "�������� ����� ����:\n"
			<< "1 - ������� ��� ����� � ������� 3\n"
			<< "2 - ������� ������� � ������� 6\n"
			<< "3 - ������� ����\n"
			<< "4 - ������� ������� ��������\n"
			<< "0 - �����\n";

		int menuChoice = 0;
		menuChoice = checkNumber(menuChoice);

		switch (menuChoice) {
		case 0: exit(0);
		case 1: removeEdges(graph);
			break;
		case 2: removeVertex(graph, 6);
			break;
		case 3: printGraph(graph);
			cout << endl;
			system("pause");
			system("cls");
			break;
		case 4: {
			int** adjacencyMatrix = createAdjacencyMatrix(graph);

			// ������� ������� ���������
			int V = graph->V;
			std::cout << "\n������� ���������:\n" << endl;
			for (int i = 0; i < V; ++i) {
				for (int j = 0; j < V; ++j) {
					std::cout << adjacencyMatrix[i][j] << " ";
				}
				std::cout << "\n";
			}
			cout << endl;
			// ����������� ������, ���������� ��� ������� ���������
			for (int i = 0; i < V; ++i) {
				delete[] adjacencyMatrix[i];
			}
			delete[] adjacencyMatrix;

			break;
		}
		default: cout << "\n�������� ��������!\n";
			break;
		}
	}
}
