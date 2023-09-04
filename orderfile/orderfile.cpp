#include "orderfile.h"

// �޲ι���
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;		// ʱ��
	string interval;	// ʱ��
	string stu_ID;		// ѧ��ѧ��
	string stu_name;	// ѧ������
	string room_ID;		// �������
	string status;		// ԤԼ״̬

	this->m_size = 0;	// ԤԼ��¼����

	while (ifs >> date && ifs >> interval && ifs >> stu_ID &&
		ifs >> stu_name && ifs >> room_ID && ifs >> status) {
		
		string key;
		string value;
		map<string, string> m;

		// ��ȡʱ��
		int pos = date.find(":");
		if (pos != -1) {
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// ��ȡʱ��
		pos = interval.find(":");
		if (pos != -1) {
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// ��ȡѧ��
		pos = stu_ID.find(":");
		if (pos != -1) {
			key = stu_ID.substr(0, pos);
			value = stu_ID.substr(pos + 1, stu_ID.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// ��ȡѧ������
		pos = stu_name.find(":");
		if (pos != -1) {
			key = stu_name.substr(0, pos);
			value = stu_name.substr(pos + 1, stu_name.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// ��ȡ������
		pos = room_ID.find(":");
		if (pos != -1) {
			key = room_ID.substr(0, pos);
			value = room_ID.substr(pos + 1, room_ID.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// ��ȡԤԼ״̬
		pos = status.find(":");
		if (pos != -1) {
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		this->m_order_data.insert(make_pair(this->m_size, m));
		this->m_size++;
	}

	ifs.close();
}

// ����ԤԼ��¼
void OrderFile::update_order()
{
	if (this->m_size == 0) {
		return;
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < m_size; i++) {
		ofs << "date:" << this->m_order_data[i]["date"] << " ";
		ofs << "interval:" << this->m_order_data[i]["interval"] << " ";
		ofs << "stu_ID:" << this->m_order_data[i]["stu_ID"] << " ";
		ofs << "stu_name:" << this->m_order_data[i]["stu_name"] << " ";
		ofs << "room_ID:" << this-> m_order_data[i]["room_ID"] << " ";
		ofs << "status:" << this->m_order_data[i]["status"] << " ";
	}

	ofs.close();
}