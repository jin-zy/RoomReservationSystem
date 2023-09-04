#pragma once
#include "../identity.h"

class Teacher : public Identity {
public:
	// 无参构造
	Teacher();
	// 有参构造
	Teacher(int empId, string name, string pwd);
public:
	virtual void oper_menu();	// 操作菜单
	void show_all_order();		// 查看所有预约
	void valid_order();			// 审核预约

public:
	int m_emp_ID;	// 教师编号
};