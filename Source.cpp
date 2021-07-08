#include<iostream>
using namespace std;
struct Graph;
Graph* front = nullptr;
struct Child
{
	Graph* connection;
	Child* next;
};

struct Graph
{
	int key;
	int count;
	Graph* next;
	Child* child;
};


Graph* Search(int a)
{
	if (front != nullptr)
	{
		Graph* current = front;
		while (current->key != a && current->next != nullptr)
		{
			current = current->next;
		}
		if (current->key == a)
		{
			return current;
		}
	}
	return nullptr;
}


void Add(int a)
{
	if (Search(a) == nullptr)
	{
		Graph* current = front;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new Graph;
		current->next->key = a;
		current->next->next = nullptr;
		current->next->child = nullptr;
		current->next->count = 0;
	}
}


void Add(Graph* current, int a)
{
	Add(a);

	Graph* temp = current;

	if (temp->child != nullptr) {
		while (temp->child->next != nullptr) {
			temp->child = temp->child->next;
		}

		temp->child->next = new Child;
		temp->child->next->connection = Search(a);
		temp->child->next->next = nullptr;
	}
	else {
		temp->child = new Child;
		temp->child->connection = Search(a);
		temp->child->next = nullptr;
	}

	Search(a)->count += 1;

}


Graph* FindZero()
{
	int temp;
	Graph* current = front;
	while (current != nullptr)
	{
		if (current->count == 0) {
			temp = current->key;
			return Search(temp);
		}

		current = current->next;
	}
	return nullptr;
}


bool Cicle() {
	Graph* current = front;
	while (current != nullptr) {
		int i = 0;
		Child* temp2 = current->child;
		while (temp2 != nullptr) {
			Child* temp = temp2;
			temp2 = temp2->next;
			while (temp != nullptr) {
				i++;
				if (temp->connection == current) {
					cout << "Graph cicle";
					return false;
				}
				temp = temp->connection->child;
				if (i > 10000) {
					cout << "Graph cicle";
					return true;
				}
			}
		}
		current = current->next;
	}
	return false;
}


void TopSort()
{
	Graph* current = FindZero();
	while ((current = FindZero()) != nullptr)
	{
		while (current->child != nullptr)
		{

			if (current->child != nullptr)
			{
				Child* temp = current->child;
				temp->connection->count -= 1;
				if (current->child->next != nullptr) {
					current->child = current->child->next;
				}
				else {
					current->child = nullptr;
				};
				delete[] temp;
			}
		}
		cout << current->key << ' ';
		current->count = -1;
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int from, to;
	while (true)
	{
		cout << "Откуда: ";
		cin >> from;
		if (from == 0) break;
		cout << "Куда: ";
		cin >> to;
		if (to == 0) break;
		while (from == to) {
			cout << "Граф не может идти сам в себя, введите корректно\n";
			cout << "Куда: ";
			cin >> to;
		}
		if (front == nullptr) {
			front = new Graph;
			front->key = from;
			front->next = nullptr;
			front->child = nullptr;
			front->count = 0;
			Add(front, to);
		}
		else {
			Add(from);
			Add(Search(from), to);
		}

	}
	if (!Cicle()) {
		TopSort();
	}
}