#include <iostream>
using namespace std;
class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		this->pPrev = pPrev;
		count++;
	}
	~Element()
	{
		count--;
	}
	friend class Iterator;
	friend class List;
	};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{

	}
};

class List
{
	Element* Head;
	Element* Tail;
	size_t size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (const int* it = il.begin(); it != il.end(); it++) push_back(*it);
	}
	List(const List& other) : List()
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~List()
	{

	}
	//				Operators
	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	//				Adding elements
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
			size++;
			return;
		}
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;

	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		size++;
	}
	//				Removing elements
	void pop_front()
	{

	}
	void pop_back()
	{

	}
};
void main()
{
	setlocale(LC_ALL, "");
}