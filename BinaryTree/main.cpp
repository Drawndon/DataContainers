#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-----------------------------------------------\n"
#define DEBUG
class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		Clear();
		cout << "TDestructor:\t" << this << endl;
		cout << delimeter;
	}
	void Clear()
	{
		Clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void Erase(int Data)
	{
		Erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

private:
	void Clear(Element*& Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);

		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void Erase(int Data, Element*& Root) //Передаем по ссылке, чтобы работать с оригиналом, а не с копией
	{
		if (Root == nullptr)return;
		Erase(Data, Root->pLeft);
		Erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				//Для того, чтобы дерево балансировалось при удалении элементов,
				//перед удалением его нужно взвесить:
				if (count(Root->pLeft) > count(Root->pRight))
				{
					//и если левая ветка тяжелее чем правая, то берем из нее максимальное значение
					//потому что оно ближе всего к удаляемому значению:
					Root->Data = maxValue(Root->pLeft);
					Erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					//в противном случае береж минимальное значение из правой ветки,
					//потому что оно ближе всего к удаляемому значению
					Root->Data = minValue(Root->pRight);
					Erase(minValue(Root->pRight), Root->pRight);
				}
			}

		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const
	{
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr) return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
	}
	int Sum(Element* Root)const
	{
		return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data) //Если меньше добавляем влево
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);

		}
		else if(Data > Root->Data)//Если больше добавляем вправо
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		//Если равны, ничего не делаем, вот и вся магия про уникальность
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}

};
//#define BASE_CHECK
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов в дереве: " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << u_tree.count() << endl;
	cout << "Сумма элементов в дереве: " << u_tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << u_tree.Avg() << endl;
#endif // BASE_CHECK

	Tree tree =
	{
			50,
		25,		75,
	 16,  32, 58, 85
	};
	int value;
	//cout << "Введите удаляемое значение: "; cin >> value;
	tree.Erase(25);
	tree.Erase(32);
	tree.Erase(50);
	tree.Erase(75);
	tree.print();

}