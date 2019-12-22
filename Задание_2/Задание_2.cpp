#include <iostream>
using namespace std;
//�������� ���������
struct Info {
	int year;
	char name[20];
};
struct Tree {
	Info *info;
	Tree *left;
	Tree *right;
};
//��������� �������
Tree *func_create_element();
Tree *func_add_element(Tree*, Tree *);
bool func_search(Tree*, int);
void func_result(Tree*, int);
int main()
{
	setlocale(LC_ALL, "Ru");
	Tree *head_tree = NULL; Tree *new_element = NULL;
	bool check = true;//����������,������� ��������� �������� �����(check=false,���� ������������ ������ ����� �� ���������) 
	int number;
	while (check)
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "������ �������:"<<endl;
		cout << "1)���������� �������� � ������" << endl;
		cout << "2)����� ���������� � �������� �� ������" << endl;
		cout << "3)����� �� ���������" << endl;
		while (true)
		{
			cout << "�������� �������:"; cin >> number;
			if (!cin)//�������� �� ���������� ���� int
			{
				cout << "������ ��� ����� �����!!!";
				cin.clear();//������� ���� ������ cin(��������� �������� ����� ����� �������� ���������) 
				cin.ignore(100, '\n');//�������� 100 �������� �� ������ � ���������������, ���� ��������� ����� ������(\n) ��� 100 ��������(100-������ ����� ��������,������� ������������,��� ������������ �� ����� ������� 100 ��������)
				cout << endl;
			}
			else
				break;
		}
		switch (number)
		{
		case 1:
			new_element=func_create_element();//����� �������,������� ������� ����� ������� 
			if (func_search(head_tree, new_element->info->year) == false)//�������� �� ������� ���������� ��������� � ������
				head_tree = func_add_element(head_tree, new_element);//����� �������,������� ��������� ����� ������� � ������
			else
				cout << "������ � ����� ����� ��� ����������!!!" << endl;
			break;
		case 2:
			int needed_number;
			while (true)
			{
				cout << "������� ��� ������� ��� ��������:"; cin >> needed_number;
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
			if (func_search(head_tree, needed_number) == true)
			{
				func_result(head_tree, needed_number);//����� �������,������� ����� ������� � ������ ��� ������������ �����  
			}
			else
				cout << "������ � ����� ����� �� ����������" << endl;
			break;
		case 3:
			check = false;//��������,������ ������� �� ������ �����(�.� while(check))
			cout << "����� �� ���������" << endl; break;
		default:
			cout << "������� � ����� ������� �� ����������!!!" << endl;
			break;
		}
	}
	system("pause");
	return 0;

}
Tree *func_create_element()//�������,��������� ����� ������� ������ ������
{
	Tree *add_element= new Tree; add_element->info = new Info;
	add_element->left = 0; add_element->right = 0;
	while (true)
	{
		cout << "������� ���:";
		cin >> add_element->info->year;
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
	cout << "������� ���:";
	cin.ignore(); cin.getline(add_element->info->name, 20);
	return add_element;
}
Tree *func_add_element(Tree*pointer, Tree *add_element)//�������,������� ��������� ����� ������� � ���� ������(� ����������� �� ����)
{
	Tree *begin_pointer = pointer;
	if (pointer == NULL) { return add_element; }//���� ������ ������ ����
	else
	{
		while (true)
		{
			if (add_element->info->year < begin_pointer->info->year && begin_pointer->left == 0)//���� ����� ������� ������=0 � ��� ������������ ������� ������ ���� ������ ������ ������ 
			{
				begin_pointer->left = add_element; break;//������ ������� ����������� �������� ������������ �������� 
			}
			if (add_element->info->year > begin_pointer->info->year && begin_pointer->right == 0)//���� ������ ������� ������=0 � ��� ������������ ������� ������ ���� ������ ������ ������ 
			{
				begin_pointer->right = add_element; break;//������� ������� ����������� �������� ������������ ��������
			}
			else//���� ������� ��� ��������� ��� ��� ������������ ������ ��� ������ ���� �������
			{
				if (add_element->info->year < begin_pointer->info->year)//���� ��� ������������ �������� ������ ���� ������ ������,�� ��������� � ������ ������� 
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
void func_result(Tree* pointer, int needed_number)//�������,������� ������� ������������ ������� ������ � ����� needed_number 
{
	while (true)
	{
		if (needed_number == pointer->info->year)
		{
			cout << "���:" << pointer->info->year << endl;
			cout << "���:" << pointer->info->name << endl;
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
bool func_search(Tree* pointer, int needed_number)//�������,������� ���������� true,���� ������� ������ � false,���� ������� �� ������
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