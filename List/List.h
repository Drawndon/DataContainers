#pragma once

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*Class Ц это обращение к обычному классу
Class<type> -это обращение к шаблонному классу, type Ц определ€ет какого типа будут пол€ создаваемого объекта.
ƒл€ того, чтобы сделать класс шаблонным, перед ним достаточно просто создать шаблон :
template<typename T>*/

#define tab "\t"
#define delimiter "\n--------------------------------------------------\n"

/////////////////////////////////////////////////////////////////////////////////////////////
////////////				ќбъ€вление класса - Class Declaration		/////////////////////

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;

	}*Head, * Tail; //ќбъекты классов и структур и указатели на эти объекты можно
	//объ€вл€ть непосредственно после описани€ классов и структур
	size_t size; //–азмер списка. size_t - это typedef на 'unsigned int'
	class ConstBaseIterator
	{
	protected: //„тобы наследники увидели этот Ёлемент
		//Ётот класс обобщает свойства разных »тераторов
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		~ConstBaseIterator() {}


		//				Comparison operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		T operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		//					Increment/Decrement:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il); //ƒелегирование в прототипе не нужно, это часть реализации
	List(const List<T>& other);
	~List();

	//				Operators:
	List<T>& operator=(const List<T>& other);

	//				Adding Elements:
	void push_front(T Data);

	void push_back(T Data);

	void insert(T Data, int Index);

	//				Removing elelemts:
	void pop_front();
	void pop_back(); //ћен€ем зеркально pop_front()

	//				Methods:
	void print()const;
	void reverse_print()const;
};


////////////				 онец объ€вление класса - Class Declaration end /////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

