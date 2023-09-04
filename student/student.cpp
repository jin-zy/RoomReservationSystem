#include "student.h"

// 默认构造
Student::Student()
{

}

// 有参构造
Student::Student(int ID, string name, string pwd)
{
	this->m_stu_ID = ID;
	this->m_name = name;
	this->m_password = pwd;

	// 获取机房信息
	ifstream ifs;
	ifs.open(ROOMS_FILE, ios::in);
	
	// 文件信息不存在
	if (!ifs.is_open()) {
		cout << "机房信息文件不存在！" << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	Rooms room;
	while (ifs >> room.m_room_ID && ifs >> room.m_capcity) {
		v_rooms.push_back(room);
	}

	ifs.close();
}

// 操作菜单
void Student::oper_menu()
{
	cout << "学生代表：" << this->m_name << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|****** 欢迎学生代表登录 *****| " << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|*******  1. 申请预约  *******|" << endl;
	cout << "|*******  2. 我的预约  *******|" << endl;
	cout << "|*******  3. 所有预约  *******|" << endl;
	cout << "|*******  4. 取消预约  *******|" << endl;
	cout << "|*******  0. 注销登录  *******|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "请输入您的操作：" << endl;
}

// 提交预约
void Student::apply_order()
{
	int date = 0;
	int interval = 0;
	int room = 0;

	cout << "机房开放时间为周一至周五!" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1 - 周一" << endl;
	cout << "2 - 周二" << endl;
	cout << "3 - 周三" << endl;
	cout << "4 - 周四" << endl;
	cout << "5 - 周五" << endl;

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) break;
		else cout << "输入有误请重新输入！" << endl;
	}

	cout << "请输入申请预约的时段：" << endl;
	cout << "1 - 上午" << endl;
	cout << "2 - 下午" << endl;

	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) break;
		else cout << "输入有误请重新输入！" << endl;
	}

	cout << "请输入申请预约的机房：" << endl;
	cout << "1 - 1号机房，容量：" << v_rooms[0].m_capcity<< endl;
	cout << "2 - 2号机房，容量：" << v_rooms[1].m_capcity << endl;
	cout << "3 - 3号机房，容量：" << v_rooms[2].m_capcity << endl;

	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) break;
		else cout << "输入有误请重新输入！" << endl;
	}

	cout << "预约成功，审核中..." << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stu_ID:" << this->m_stu_ID << " ";
	ofs << "stu_name:" << this->m_name << " ";
	ofs << "room_ID:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");
}

// 查看自己的预约
void Student::show_my_order()
{
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		if (atoi(of.m_order_data[i]["stu_ID"].c_str()) == this->m_stu_ID) {
			cout << "预约日期：周" << of.m_order_data[i]["date"];
			cout << "\t时间段：" << (of.m_order_data[i]["interval"] == "1" ? "上午" : "下午");
			cout << "\t机房号：" << of.m_order_data[i]["room_ID"];
			string status = " 状态：";
			if (of.m_order_data[i]["status"] == "1") status += "审核中";
			else if (of.m_order_data[i]["status"] == "2") status += "预约成功";
			else if (of.m_order_data[i]["status"] == "-1") status += "预约失败，审核未通过";
			else if (of.m_order_data[i]["status"] == "0") status += "预约已取消";
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

// 查看所有的预约
void Student::show_all_order()
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

// 取消预约
void Student::cancel_order()
{
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "您的预约记录如下：" << endl;

	vector<int> vec;
	int index = 1;
	for (int i = 0; i < of.m_size; i++) {
		if (atoi(of.m_order_data[i]["stu_ID"].c_str()) == this->m_stu_ID) {
			if (of.m_order_data[i]["status"] == "1" || of.m_order_data[i]["status"] == "2") {
				vec.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_order_data[i]["date"];
				cout << "\t时间段：" << (of.m_order_data[i]["interval"] == "1" ? "上午" : "下午");
				cout << "\t机房号：" << of.m_order_data[i]["room_ID"];
				string status = " 状态：";
				if (of.m_order_data[i]["status"] == "1") status += "审核中";
				else if (of.m_order_data[i]["status"] == "2") status += "预约成功";
				else if (of.m_order_data[i]["status"] == "-1") status += "预约失败，审核未通过";
				else if (of.m_order_data[i]["status"] == "0") status += "预约已取消";
				cout << status << endl;
			}
		}
	}

	cout << "请输入要取消的记录，输入0返回：" << endl;
	int select = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= vec.size()) {
			if (select == 0) break;
			else {
				of.m_order_data[vec[select - 1]]["status"] = "0";
				of.update_order();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	system("pause");
	system("cls");
}