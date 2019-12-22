#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
struct Bus   //�������� ����������
{
	char FIO[30];
	int number_bus;
	int way;
};
struct List {
	Bus *bus;
	List *next;
};
//��������� �������
void creat_file();
List * func_added_bus(List *, char*, int, int );
List *func_delete_bus(List *, int );
List *func_search_bus(List *, int);
void func_result(List *);
List*create_start_list(List*);
int main()
{
	setlocale(LC_ALL, "Ru");
	List *bus_in_park = NULL; List *bus_in_way = NULL;//������� ��� ��������� � �������������� ��=NULL
	List *need_element;//������� ���������,������� ����� �������������� � ������� ������ ��������   
	cout << "---------------------------------------------------------------" << endl;
	cout << "��������� '���������� ����'" << endl;
	bus_in_park=create_start_list(bus_in_park);//�������� �������,������� ���������� �� ����� ������ � ������ ��������� � �����
	bool check = true;//����������,������� ��������� �������� �����(check=false,���� ������������ ������ ����� �� ���������) 
	int need_number_bus;//������� ����������(� ��� ����� ���������� ����� ��������,������� ����� ��������� � ���� ��� � ����)
	int choice_func;//������� ����������(������������ ����� ������� � ��� ������ ����� ������ ) 
	while (check)
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "1)����������� �������� � ����" << endl;
		cout << "2)����������� �������� � ���������� ����" << endl;
		cout << "3)����� ���������� �� ��������� � �����" << endl;
		cout << "4)����� ���������� �� ��������� � ����" << endl;
		cout << "5)����� �� ���������" << endl;
		while (true)
		{
			cout << "�������� �������:";
			cin >> choice_func;//������� ����������(������������ ����� ������� � ��� ������ ����� ������ )
			if (!cin)//�������� �� ���������� ���� int
			{
				cout << "������ ��� ����� �����!!!";
				cin.clear();//������� ���� ������ cin(��������� �������� ����� ����� �������� ���������) 
				cin.ignore(100, '\n');//�������� 100 �������� �� ������ � ���������������, ���� ��������� ����� ������(\n) ��� 100 ��������(100-������ ����� ��������,������� ������������,��� ������������ �� ����� ������� 100 ��������) )
				cout << endl;
			}
			else
				break;
		}
		switch (choice_func)
		{
		case 1:
			cout << "---------------------------------------------------------------" << endl;
			cout << "����������� �������� � ����" << endl;
			while (true)
			{
				cout << "---------------------------------------------------------------" << endl;
				cout << "������� ����� ��������:";
				cin >> need_number_bus;//������ ������ ����� ��������
				if (!cin)
				{
					cout << "������ ��� ����� �����!!!";
					cin.clear();
					cin.ignore(100,'\n');
					cout << endl;
				}
				else
					break;
			}
			need_element = func_search_bus(bus_in_park, need_number_bus);//�������� need_element �������� ������ �� �������� � ������� need_number_bus
			if (need_element == 0) cout << "�������� � ����� ������� �� ���������" << endl;//���� ������ ������ �� ���������� � ������ ��������� � �����
			else
			{
				bus_in_way = func_added_bus(bus_in_way, need_element->bus->FIO, need_element->bus->number_bus, need_element->bus->way);//��������� �������,������� ��������� � ������ ��������� � ���� ������ �� ��������� need_element
				bus_in_park = func_delete_bus(bus_in_park, need_number_bus);//�������� �������,������� ������� ������ �� �������� � ����� � ������� need_number 
			}
			break;
		case 2:
			cout << "---------------------------------------------------------------" << endl;
			cout << "����������� �������� � ���������� ����" << endl;
			while (true)
			{
				cout << "---------------------------------------------------------------" << endl;
				cout << "������� ����� ��������:";
				cin >> need_number_bus;
				if (!cin)
				{
					cout << "������ ��� ����� �����!!!";
					cin.clear();
					cin.ignore(100, '\n');
					cout << endl;
				}
				else
					break;
			}
			need_element = func_search_bus(bus_in_way, need_number_bus); // �������� need_element �������� ������ �� �������� � ������� need_number_bus
			if (need_element == 0)//���� ������ ������ �� ���������� � ������ ��������� � �����
			{
				cout << "�������� � ����� ������� �� ���������" << endl; 
			}
			else
			{
				bus_in_park = func_added_bus(bus_in_park, need_element->bus->FIO, need_element->bus->number_bus, need_element->bus->way);//��������� �������,������� ��������� � ������ ��������� � ����� ������ �� ��������� need_element
				bus_in_way = func_delete_bus(bus_in_way, need_number_bus);//�������� �������,������� ������� ������ �� �������� � ����� � ������� need_number
			}
			break;
		case 3:
			cout << "---------------------------------------------------------------" << endl;
			cout << "����� ���������� �� ��������� � ���������� �����" << endl;
			if (bus_in_park == 0)//���� ������ ����
			{
				cout << "������ ��������� ����" << endl;
			}
			else
				func_result(bus_in_park);//����� �������,������� ������� ������ �� �����
			break;
		case 4:
			cout << "---------------------------------------------------------------" << endl;
			cout << "����� ���������� �� ��������� � ����" << endl;
			if (bus_in_way == 0)//���� ������ ����
			{
				cout << "������ ��������� ����" << endl;
			}
			else
				func_result(bus_in_way);//����� �������,������� ������� ������ �� �����
			break;
		case 5:
			check = false;//��������,������ ������� �� ������ �����(�.� while(check))
			cout << "����� �� ���������" << endl;break;
		default:
			cout << "������� � ����� ������� �� ����������!!!" << endl;//���� ������������ ���� ����� �������������� �������
			break;

		}
	}
	system("pause");
	return 0;

}
void creat_file()//�������,������� ������� ����(���������� � ���� ������)
{
	Bus*massiv = new Bus[5];//�������� ������ ��� ������ � ��������� ���
	for (int i(0); i < 5; i++)
	{
		//���������� ������ � ������
		cin.ignore(); cin.getline(massiv[i].FIO, 30);
		cin >> massiv[i].number_bus;
		cin >> massiv[i].way;
	}
	FILE *c_file = fopen("create_file.bin", "wb");//������� �������� ���� � ������ ������ �������
	fwrite(massiv, sizeof(Bus), 5, c_file);//������ ������ �� ������� � ����
	fclose(c_file);
}
List * func_added_bus(List *list_bus, char*FIO, int number, int way)//�������,����������� ������ � ������(� ����� �����),���� �� ����,�� ������� ����� ������ � ���������� ���
{
	List *bus_park = list_bus;
	if (bus_park == 0)
	{
		List*bus_park = new List; bus_park->bus = new Bus; bus_park->next = 0;
		bus_park->bus->number_bus = number;
		bus_park->bus->way = way;
		strcpy_s(bus_park->bus->FIO, FIO);//������� �������� ������,������� ����������� ������� ������ ����������,�� ������� ��������� ���������
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
List *func_delete_bus(List *list_bus, int number)//�������,������� ������� �� ������ ������� � ������������ �������(���� ������ ����,�� ���������� 0) 
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
List *func_search_bus(List *list_bus, int search_number)//�������,������� ����� ����� ������� ������ � ������ � ���������� ��������� �� ����(���� ������� �� ������,�� ���������� 0)
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
void func_result(List *list_bus)//�������,������� ������� ������ ������ �� �����
{
	while (list_bus != 0)
	{
		cout << list_bus->bus->FIO << endl;
		cout << list_bus->bus->number_bus << endl;
		cout << list_bus->bus->way << endl;
		list_bus = list_bus->next;
	}
}
List*create_start_list(List*bus_park)//�������,������� ��������� ������ ��������� � ����� �� �����,������� �� ������� � ������ ������� 
{
	FILE *c_file = fopen("create_file.bin", "rb");
	Bus*new_massiv = new Bus[5];//�������� ������ ��� ������ � ��������� ���
	fread(new_massiv, sizeof(Bus), 5, c_file);
	fclose(c_file);
	for (int i(0); i < 5; i++)
	{
		bus_park = func_added_bus(bus_park, new_massiv[i].FIO, new_massiv[i].number_bus, new_massiv[i].way);//�������� �������,������� ����� ��������� ������ ��������� � ����� 
	}
	return bus_park;
}