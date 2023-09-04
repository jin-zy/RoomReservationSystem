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
		// 显示主菜单
		menu.login_menu();

		cin >> select;
		switch (select) {
		case 1:	// 学生身份
			menu.login(STUDENT_FILE, 1);
			break;
		case 2:	// 教师身份
			menu.login(TEACHER_FILE, 2);
			break;
		case 3:	// 管理员身份
			menu.login(ADMIN_FILE, 3);
			break;
		case 0:	// 退出系统
			cout << "欢迎下次使用!" << endl;
			system("pause");
			return 0;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}