#pragma once
#include "../identity.h"

using namespace std;

/* ѧ���� */
class Student : public Identity {
public:
	// Ĭ�Ϲ���
	Student();
	// �вι���
	Student(int ID, string name, string pwd);

public:
	virtual void oper_menu();	// �����˵�
	void apply_order();			// �ύԤԼ
	void show_my_order();			// �鿴�Լ���ԤԼ
	void show_all_order();		// �鿴���е�ԤԼ
	void cancel_order();		// ȡ��ԤԼ

public:
	int m_stu_ID;				// ѧ��ѧ��
	vector<Rooms> v_rooms;		// ��������
};
