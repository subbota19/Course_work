#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
struct Bus   //создание стркуктуры
{
	char FIO[30];
	int number_bus;
	int way;
};
struct List {
	Bus *bus;
	List *next;
};
//прототипы функций
void creat_file();
List * func_added_bus(List *, char*, int, int );
List *func_delete_bus(List *, int );
List *func_search_bus(List *, int);
void func_result(List *);
List*create_start_list(List*);
int main()
{
	setlocale(LC_ALL, "Ru");
	List *bus_in_park = NULL; List *bus_in_way = NULL;//создаем два указателя и инициализируем их=NULL
	List *need_element;//создаем указатель,который будет использоваться в функции поиска элемента   
	cout << "---------------------------------------------------------------" << endl;
	cout << "Программа 'Автобусный парк'" << endl;
	bus_in_park=create_start_list(bus_in_park);//вызываем функцию,которая записывает из файла данные в список автобусов в парке
	bool check = true;//переменная,которая позволяет работать циклу(check=false,если пользователь желает выйти из программы) 
	int need_number_bus;//создаем переменную(в нее будем записывать номер автобуса,который хотим отправить в парк или в путь)
	int choice_func;//создаем переменную(пользователь будет вводить в нее нужный номер функии ) 
	while (check)
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "1)Отправление автобуса в путь" << endl;
		cout << "2)Отправление автобуса в автобусный парк" << endl;
		cout << "3)Вывод информации об автобусах в парке" << endl;
		cout << "4)Вывод информации об автобусах в пути" << endl;
		cout << "5)Выход из программы" << endl;
		while (true)
		{
			cout << "Выберите функцию:";
			cin >> choice_func;//создаем переменную(пользователь будет вводить в нее нужный номер функии )
			if (!cin)//проверка на корректный ввод int
			{
				cout << "Ошибка при вводе числа!!!";
				cin.clear();//очищаем флаг ошибки cin(следующая операции ввода будет работать правильно) 
				cin.ignore(100, '\n');//вынимаем 100 символов из буфера и останавливаемся, если встречаем новую строку(\n) или 100 символов(100-просто число символов,которое предпологает,что пользователь не будет вводить 100 символов) )
				cout << endl;
			}
			else
				break;
		}
		switch (choice_func)
		{
		case 1:
			cout << "---------------------------------------------------------------" << endl;
			cout << "Отправление автобуса в путь" << endl;
			while (true)
			{
				cout << "---------------------------------------------------------------" << endl;
				cout << "Введите номер автобуса:";
				cin >> need_number_bus;//вводим нужный номер автобуса
				if (!cin)
				{
					cout << "Ошибка при вводе числа!!!";
					cin.clear();
					cin.ignore(100,'\n');
					cout << endl;
				}
				else
					break;
			}
			need_element = func_search_bus(bus_in_park, need_number_bus);//указаелю need_element передаем данные об автобусе с номером need_number_bus
			if (need_element == 0) cout << "Автобуса с таким номером не сущесвует" << endl;//если такого номера не существует в списке автобусов в парке
			else
			{
				bus_in_way = func_added_bus(bus_in_way, need_element->bus->FIO, need_element->bus->number_bus, need_element->bus->way);//вызывваем функцию,которая добавляет в список автобусов в пути данные из указателя need_element
				bus_in_park = func_delete_bus(bus_in_park, need_number_bus);//вызываем функцию,которая удаляет данные об автобусе в парке с номером need_number 
			}
			break;
		case 2:
			cout << "---------------------------------------------------------------" << endl;
			cout << "Отправление автобуса в автобусный парк" << endl;
			while (true)
			{
				cout << "---------------------------------------------------------------" << endl;
				cout << "Введите номер автобуса:";
				cin >> need_number_bus;
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
			need_element = func_search_bus(bus_in_way, need_number_bus); // указаелю need_element передаем данные об автобусе с номером need_number_bus
			if (need_element == 0)//если такого номера не существует в списке автобусов в парке
			{
				cout << "Автобуса с таким номером не сущесвует" << endl; 
			}
			else
			{
				bus_in_park = func_added_bus(bus_in_park, need_element->bus->FIO, need_element->bus->number_bus, need_element->bus->way);//вызывваем функцию,которая добавляет в список автобусов в парке данные из указателя need_element
				bus_in_way = func_delete_bus(bus_in_way, need_number_bus);//вызываем функцию,которая удаляет данные об автобусе в парке с номером need_number
			}
			break;
		case 3:
			cout << "---------------------------------------------------------------" << endl;
			cout << "Вывод информации об автобусах в автобусном парке" << endl;
			if (bus_in_park == 0)//если список пуст
			{
				cout << "Список автобусов пуст" << endl;
			}
			else
				func_result(bus_in_park);//вызов функции,которая выводит список на экран
			break;
		case 4:
			cout << "---------------------------------------------------------------" << endl;
			cout << "Вывод информации об автобусах в пути" << endl;
			if (bus_in_way == 0)//если список пуст
			{
				cout << "Список автобусов пуст" << endl;
			}
			else
				func_result(bus_in_way);//вызов функции,которая выводит список на экран
			break;
		case 5:
			check = false;//операция,котрая выходит из нашего цикла(т.к while(check))
			cout << "ВЫХОД ИЗ ПРОГРАММЫ" << endl;break;
		default:
			cout << "Функции с таким номером не существует!!!" << endl;//елси пользователь ввел номер несуществующей функции
			break;

		}
	}
	system("pause");
	return 0;

}
void creat_file()//функция,которая создает файл(записываем в него данные)
{
	Bus*massiv = new Bus[5];//выделяем память под массив и заполняем его
	for (int i(0); i < 5; i++)
	{
		//записываем данные в массив
		cin.ignore(); cin.getline(massiv[i].FIO, 30);
		cin >> massiv[i].number_bus;
		cin >> massiv[i].way;
	}
	FILE *c_file = fopen("create_file.bin", "wb");//создаем бинарный файл и вносим данные массива
	fwrite(massiv, sizeof(Bus), 5, c_file);//вносим данные из массива в файл
	fclose(c_file);
}
List * func_added_bus(List *list_bus, char*FIO, int number, int way)//функция,добавляющая данные в список(в самый конец),если он пуст,то создает новый список и возвращает его
{
	List *bus_park = list_bus;
	if (bus_park == 0)
	{
		List*bus_park = new List; bus_park->bus = new Bus; bus_park->next = 0;
		bus_park->bus->number_bus = number;
		bus_park->bus->way = way;
		strcpy_s(bus_park->bus->FIO, FIO);//функция копирует строку,включая завершающий нулевой символ назначения,на которую ссылается указатель
		return bus_park;
	}
	else
	{
		while (bus_park->next != 0)
		{
			bus_park = bus_park->next;
		}
		bus_park->next = new List;
		bus_park->next->bus = new Bus;
		List *just_pointer = bus_park->next;
		just_pointer->next = 0;
		bus_park->next->bus->number_bus = number;
		bus_park->next->bus->way = way;
		strcpy_s(bus_park->next->bus->FIO, FIO);
		return list_bus;
	}
}
List *func_delete_bus(List *list_bus, int number)//функция,которая удаляет из списка элемент с определенным номером(если список пуст,то возвращает 0) 
{
	List *pointer = list_bus; List *delete_bus;
	if (list_bus == 0) return 0;
	if (list_bus->bus->number_bus == number)
	{
		list_bus = pointer->next;
		delete_bus = pointer;
	}
	else
	{
		while (pointer->next->bus->number_bus != number && pointer->next != 0)
		{
			pointer = pointer->next;
		}
		if (pointer->next == 0) return list_bus;
		delete_bus = pointer->next;
		pointer->next = delete_bus->next;
	}
	delete delete_bus;
	return list_bus;
}
List *func_search_bus(List *list_bus, int search_number)//функция,которая ведет поиск нужного номера в списке и возвращает указатель на него(если элемент не найден,то возвращает 0)
{
	List *pointer = list_bus;
	if (pointer == 0)	return 0;
	while (pointer->bus->number_bus != search_number && pointer->next != 0)
	{
		pointer = pointer->next;
	}
	if (pointer->bus->number_bus == search_number) return pointer;
	else return 0;
}
void func_result(List *list_bus)//функция,которая выводит данные списка на экран
{
	while (list_bus != 0)
	{
		cout << list_bus->bus->FIO << endl;
		cout << list_bus->bus->number_bus << endl;
		cout << list_bus->bus->way << endl;
		list_bus = list_bus->next;
	}
}
List*create_start_list(List*bus_park)//функция,которая заполняет список автобусов в парке из файла,который мы создали в другой функции 
{
	FILE *c_file = fopen("create_file.bin", "rb");
	Bus*new_massiv = new Bus[5];//выделяем память под массив и заполняем его
	fread(new_massiv, sizeof(Bus), 5, c_file);
	fclose(c_file);
	for (int i(0); i < 5; i++)
	{
		bus_park = func_added_bus(bus_park, new_massiv[i].FIO, new_massiv[i].number_bus, new_massiv[i].way);//вызываем функцию,котарая будет заполнять список автобусов в парке 
	}
	return bus_park;
}