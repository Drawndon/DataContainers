#include <iostream>
using namespace std;


#define tab "\t"
#define delimiter "\n--------------------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
		friend class Iterator;
		friend List operator+(const List& left, const List& right);

	}*Head, *Tail; //Объекты классов и структур и указатели на эти объекты можно
	//объявлять непосредственно после описания классов и структур
	size_t size; //Размер списка. size_t - это typedef на 'unsigned int'
public:
	class Iterator
	{
	protected:
		Element* Temp;
	public:

		Iterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << "ITConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ITDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int operator*() const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Element* get_Head()const
	{
		return Head;
	}
	Element* get_Tail()const
	{
		return Tail;
	}
	size_t get_size()const
	{
		return size;
	}
	Iterator begin() const
	{
		return Head;
	}
	Iterator end() const
	{
		return nullptr;
	}
	List(Element* Head = nullptr, Element* Tail = nullptr, int size = 0) : Head(Head), Tail(Tail), size(size)
	{
		cout << "LConstructor:\t" << this << endl;
	}
	explicit List(int size) :List()
	{
		while (size--) push_front(0);
		cout << "LSizeConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
		cout << "ListitConstructor:\t" << this << endl;
	}
	List(const List& other) : List()
	{
		//Deep copy (побитовое копирование)
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	List(List&& other) noexcept : List()
	{
		//Shallow copy (поверхностное копирование)
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//      Operators
	List& operator=(const List& other)
	{
		if (this == &other) return *this; //0) Проверить, что This и Other разные объекты
		while (Head) pop_front();         //1) Очистить данные
		//2)Deep copy (побитовое копирование)
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;
	}

	const int& operator[] (int index) const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
		return Temp->Data;
	}

	int& operator[] (int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
		return Temp->Data;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		//1) Создаем элемент, в котором будет храниться добавляемое значение:
		Element* New = new Element(Data);

		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			//2) Пристыковываем новый элемент к списку:
			New->pNext = Head;

			//3) Пристыковываем начальный элемент списка к новому элементу:
			Head->pPrev = New;

			//4) Делаем новый элемент начальным элементом списка:
			Head = New;
		}

		size++;
	}

	void push_back(int Data)
	{
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = New;
		else
		{
			//2) Цепляем новый элемент за хвост списка
			New->pPrev = Tail;

			//3) Пристыковываем список к новому элементу:
			Tail->pNext = New;

			//4) Делаем новый элемент хвостом списка:
			Tail = New;
		}
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index < 0) return;
		if (Index == 0 || size == 0) return push_front(Data); //Проверяем граничные условия
		if (Index >= size) return push_back(Data); //Проверяем граничные условия
		//1) Доходим до нужного элемента:
		Element* Temp;
		if (Index < size / 2) // Определяем с какой стороны заходить, либо через Голову, либо через Хвост
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//Независимо от того, каким образом мы дошли до нужного элемента, сначала списка или с конца
		//списка, процедура добавления элемента будет идентичной:
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//2) Создаем новый элемент:
		Element* New = new Element(Data);

		//3) Пристыковываем новый элемент к списку:
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;

		//4) Вклиниваем новый элемент в список:
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;

		size++;

	}

	//				Removing elelemts:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)	//Если Голова и Хвост равны, значит они указывают либо на 0,
			//либо на один и тот же элемент
			//Ситуацию с пустым списком обрабатывает предыдущее условие.
			//Ситуацию с вырожденным списком обрабатывает текущее условие, 
			//и в этом if удаляется один единственный элемент списка
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			//			Общий случай:
			//1) Смещаем Голову на следующий элемент:
			Head = Head->pNext;

			//2) Удаляем элемент из памяти:
			delete Head->pPrev;

			//3) Обнуляем указатель на удаленный элемент (делаем Head последним элементом списка):
			Head->pPrev = nullptr;

		}
		size--;
	}

	void pop_back() //Меняем зеркально pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return; // Если список пуст
		if (Head == Tail)
		{
			delete Head; // Можно Tail
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}

	void erase(int Index)
	{
		if (Index < 0) return;
		if (Index == 0 || size == 0) return pop_front();
		if (Index >= size) return pop_back();
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Element* Erased = Temp;
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Erased;
		size--;
	}

	//				Methods:
	void print()const
	{
		cout << delimiter << endl;
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail: " << Tail << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout << "Tail: " << Tail << endl;
		for (Element * Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head: " << Head << endl;
		cout << "Количество элементов списка: " << size<<  endl;
		cout << delimiter << endl;

	}
	void reverse()
	{
		List reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}
		*this = std::move(reverse);
		reverse.Head = nullptr;
	}
	friend class Element;
	friend List operator+(const List& left, const List& right);

};

List operator+(const List& left, const List& right)
{
	List fusion;
	for (List::Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	for (List::Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	fusion.reverse();
	return fusion;

}


//#define BASE_CHECK
#define HOME_WORK


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	list.pop_front(); // Проверяем на пустом списке, еще не заполнен
	list.print();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	/*list.pop_back();
	list.print();
	list.reverse_print();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK


#ifdef HOME_WORK
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;
	list3.erase(5);
	list3.print();
#endif // HOME_WORK


}