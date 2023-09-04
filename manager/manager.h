#pragma once

#include "../student/student.h"
#include "../teacher/teacher.h"

class Manager : public Identity {
public:
	//	�޲ι���
	Manager();
	// �вι���
	Manager(string name, string pwd);

public:
	virtual void oper_menu();	// �����˵�
	void add_account();			// ����˺�
	void show_account();		// �鿴�˺�
	void show_rooms();			// �鿴������Ϣ
	void empty_files();			// ���ԤԼ��¼
	void init_vector();			// ��ʼ������
	bool check_repeat(int id, int type);	// ����ظ�ע��

private:
	vector<Student> v_stu;	// ѧ������
	vector<Teacher> v_teac;	// ��ʦ����
	vector<Rooms> v_rooms;	// ��������
};
