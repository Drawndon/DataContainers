//ForwardList
#include <iostream>
#include <ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------\n"

class Element
{
	int Data; //Значение элемента
	Element* pNext; //Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;

#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;

class ForwardList
{
	Element* Head;
	size_t size;
public:
	Element* get_Head()const
	{
		return Head;
	}
	size_t get_size()const
	{
		return size;
	}
	ForwardList()
	{
		//Констуктор по умолчанию - создает пустой список
		Head = nullptr; //Если список пуст, то его Голова указывает на ноль
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(int size) :ForwardList()
	{
		while (size--) push_front(0);
		cout << "FLSizeConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		//Deep copy (Побитовое копирование):
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);
	}

	~ForwardList()
	{
		clock_t t_start = clock();
		while (Head) pop_front(); //pop_back() намного медленнее
		clock_t t_end = clock();
		cout << "FLDestructor:\t" << this << "\tcomplete for " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	}

	//				Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this; //0)Проверяем не является ли this и other одним и тем же объектом
		while (Head) pop_front();			//1)Старое значение объекта удаляется из памяти
		//2)	Deep copy (Побитовое копирование):
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data); так медленнее
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_front(Temp->Data);
		reverse(); //Разворачиваем список
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;
	}

	int operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
			return Temp->Data;

	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
			return Temp->Data;

	}

	//				Adding elements:
	void push_front(int Data)
	{
		////1) Создаем элемент и сохраняем в него добавляемое значение:
		//Element* New = new Element(Data);

		////2) Привязываем новый созданный элемент к началу списка
		//New->pNext = Head;

		////3) Переносим Голову на новый элемент (Отправляем новый элемент в Голову):
		//Head = New;

		Head = new Element(Data, Head);

		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		if (Index >= size) return push_back(Data);
		//1) Доходим до элемента перед вставляемым
		Element* Temp = Head;

		for (int i = 0; i < Index-1; i++) Temp = Temp->pNext;

		////2) Создаем добавляемый элемент:
		//Element* New = new Element(Data);

		////3) Пристыковываем новый элемент к его следующему элементу
		//New->pNext = Temp->pNext;

		////4) Пристыковываем предыдущий элемент к новому:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;

	}

	//				Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Head->pNext;
		//3) Удаляем удаляемый элемент из памяти:
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr) return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0) return pop_front();
		if (Index > Element::count) return;
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
	}

	//					Methods:
	void reverse()
	{
		ForwardList reverse; //Этот список будет задомнаперед
		while (Head) //Пока список содержит элементы
		{
			reverse.push_front(Head->Data); //Добавляем головной элемент в реверсный список
			pop_front(); //и удаляем начальный элемент списка
		}
		//Подменяем наш список реверсным
		/*Head = reverse.Head;
		size = reverse.size;*/
		*this = std::move(reverse); //Это встроенная функция, которая явным образом вызывает MoveAssignment, если он есть,
		//в противном случае Behavior is undefined
		reverse.Head = nullptr; //Поскольку реверсный список является локальной переменной для него будет вызван деструктор
		//который полностью его очистит, а он указывает на ту же память, на которую указывает наш основной список
		//следовательно деструктор удалит и наш основной список.
	}

	void print()const
	{
		/*
		Element* Temp = Head; //Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
		//Temp; //Указатель 'Temp';
		//Temp->...; //Элемент 'Temp';
		
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList fusion;
	for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	fusion.reverse();
	return fusion;
}


//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
#define MOVE_SEMANTIC_CHECK


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element = 5;

	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}

	//list.push_back(123);
	list.print();
	//list.pop_back();
	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();*/
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	//list1.print();
	for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab; cout << endl;
	
	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	//list2.print();
	for (int i = 0; i < list2.get_size(); i++) cout << list2[i] << tab; cout << endl;

	//ForwardList list3 = list1 + list2; //CopyConstructor
	//list3.print();

	ForwardList list3;
	cout << delimiter << endl;
	list3 = list1 + list2; //CopyAssignment
	cout << delimiter << endl;
	//list3.print();
	for (int i = 0; i < list3.get_size(); i++) cout << list3[i] << tab; cout << endl;

	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.insert(value, index);
	list1.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;

	list1.erase(index);*/
#endif // OPERATOR_PLUS_CHECK

#ifdef PERFORMANCE_CHECK



	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "ForwardList filled  for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK

#ifdef SUBSCRIPT_OPERATOR_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	clock_t  start;
	clock_t end;

	ForwardList list(n);
	start = clock();
	for (int i = 0; i < list.get_size(); i++) list[i] = rand() % 100;
	end = clock();
	cout << "Список заполнен за " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
	system("PAUSE");
	for (int i = 0; i < list.get_size(); i++) cout << list[i] << tab;
	cout << endl;
#endif // SUBSCRIPT_OPERATOR_CHECK

#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	clock_t t_start, t_end;

	ForwardList list1;
	t_start = clock();
	for (int i = 0; i < n; i++) list1.push_front(rand() % 100);
	t_end = clock();
	cout << "Список заполнен за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд" << endl;
	system("PAUSE");
	t_start = clock();
	ForwardList list2 = list1;
	t_end = clock();
	cout << "Копирование завершено за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд" << endl;

	//for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab; cout << endl;
	//for (int i = 0; i < list2.get_size(); i++) cout << list2[i] << tab; cout << endl;  
#endif // COPY_SEMANTIC_PERFORMANCE_CHECK

#ifdef MOVE_SEMANTIC_CHECK
	clock_t t_start, t_end;
	ForwardList list1;
	ForwardList list2;
	t_start = clock();
	for (int i = 0; i < 5000000; i++) list1.push_front(rand());
	for (int i = 0; i < 5000000; i++) list2.push_front(rand());
	t_end = clock();
	cout << "Lists filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;
	system("PAUSE");

	t_start = clock();
	ForwardList list3 = list1 + list2;
	t_end = clock();
	cout << "Lists concatenated for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;

	t_start = clock();
	ForwardList list4 = list3;
	t_end = clock();
	cout << "Lists copied for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;
#endif // MOVE_SEMANTIC_CHECK






}