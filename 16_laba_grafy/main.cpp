#include <cstdlib>
#include <iostream>
#include <vector> 

using namespace std;

int removedEdges = 0, removedVertex = 0;


// Структура для представления списка смежности узла
struct AdjListNode
{
	int dest;
	struct AdjListNode* next;
};

// Структура для представления списка смежности
struct AdjList
{
	struct AdjListNode* head; // указатель на головной узел списка
};

// Структура для представления графа. Граф представляет собой массив из списков смежности.
// Размер массива будет V (число вершин в графе)
struct Graph
{
	int V;
	struct AdjList* array;
};

// вспомогательная функция для создания узла нового списка смежности
struct AdjListNode* newAdjListNode(int dest)
{
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

// Служебная функция, которая создает граф с V вершинами
struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;

	// Создание массива списков смежности. Размер массива будет V
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	// Инициализация каждого списка смежности как пустого, сделав начало = NULL
	int i;
	for (i = 0; i < V; ++i) {

		graph->array[i].head = new AdjListNode;
		graph->array[i].head->next = new AdjListNode;
		graph->array[i].head->next = NULL;
		graph->array[i].head = NULL;
	}
	return graph;
}

// Функция для добавления ребра между вершинами src и dest
void addEdge(struct Graph* graph, int src, int dest)
{
	// Создаем новый узел смежности для dest и добавляем его в список src
	struct AdjListNode* newNode = newAdjListNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Так как граф неориентированный, добавляем также ребро от dest к src
	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
	graph->array[dest].head->next = NULL;
}

// Функция для удаления ребра между вершинами src и dest
void removeEdge(struct Graph* graph, int src, int dest)
{
	struct AdjListNode* curr = graph->array[src].head;
	struct AdjListNode* prev = NULL;

	// Находим ребро, которое нужно удалить
	while (curr != NULL && curr->dest != dest)
	{
		prev = curr;
		curr = curr->next;
	}

	// Если такое ребро найдено, удаляем его
	if (curr != NULL)
	{
		// Если ребро находится в начале списка
		if (prev == NULL)
			graph->array[src].head = curr->next;
		else
			prev->next = curr->next;

		free(curr);
	}
	curr = NULL;
}

// Функция для удаления вершины v из графа
void removeVertex(struct Graph* graph, int v)
{
	if (removedVertex) {
		cout << "\nВершина уже удалена!\n";
		return;
	}

	// Удаляем все ребра, связанные с вершиной v
	struct AdjListNode* curr = graph->array[v].head;

	int dest = curr->dest;
	// Удаляем ребро из списка связанных с вершиной v
	removeEdge(graph, v, dest);
	curr = curr->next;

	// Освобождаем память, выделенную для списка связанных с вершиной v
	free(graph->array[v].head);

	// Обнуляем указатель на головной узел списка связанных с вершиной v
	graph->array[v].head = NULL;
	cout << "\nУдалено!\n" << endl;
}

// Функция для вывода графа
void printGraph(struct Graph* graph)
{
	cout << "\n\tВершины были пронумерованы начиная от 0!" << endl;
	for (int v = 0; v < graph->V; ++v)
	{
		struct AdjListNode* pCrawl = graph->array[v].head;
		cout << "\nСписок смежности вершины " << v << "\nhead ";
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
		cout << "\nРебра уже удалены!\n";
		return;
	}
	// Удаление ребра между вершинами 1 и 2
	removeEdge(graph, 1, 2);

	// Удаление ребра между вершинами 1 и 6
	removeEdge(graph, 1, 6);

	// Удаление ребра между вершинами 6 и 8
	removeEdge(graph, 6, 8);

	// Удаление ребра между вершинами 3 и 5
	removeEdge(graph, 3, 5);

	// Удаление ребра между вершинами 3 и 6
	removeEdge(graph, 3, 6);
	++removedEdges;
	cout << "\nУдалено!\n" << endl;
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

	// Создаем квадратную матрицу с размером V x V и заполняем ее нулями
	int** matrix = new int* [V];
	for (int i = 0; i < V; ++i) {
		matrix[i] = new int[V];
		for (int j = 0; j < V; ++j) {
			matrix[i][j] = 0;
		}
	}

	// Заполняем матрицу смежности на основе списка смежности
	for (int v = 0; v < V; ++v) {
		struct AdjListNode* pCrawl = graph->array[v].head;
		while (pCrawl) {
			int dest = pCrawl->dest;
			matrix[v][dest] = 1;
			matrix[dest][v] = 1; // Для неориентированного графа
			pCrawl = pCrawl->next;
		}
	}

	return matrix;
}

void main()
{
	system("chcp 1251");
	system("cls");

	// Создаем граф с 8 вершинами
	struct Graph* graph = createGraph(8);

	// Добавляем ребра в граф
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
		cout << "Выберите пункт меню:\n"
			<< "1 - Удалить все ребра с номером 3\n"
			<< "2 - Удалить вершину с номером 6\n"
			<< "3 - Вывести граф\n"
			<< "4 - Вывести матрицу смежност\n"
			<< "0 - Выход\n";

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

			// Выводим матрицу смежности
			int V = graph->V;
			std::cout << "\nМатрица смежности:\n" << endl;
			for (int i = 0; i < V; ++i) {
				for (int j = 0; j < V; ++j) {
					std::cout << adjacencyMatrix[i][j] << " ";
				}
				std::cout << "\n";
			}
			cout << endl;
			// Освобождаем память, выделенную для матрицы смежности
			for (int i = 0; i < V; ++i) {
				delete[] adjacencyMatrix[i];
			}
			delete[] adjacencyMatrix;

			break;
		}
		default: cout << "\nНеверное значение!\n";
			break;
		}
	}
}
