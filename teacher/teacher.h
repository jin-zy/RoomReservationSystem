#pragma once
#include "../identity.h"

class Teacher : public Identity {
public:
	// �޲ι���
	Teacher();
	// �вι���
	Teacher(int empId, string name, string pwd);
public:
	virtual void oper_menu();	// �����˵�
	void show_all_order();		// �鿴����ԤԼ
	void valid_order();			// ���ԤԼ

public:
	int m_emp_ID;	// ��ʦ���
};