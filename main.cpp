#include <iostream>

using namespace std;

template<typename T>
class Node
{
public:
	Node(T inputData) {
		this->data = inputData;
		this->next = nullptr;
		this->counter++;
	}
	void setCounter(int inputCounter) {
		this->counter = inputCounter;
	}
	int getCounter() {
		return counter;
	}
	void setNext(Node* inputNext) {
		this->next = inputNext;
	}
	T getData() {
		return data;
	}
	Node* getNext() {
		return next;
	}
private:
	T data;
	Node<T>* next;
	int counter = 0;
};

template<typename T>
class List
{
public:
	List() {
		this->first = nullptr;
		this->last = nullptr;
	}
	bool is_empty() { return first == nullptr; }
	void push_back(T val) {
		Node<T>* p = new Node<T>(val);
		p->setCounter(counter);
		counter++;
		if (is_empty()) {
			first = p;
			last = p;
			return;
		}
		last->setNext(p);
		last = p;
	}
	int findIndexElement(T data) {
		if (is_empty()) { cout << "Список пуст" << endl; }
		Node<T>* p = first;
		while (p) {
			if (p->getData() == data) { return p->getCounter(); }
			p = p->getNext();
		}
		cout << "Объект не найден" << endl;
		return -1;
	}
	void deleteFirst() {
		if (is_empty()) { return; }
		Node<T>* p = first;
		first = p->getNext();
		delete p;
	}
	void deleteLast() {
		if (is_empty()) { return; }
		if (first == last) {
			deleteFirst();
		}
		Node<T>* p = first;
		while (p->getNext() != last) {
			p = p->getNext();
		}
		p->setNext(nullptr);
		delete last;
		last = p;
		counter--;
	}
	void insert(const int index) {
		if (is_empty()) { return; }
		if (index == 0) { deleteFirst(); return; }
		if (index == counter) { deleteLast(); return; }
		Node<T>* p = first;
		for (int i = 0; i < index-1; i++)
		{
			p = p->getNext();
		}
		Node<T>* to_delete = p->getNext();
		p->setNext(to_delete->getNext());
		Node<T>* temp = to_delete;
		for (int i = temp->getCounter(); i < last->getCounter()-1; i++) {
			temp = temp->getNext();
			temp->setCounter(temp->getCounter() - 1);
		}
		to_delete->setNext(nullptr);
		delete to_delete;
	}
	int size() {
		return counter + 1;
	}
	Node<T>* begin() {
		return first;
	}
	Node<T>* end() {
		return last;
	}

	T operator [](const int index) {
		Node<T>* p = first;
		for (int i = 0; i < index; i++)
		{
			p = p->getNext();
		}
		return p->getData();
	}
private:
	Node<T>* first;
	Node<T>* last;
	int counter = 0;
};

int main() {
	setlocale(LC_ALL, "ru");
	List<int> L;
	L.push_back(1);
	L.push_back(2);
	L.push_back(4);
	L.push_back(3);
	L.deleteLast();
	L.push_back(5);
	L.insert(2);

	//проверка на утечку памяти при insert
	for (int i = 0;; i++) {
		L.push_back(i);
		L.insert(2);
		cout << L[2] << endl;
	}

	return 0;
}