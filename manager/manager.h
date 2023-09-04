#pragma once

#include "../student/student.h"
#include "../teacher/teacher.h"

class Manager : public Identity {
public:
	//	无参构造
	Manager();
	// 有参构造
	Manager(string name, string pwd);

public:
	virtual void oper_menu();	// 操作菜单
	void add_account();			// 添加账号
	void show_account();		// 查看账号
	void show_rooms();			// 查看机房信息
	void empty_files();			// 清空预约记录
	void init_vector();			// 初始化容器
	bool check_repeat(int id, int type);	// 检测重复注册

private:
	vector<Student> v_stu;	// 学生容器
	vector<Teacher> v_teac;	// 教师容器
	vector<Rooms> v_rooms;	// 机房容器
};
