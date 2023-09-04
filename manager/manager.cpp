#include "manager.h"

// 默认构造
Manager::Manager()
{

}

// 有参构造
Manager::Manager(string name, string pwd)
{
	this->m_name = name;
	this->m_password = pwd;

	// 初始化容器
	this->init_vector();

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
	cout << "当前机房数量为：" << v_rooms.size() << endl;

	ifs.close();
}

// 操作菜单
void Manager::oper_menu()
{
	cout << "管理员：" << this->m_name << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|******* 欢迎管理员登录 ******| " << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|*******  1. 添加账号  *******|" << endl;
	cout << "|*******  2. 查看账号  *******|" << endl;
	cout << "|*******  3. 查看机房  *******|" << endl;
	cout << "|*******  4. 清空预约  *******|" << endl;
	cout << "|*******  0. 注销登录  *******|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "请输入您的操作：" << endl;
}

// 添加账号
void Manager::add_account()
{
	cout << "请输入要添加的账号类型：" << endl;
	cout << "1 - 学生代表" << endl;
	cout << "2 - 教    师" << endl;

	string fileName;
	string tip;
	ofstream ofs;

	int select = 0;
	cin >> select;

	string errTip;	// 错误提示，添加重复账号
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errTip = "学号重复，请重新输入！";
	}
	else if (select == 2) {
		fileName = TEACHER_FILE;
		tip = "请输入教职工号：";
		errTip = "教职工号重复，请重新输入！";
	}
	else {
		cout << "输入有误！" << endl;
	}

	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;

	while (true) {
		cin >> id;

		bool ret = this->check_repeat(id, select);

		if (ret) {	// 有重复
			cout << errTip << endl;
		}
		else {
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入登录密码：" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功！" << endl;

	system("pause");
	system("cls");

	ofs.close();
	// 初始化容器
	this->init_vector();
}

// 查看账号
void print_student(Student& stu)
{
	cout << "学号：" << stu.m_stu_ID << "\t姓名：" << stu.m_name
		<< "\t密码：" << stu.m_password << endl;
}

void print_teacher(Teacher& teac)
{
	cout << "职工号：" << teac.m_emp_ID << "\t姓名：" << teac.m_name
		<< "\t密码：" << teac.m_password << endl;
}

void Manager::show_account()
{
	cout << "请选择查看的内容：" << endl;
	cout << "1 - 查看学生账号" << endl;
	cout << "2 - 查看教师账号" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		if (v_stu.size() == 0) {
			cout << "当前没有学生账号" << endl;
		}
		else {
			cout << "所有学生账号信息如下：" << endl;
			for_each(v_stu.begin(), v_stu.end(), print_student);
		}
	}
	else if (select == 2) {
		if (v_teac.size() == 0) {
			cout << "当前没有教师账号" << endl;
		}
		else {
			cout << "所有教师账号信息如下：" << endl;
			for_each(v_teac.begin(), v_teac.end(), print_teacher);
		}
	}
	system("pause");
	system("cls");
}

// 查看机房信息
void Manager::show_rooms()
{
	cout << "机房信息如下：" << endl;
	for (vector<Rooms>::iterator it = v_rooms.begin(); it != v_rooms.end(); it++) {
		cout << "房间号：" << it->m_room_ID << "\t容量：" << it->m_capcity << endl;
	}
	system("pause");
	system("cls");
}

// 清空预约记录
void Manager::empty_files()
{
	cout << "是否确认清空？" << endl;
	cout << "1 - 确认" << endl;
	cout << "2 - 返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

// 初始化容器
void Manager::init_vector()
{
	// 读取学生文件中的信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "学生文件读取失败！" << endl;
		return;
	}

	v_stu.clear();
	// v_teac.clear();

	Student stu;
	while (ifs >> stu.m_stu_ID && ifs >> stu.m_name && ifs >> stu.m_password) {
		v_stu.push_back(stu);
	}

	cout << "当前学生数量为：" << v_stu.size() << endl;
	ifs.close();

	// 读取教师文件中的信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "教师文件读取失败！" << endl;
		return;
	}

	Teacher teac;
	while (ifs >> teac.m_emp_ID && ifs >> teac.m_name && ifs >> teac.m_password) {
		v_teac.push_back(teac);
	}

	cout << "当前教师数量为：" << v_teac.size() << endl;
	ifs.close();
}

// 检测重复注册
bool Manager::check_repeat(int id, int type)
{
	if (type == 1) {
		for (vector<Student>::iterator it = v_stu.begin(); it != v_stu.end(); it++) {
			if (id == it->m_stu_ID) {
				return true;
			}
		}
	}
	else if (type == 2) {
		for (vector<Teacher>::iterator it = v_teac.begin(); it != v_teac.end(); it++) {
			if (id == it->m_emp_ID) {
				return true;
			}
		}
	}
	return false;
}