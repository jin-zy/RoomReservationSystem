#include "manager.h"

// Ĭ�Ϲ���
Manager::Manager()
{

}

// �вι���
Manager::Manager(string name, string pwd)
{
	this->m_name = name;
	this->m_password = pwd;

	// ��ʼ������
	this->init_vector();

	// ��ȡ������Ϣ
	ifstream ifs;
	ifs.open(ROOMS_FILE, ios::in);

	// �ļ���Ϣ������
	if (!ifs.is_open()) {
		cout << "������Ϣ�ļ������ڣ�" << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	Rooms room;
	while (ifs >> room.m_room_ID && ifs >> room.m_capcity) {
		v_rooms.push_back(room);
	}
	cout << "��ǰ��������Ϊ��" << v_rooms.size() << endl;

	ifs.close();
}

// �����˵�
void Manager::oper_menu()
{
	cout << "����Ա��" << this->m_name << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|******* ��ӭ����Ա��¼ ******| " << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|*******  1. ����˺�  *******|" << endl;
	cout << "|*******  2. �鿴�˺�  *******|" << endl;
	cout << "|*******  3. �鿴����  *******|" << endl;
	cout << "|*******  4. ���ԤԼ  *******|" << endl;
	cout << "|*******  0. ע����¼  *******|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "���������Ĳ�����" << endl;
}

// ����˺�
void Manager::add_account()
{
	cout << "������Ҫ��ӵ��˺����ͣ�" << endl;
	cout << "1 - ѧ������" << endl;
	cout << "2 - ��    ʦ" << endl;

	string fileName;
	string tip;
	ofstream ofs;

	int select = 0;
	cin >> select;

	string errTip;	// ������ʾ������ظ��˺�
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errTip = "ѧ���ظ������������룡";
	}
	else if (select == 2) {
		fileName = TEACHER_FILE;
		tip = "�������ְ���ţ�";
		errTip = "��ְ�����ظ������������룡";
	}
	else {
		cout << "��������" << endl;
	}

	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;

	while (true) {
		cin >> id;

		bool ret = this->check_repeat(id, select);

		if (ret) {	// ���ظ�
			cout << errTip << endl;
		}
		else {
			break;
		}
	}

	cout << "������������" << endl;
	cin >> name;

	cout << "�������¼���룺" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ���" << endl;

	system("pause");
	system("cls");

	ofs.close();
	// ��ʼ������
	this->init_vector();
}

// �鿴�˺�
void print_student(Student& stu)
{
	cout << "ѧ�ţ�" << stu.m_stu_ID << "\t������" << stu.m_name
		<< "\t���룺" << stu.m_password << endl;
}

void print_teacher(Teacher& teac)
{
	cout << "ְ���ţ�" << teac.m_emp_ID << "\t������" << teac.m_name
		<< "\t���룺" << teac.m_password << endl;
}

void Manager::show_account()
{
	cout << "��ѡ��鿴�����ݣ�" << endl;
	cout << "1 - �鿴ѧ���˺�" << endl;
	cout << "2 - �鿴��ʦ�˺�" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		if (v_stu.size() == 0) {
			cout << "��ǰû��ѧ���˺�" << endl;
		}
		else {
			cout << "����ѧ���˺���Ϣ���£�" << endl;
			for_each(v_stu.begin(), v_stu.end(), print_student);
		}
	}
	else if (select == 2) {
		if (v_teac.size() == 0) {
			cout << "��ǰû�н�ʦ�˺�" << endl;
		}
		else {
			cout << "���н�ʦ�˺���Ϣ���£�" << endl;
			for_each(v_teac.begin(), v_teac.end(), print_teacher);
		}
	}
	system("pause");
	system("cls");
}

// �鿴������Ϣ
void Manager::show_rooms()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<Rooms>::iterator it = v_rooms.begin(); it != v_rooms.end(); it++) {
		cout << "����ţ�" << it->m_room_ID << "\t������" << it->m_capcity << endl;
	}
	system("pause");
	system("cls");
}

// ���ԤԼ��¼
void Manager::empty_files()
{
	cout << "�Ƿ�ȷ����գ�" << endl;
	cout << "1 - ȷ��" << endl;
	cout << "2 - ����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}

// ��ʼ������
void Manager::init_vector()
{
	// ��ȡѧ���ļ��е���Ϣ
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "ѧ���ļ���ȡʧ�ܣ�" << endl;
		return;
	}

	v_stu.clear();
	// v_teac.clear();

	Student stu;
	while (ifs >> stu.m_stu_ID && ifs >> stu.m_name && ifs >> stu.m_password) {
		v_stu.push_back(stu);
	}

	cout << "��ǰѧ������Ϊ��" << v_stu.size() << endl;
	ifs.close();

	// ��ȡ��ʦ�ļ��е���Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "��ʦ�ļ���ȡʧ�ܣ�" << endl;
		return;
	}

	Teacher teac;
	while (ifs >> teac.m_emp_ID && ifs >> teac.m_name && ifs >> teac.m_password) {
		v_teac.push_back(teac);
	}

	cout << "��ǰ��ʦ����Ϊ��" << v_teac.size() << endl;
	ifs.close();
}

// ����ظ�ע��
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