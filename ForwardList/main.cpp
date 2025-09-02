//ForwardList
#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data; //Значение элемента
	Element* pNext; //Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		//Констуктор по умолчанию - создает пустой список
		Head = nullptr; //Если список пуст, то его Голова указывает на ноль
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		//1) Создаем элемент и сохраняем в него добавляемое значение:
		Element* New = new Element(Data);
		//2) Привязываем новый созданный элемент к началу списка
		New->pNext = Head;
		//3) Переносим Голову на новый элемент (Отправляем новый элемент в Голову):
		Head = New;
	}

	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}

	//				Removing elements:
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
	}

	//					Methods:
	void print()const
	{
		Element* Temp = Head; //Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Element element = 5;

	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	
	for (int i = 0; i < n; i++)
	{
		list.pop_front();
	}
	list.print();
	
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	
}