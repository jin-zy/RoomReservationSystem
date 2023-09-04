#include "teacher.h"

// 无参构造
Teacher::Teacher()
{

}

// 有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_emp_ID = empId;
	this->m_name = name;
	this->m_password == pwd;
}

// 操作菜单
void Teacher::oper_menu()
{
	cout << "教师：" << this->m_name << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|******** 欢迎教师登录 *******| " << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|*******  1. 查看预约  *******|" << endl;
	cout << "|*******  2. 审核预约  *******|" << endl;
	cout << "|*******  0. 注销登录  *******|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "请输入您的操作：" << endl;
}

// 查看所有预约
void Teacher::show_all_order()
{
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		cout << i + 1 << "、";

		cout << "预约日期：周" << of.m_order_data[i]["date"];
		cout << "\t时间段：" << (of.m_order_data[i]["interval"] == "1" ? "上午" : "下午");
		cout << "\t学号：" << of.m_order_data[i]["stu_ID"];
		cout << "\t姓名：" << of.m_order_data[i]["stu_name"];
		cout << "\t机房号：" << of.m_order_data[i]["room_ID"];
		string status = " 状态：";
		if (of.m_order_data[i]["status"] == "1") status += "审核中";
		else if (of.m_order_data[i]["status"] == "2") status += "预约成功";
		else if (of.m_order_data[i]["status"] == "-1") status += "预约失败，审核未通过";
		else if (of.m_order_data[i]["status"] == "0") status += "预约已取消";
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

// 审核预约
void Teacher::valid_order()
{
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "待审核的预约记录如下：" << endl;

	vector<int> vec;
	int index = 0;
	for (int i = 0; i < of.m_size; i++) {
		if (of.m_order_data[i]["status"] == "1") {
			vec.push_back(i);
			cout << ++index << "、";
			cout << "预约日期：周" << of.m_order_data[i]["date"];
			cout << "\t时间段：" << (of.m_order_data[i]["interval"] == "1" ? "上午" : "下午");
			cout << "\t学号：" << of.m_order_data[i]["stu_ID"];
			cout << "\t姓名：" << of.m_order_data[i]["stu_name"];
			cout << "\t机房号：" << of.m_order_data[i]["room_ID"];
			string status = " 状态：审核中";
			cout << status << endl;
		}
	}

	cout << "请输入要审核的记录，输入0返回：" << endl;
	int select = 0;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= vec.size()) {
			if (select == 0) break;
			else {
				cout << "请输入审核结果：" << endl;
				cout << "1 - 通过" << endl;
				cout << "2 - 不通过" << endl;
				cin >> ret;

				if (ret == 1) {
					of.m_order_data[vec[select - 1]]["status"] = "2";
				}
				else {
					of.m_order_data[vec[select - 1]]["status"] = "-1";
				}

				of.update_order();

				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}