#include <iostream>
using namespace std;
//создание структуры
struct Info {
	int year;
	char name[20];
};
struct Tree {
	Info *info;
	Tree *left;
	Tree *right;
};
//прототипы функций
Tree *func_create_element();
Tree *func_add_element(Tree*, Tree *);
bool func_search(Tree*, int);
void func_result(Tree*, int);
int main()
{
	setlocale(LC_ALL, "Ru");
	Tree *head_tree = NULL; Tree *new_element = NULL;
	bool check = true;//переменная,которая позволяет работать циклу(check=false,если пользователь желает выйти из программы) 
	int number;
	while (check)
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "Список функций:"<<endl;
		cout << "1)Добавление элемента в дерево" << endl;
		cout << "2)Вывод информации о элементе из дерева" << endl;
		cout << "3)Выход из программы" << endl;
		while (true)
		{
			cout << "Выберите функцию:"; cin >> number;
			if (!cin)//проверка на корректный ввод int
			{
				cout << "Ошибка при вводе числа!!!";
				cin.clear();//очищаем флаг ошибки cin(следующая операции ввода будет работать правильно) 
				cin.ignore(100, '\n');//вынимаем 100 символов из буфера и останавливаемся, если встречаем новую строку(\n) или 100 символов(100-просто число символов,которое предпологает,что пользователь не будет вводить 100 символов)
				cout << endl;
			}
			else
				break;
		}
		switch (number)
		{
		case 1:
			new_element=func_create_element();//вызов функции,которая создает новый элемент 
			if (func_search(head_tree, new_element->info->year) == false)//проверка на наличие одинаковых элементов в дереве
				head_tree = func_add_element(head_tree, new_element);//вызов функции,которая добавляет новый элемент в дерево
			else
				cout << "Данные с таким годом уже существуют!!!" << endl;
			break;
		case 2:
			int needed_number;
			while (true)
			{
				cout << "Введите год нужного вам элемента:"; cin >> needed_number;
				if (!cin)
				{
					cout << "Ошибка при вводе числа!!!";
					cin.clear();
					cin.ignore(100, '\n');
					cout << endl;
				}
				else
					break;
				
			}
			if (func_search(head_tree, needed_number) == true)
			{
				func_result(head_tree, needed_number);//вызов функции,которая вывод элемент с нужным для пользователя годом  
			}
			else
				cout << "Данных с таким годом не существует" << endl;
			break;
		case 3:
			check = false;//операция,котрая выходит из нашего цикла(т.к while(check))
			cout << "ВЫХОД ИЗ ПРОГРАММЫ" << endl; break;
		default:
			cout << "Функции с таким номером не существует!!!" << endl;
			break;
		}
	}
	system("pause");
	return 0;

}
Tree *func_create_element()//функция,создающая новый элемент нашего дерево
{
	Tree *add_element= new Tree; add_element->info = new Info;
	add_element->left = 0; add_element->right = 0;
	while (true)
	{
		cout << "Введите год:";
		cin >> add_element->info->year;
		if (!cin)
		{
			cout << "Ошибка при вводе числа!!!";
			cin.clear();
			cin.ignore(100, '\n');
			cout << endl;
		}
		else
			break;
	}
	cout << "Введите имя:";
	cin.ignore(); cin.getline(add_element->info->name, 20);
	return add_element;
}
Tree *func_add_element(Tree*pointer, Tree *add_element)//функция,которая добавляет новый элемент в наше дерево(в зависимости от года)
{
	Tree *begin_pointer = pointer;
	if (pointer == NULL) { return add_element; }//если корень дерева пуст
	else
	{
		while (true)
		{
			if (add_element->info->year < begin_pointer->info->year && begin_pointer->left == 0)//если левый потомок дерева=0 и год добавляемого элмента меньше года предка нашего дерева 
			{
				begin_pointer->left = add_element; break;//левому потомку присваеваем значение добавляемого элемента 
			}
			if (add_element->info->year > begin_pointer->info->year && begin_pointer->right == 0)//елси правый потомок дерева=0 и год добавляемого элмента меньше года предка нашего дерева 
			{
				begin_pointer->right = add_element; break;//правому потомку присваеваем значение добавляемого элемента
			}
			else//елси потомки уже заполнены или год добавляемого больше или меньше года потомка
			{
				if (add_element->info->year < begin_pointer->info->year)//если год добавляемого элемента меньше года предка дерева,то двигаемся к левому потомку 
				{
					begin_pointer = begin_pointer->left;
				}
				else	
				{
					begin_pointer = begin_pointer->right;
				}
			}
		}
	}
	return pointer;
}
void func_result(Tree* pointer, int needed_number)//функция,которая выводит пользователю элемент дерева с годом needed_number 
{
	while (true)
	{
		if (needed_number == pointer->info->year)
		{
			cout << "Год:" << pointer->info->year << endl;
			cout << "Имя:" << pointer->info->name << endl;
			break;
		}
		else
		{
			if (needed_number > pointer->info->year)
				pointer = pointer->right;
			else
				pointer = pointer->left;
		}
	}
} 
bool func_search(Tree* pointer, int needed_number)//функция,которая возвращает true,если элемент найден и false,если элемент не найден
{
	if (pointer == 0)
		return false;
	if (needed_number == pointer->info->year)
		return true;
	while (true)
	{
		if (needed_number > pointer->info->year)
		{
			if (pointer->right == 0)
				return false;
			if (pointer->right->info->year == needed_number)
				return true;
			pointer = pointer->right;
		}
		else
		{
			if (pointer->left == 0)
				return false;
			if (pointer->left->info->year == needed_number)
				return true;
			pointer = pointer->left;
		}
	}
}