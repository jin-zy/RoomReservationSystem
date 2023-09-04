#include "student.h"

// Ĭ�Ϲ���
Student::Student()
{

}

// �вι���
Student::Student(int ID, string name, string pwd)
{
	this->m_stu_ID = ID;
	this->m_name = name;
	this->m_password = pwd;

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

	ifs.close();
}

// �����˵�
void Student::oper_menu()
{
	cout << "ѧ������" << this->m_name << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|****** ��ӭѧ�������¼ *****| " << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|*******  1. ����ԤԼ  *******|" << endl;
	cout << "|*******  2. �ҵ�ԤԼ  *******|" << endl;
	cout << "|*******  3. ����ԤԼ  *******|" << endl;
	cout << "|*******  4. ȡ��ԤԼ  *******|" << endl;
	cout << "|*******  0. ע����¼  *******|" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "���������Ĳ�����" << endl;
}

// �ύԤԼ
void Student::apply_order()
{
	int date = 0;
	int interval = 0;
	int room = 0;

	cout << "��������ʱ��Ϊ��һ������!" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1 - ��һ" << endl;
	cout << "2 - �ܶ�" << endl;
	cout << "3 - ����" << endl;
	cout << "4 - ����" << endl;
	cout << "5 - ����" << endl;

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) break;
		else cout << "�����������������룡" << endl;
	}

	cout << "����������ԤԼ��ʱ�Σ�" << endl;
	cout << "1 - ����" << endl;
	cout << "2 - ����" << endl;

	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) break;
		else cout << "�����������������룡" << endl;
	}

	cout << "����������ԤԼ�Ļ�����" << endl;
	cout << "1 - 1�Ż�����������" << v_rooms[0].m_capcity<< endl;
	cout << "2 - 2�Ż�����������" << v_rooms[1].m_capcity << endl;
	cout << "3 - 3�Ż�����������" << v_rooms[2].m_capcity << endl;

	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) break;
		else cout << "�����������������룡" << endl;
	}

	cout << "ԤԼ�ɹ��������..." << endl;

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

// �鿴�Լ���ԤԼ
void Student::show_my_order()
{
	OrderFile of;
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		if (atoi(of.m_order_data[i]["stu_ID"].c_str()) == this->m_stu_ID) {
			cout << "ԤԼ���ڣ���" << of.m_order_data[i]["date"];
			cout << "\tʱ��Σ�" << (of.m_order_data[i]["interval"] == "1" ? "����" : "����");
			cout << "\t�����ţ�" << of.m_order_data[i]["room_ID"];
			string status = " ״̬��";
			if (of.m_order_data[i]["status"] == "1") status += "�����";
			else if (of.m_order_data[i]["status"] == "2") status += "ԤԼ�ɹ�";
			else if (of.m_order_data[i]["status"] == "-1") status += "ԤԼʧ�ܣ����δͨ��";
			else if (of.m_order_data[i]["status"] == "0") status += "ԤԼ��ȡ��";
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

// �鿴���е�ԤԼ
void Student::show_all_order()
{
	OrderFile of;
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		cout << i + 1 << "��";

		cout << "ԤԼ���ڣ���" << of.m_order_data[i]["date"];
		cout << "\tʱ��Σ�" << (of.m_order_data[i]["interval"] == "1" ? "����" : "����");
		cout << "\tѧ�ţ�" << of.m_order_data[i]["stu_ID"];
		cout << "\t������" << of.m_order_data[i]["stu_name"];
		cout << "\t�����ţ�" << of.m_order_data[i]["room_ID"];
		string status = " ״̬��";
		if (of.m_order_data[i]["status"] == "1") status += "�����";
		else if (of.m_order_data[i]["status"] == "2") status += "ԤԼ�ɹ�";
		else if (of.m_order_data[i]["status"] == "-1") status += "ԤԼʧ�ܣ����δͨ��";
		else if (of.m_order_data[i]["status"] == "0") status += "ԤԼ��ȡ��";
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

// ȡ��ԤԼ
void Student::cancel_order()
{
	OrderFile of;
	if (of.m_size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����ԤԼ��¼���£�" << endl;

	vector<int> vec;
	int index = 1;
	for (int i = 0; i < of.m_size; i++) {
		if (atoi(of.m_order_data[i]["stu_ID"].c_str()) == this->m_stu_ID) {
			if (of.m_order_data[i]["status"] == "1" || of.m_order_data[i]["status"] == "2") {
				vec.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_order_data[i]["date"];
				cout << "\tʱ��Σ�" << (of.m_order_data[i]["interval"] == "1" ? "����" : "����");
				cout << "\t�����ţ�" << of.m_order_data[i]["room_ID"];
				string status = " ״̬��";
				if (of.m_order_data[i]["status"] == "1") status += "�����";
				else if (of.m_order_data[i]["status"] == "2") status += "ԤԼ�ɹ�";
				else if (of.m_order_data[i]["status"] == "-1") status += "ԤԼʧ�ܣ����δͨ��";
				else if (of.m_order_data[i]["status"] == "0") status += "ԤԼ��ȡ��";
				cout << status << endl;
			}
		}
	}

	cout << "������Ҫȡ���ļ�¼������0���أ�" << endl;
	int select = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= vec.size()) {
			if (select == 0) break;
			else {
				of.m_order_data[vec[select - 1]]["status"] = "0";
				of.update_order();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "�����������������룡" << endl;
	}

	system("pause");
	system("cls");
}