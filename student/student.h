#pragma once
#include "../identity.h"

using namespace std;

/* 学生类 */
class Student : public Identity {
public:
	// 默认构造
	Student();
	// 有参构造
	Student(int ID, string name, string pwd);

public:
	virtual void oper_menu();	// 操作菜单
	void apply_order();			// 提交预约
	void show_my_order();			// 查看自己的预约
	void show_all_order();		// 查看所有的预约
	void cancel_order();		// 取消预约

public:
	int m_stu_ID;				// 学生学号
	vector<Rooms> v_rooms;		// 机房容器
};
