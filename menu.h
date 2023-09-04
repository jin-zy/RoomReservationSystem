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

// 无参构造
Menu::Menu()
{

}

// 主菜单
void Menu::login_menu()
{
	cout << "+-----------------------------+" << endl;
	cout << "|****** 欢迎使用预约系统 *****|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|*******  1. 学生代表  *******|" << endl;
	cout << "|*******  2. 教    师  *******|" << endl;
	cout << "|*******  3. 管 理 员  *******|" << endl;
	cout << "|*******  0. 退    出  *******|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << endl;
	cout << "请输入您的身份：" << endl;
}

// 管理员子菜单
void Menu::manager_menu(Identity*& account)
{
	while (true) {
		// 显示菜单
		account->oper_menu();

		Manager* manager = (Manager*)account;
		int select = 0;
		cin >> select;

		switch (select) {
		case 1:	// 添加账号
			manager->add_account();
			break;
		case 2:	// 查看账号
			manager->show_account();
			break;
		case 3:	// 查看机房
			manager->show_rooms();
			break;
		case 4:	// 清空预约
			manager->empty_files();
			break;
		case 0:	// 注销登录
			delete account;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
		}
	}
}

// 学生子菜单
void Menu::student_menu(Identity*& account)
{
	while (true) {
		// 显示菜单
		account->oper_menu();

		Student* student = (Student*)account;
		int select = 0;
		cin >> select;

		switch (select) {
		case 1:	// 申请预约
			student->apply_order();
			break;
		case 2:	// 查看自己的预约
			student->show_my_order();
			break;
		case 3:	// 查看所有的预约
			student->show_all_order();
			break;
		case 4:	// 取消预约
			student->cancel_order();
			break;
		case 0:	// 注销登录
			delete account;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
		}
	}
}

// 教师子菜单
void Menu::teacher_menu(Identity*& account)
{
	while (true) {
		// 显示菜单
		account->oper_menu();

		Teacher* teacher = (Teacher*)account;
		int select = 0;
		cin >> select;

		switch (select) {
		case 1:	// 查看所有预约
			teacher->show_all_order();
			break;
		case 2:	// 审核预约
			teacher->valid_order();
			break;
		case 0:	// 注销登录
			delete account;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
		}
	}
}

// 登录函数
// file_name - 操作的文件
// type - 登录省份（1、学生 2、教师 3、管理员）
void Menu::login(string file_name, int type)
{
	Identity* account = NULL;	// 身份指针
	//string file_root = file_name.substr(file_name.find_first_of("/") + 1);
	// cout << file_root << endl;
	ifstream ifs;
	ifs.open(file_name, ios::in);

	// 文件不存在
	if (!ifs.is_open()) {
		cout << "信息文件不存在！" << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1) {
		// 学生登录
		cout << "请输入您的学号：" << endl;
		cin >> id;
	}
	else if (type == 2) {
		// 教师登录
		cout << "请输入您的教职工号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1) {
		// 学生登录验证 
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "学生验证登录成功！" << endl;
				// 登录成功，清空页面
				system("pause");
				system("cls");
				// 创建学生对象
				account = new Student(id, name, pwd);
				// 进入学生子菜单
				student_menu(account);
				return;
			}
		}
	}
	else if (type == 2) {
		// 教师登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "教师验证登录成功！" << endl;
				// 登录成功，清空页面
				system("pause");
				system("cls");
				// 创建教师对象
				account = new Teacher(id, name, pwd);
				// 进入教师子菜单
				teacher_menu(account);
				return;
			}
		}
	}
	else if (type == 3) {
		// 管理员登录验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "管理员验证登录成功！" << endl;
				// 登录成功，清空页面
				system("pause");
				system("cls");
				// 创建管理员对象
				account = new Manager(name, pwd);
				// 进入管理员子菜单
				manager_menu(account);
				return;
			}
		}
	}

	cout << "验证登录失败！！" << endl;

	system("pause");
 	system("cls");
	return;
}
