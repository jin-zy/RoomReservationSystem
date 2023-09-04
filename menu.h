#pragma once
#include <iostream>
#include "student/student.h"
#include "manager/manager.h"
#include "teacher/teacher.h"

using namespace std;

class Menu {
public:
	Menu();
public:
	void login_menu();
	void login(string file_name, int type);
	void manager_menu(Identity *&account);
	void student_menu(Identity *&account);
	void teacher_menu(Identity*& account);
};

// �޲ι���
Menu::Menu()
{

}

// ���˵�
void Menu::login_menu()
{
	cout << "+-----------------------------+" << endl;
	cout << "|****** ��ӭʹ��ԤԼϵͳ *****|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|*******  1. ѧ������  *******|" << endl;
	cout << "|*******  2. ��    ʦ  *******|" << endl;
	cout << "|*******  3. �� �� Ա  *******|" << endl;
	cout << "|*******  0. ��    ��  *******|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << endl;
	cout << "������������ݣ�" << endl;
}

// ����Ա�Ӳ˵�
void Menu::manager_menu(Identity*& account)
{
	while (true) {
		// ��ʾ�˵�
		account->oper_menu();

		Manager* manager = (Manager*)account;
		int select = 0;
		cin >> select;

		switch (select) {
		case 1:	// ����˺�
			manager->add_account();
			break;
		case 2:	// �鿴�˺�
			manager->show_account();
			break;
		case 3:	// �鿴����
			manager->show_rooms();
			break;
		case 4:	// ���ԤԼ
			manager->empty_files();
			break;
		case 0:	// ע����¼
			delete account;
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
		}
	}
}

// ѧ���Ӳ˵�
void Menu::student_menu(Identity*& account)
{
	while (true) {
		// ��ʾ�˵�
		account->oper_menu();

		Student* student = (Student*)account;
		int select = 0;
		cin >> select;

		switch (select) {
		case 1:	// ����ԤԼ
			student->apply_order();
			break;
		case 2:	// �鿴�Լ���ԤԼ
			student->show_my_order();
			break;
		case 3:	// �鿴���е�ԤԼ
			student->show_all_order();
			break;
		case 4:	// ȡ��ԤԼ
			student->cancel_order();
			break;
		case 0:	// ע����¼
			delete account;
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
		}
	}
}

// ��ʦ�Ӳ˵�
void Menu::teacher_menu(Identity*& account)
{
	while (true) {
		// ��ʾ�˵�
		account->oper_menu();

		Teacher* teacher = (Teacher*)account;
		int select = 0;
		cin >> select;

		switch (select) {
		case 1:	// �鿴����ԤԼ
			teacher->show_all_order();
			break;
		case 2:	// ���ԤԼ
			teacher->valid_order();
			break;
		case 0:	// ע����¼
			delete account;
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
		}
	}
}

// ��¼����
// file_name - �������ļ�
// type - ��¼ʡ�ݣ�1��ѧ�� 2����ʦ 3������Ա��
void Menu::login(string file_name, int type)
{
	Identity* account = NULL;	// ���ָ��
	//string file_root = file_name.substr(file_name.find_first_of("/") + 1);
	// cout << file_root << endl;
	ifstream ifs;
	ifs.open(file_name, ios::in);

	// �ļ�������
	if (!ifs.is_open()) {
		cout << "��Ϣ�ļ������ڣ�" << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1) {
		// ѧ����¼
		cout << "����������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2) {
		// ��ʦ��¼
		cout << "���������Ľ�ְ���ţ�" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1) {
		// ѧ����¼��֤ 
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "ѧ����֤��¼�ɹ���" << endl;
				// ��¼�ɹ������ҳ��
				system("pause");
				system("cls");
				// ����ѧ������
				account = new Student(id, name, pwd);
				// ����ѧ���Ӳ˵�
				student_menu(account);
				return;
			}
		}
	}
	else if (type == 2) {
		// ��ʦ��¼��֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				// ��¼�ɹ������ҳ��
				system("pause");
				system("cls");
				// ������ʦ����
				account = new Teacher(id, name, pwd);
				// �����ʦ�Ӳ˵�
				teacher_menu(account);
				return;
			}
		}
	}
	else if (type == 3) {
		// ����Ա��¼��֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "����Ա��֤��¼�ɹ���" << endl;
				// ��¼�ɹ������ҳ��
				system("pause");
				system("cls");
				// ��������Ա����
				account = new Manager(name, pwd);
				// �������Ա�Ӳ˵�
				manager_menu(account);
				return;
			}
		}
	}

	cout << "��֤��¼ʧ�ܣ���" << endl;

	system("pause");
 	system("cls");
	return;
}
