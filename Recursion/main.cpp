#include <iostream>
using namespace std;

void elevator(int floor);
size_t factorial(int n);
double power(double a, int b);
int fibonacci(int n);

//#define ELEVATOR_CHECK
//#define FACTORIAL_CHECK
//#define POWER_CHECK
//#define FIBONACCI_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef ELEVATOR_CHECK
	int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);
	//cout << "Recursion";
	//main(); Бесконечный цикл, а глубина стека ограничена  
#endif // ELEVATOR_CHECK

#ifdef FACTORIAL_CHECK
	int fact;
	cout << "Введите число, факториал которого необходимо вычислить: "; cin >> fact;
	cout << "Факториал: " << fact << " равен " << factorial(fact) << endl;
#endif // FACTORIAL_CHECK

#ifdef POWER_CHECK
	double a;
	int b;
	cout << "Введите основание: "; cin >> a;
	cout << "Введите степень: "; cin >> b;
	cout << "Число: " << a << " в степени " << b << " равно " << power(a, b) << endl;
#endif // POWER_CHECK

#ifdef FIBONACCI_CHECK
	int num;
	cout << "Введите число до которого надо вывести ряд Фибоначчи: "; cin >> num;
	cout << "Ряд Фибоначчи: ";
	int next, i = 0;
	while ((next = fibonacci(i)) <= num)
	{
		cout << next << " ";
		i++;
	}
#endif // FIBONACCI_CHECK


}

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}

size_t factorial(int n)
{
	return n == 1 || n == 0 ? 1 : n * factorial(n - 1);
}
double power(double a, int b)
{
	return b == 0 ? 1 : b < 0 ? 1 / power(a, -b) : a * power(a, b - 1);
}
int fibonacci(int n)
{
	return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}