#include <iostream>
#include <fstream>
#include <string>

#include "menu.h"

using namespace std;

int main()
{
	Menu menu;

	int select = 0;
	while (true) {
		// ��ʾ���˵�
		menu.login_menu();

		cin >> select;
		switch (select) {
		case 1:	// ѧ�����
			menu.login(STUDENT_FILE, 1);
			break;
		case 2:	// ��ʦ���
			menu.login(TEACHER_FILE, 2);
			break;
		case 3:	// ����Ա���
			menu.login(ADMIN_FILE, 3);
			break;
		case 0:	// �˳�ϵͳ
			cout << "��ӭ�´�ʹ��!" << endl;
			system("pause");
			return 0;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}