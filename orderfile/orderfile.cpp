#include "orderfile.h"

// 无参构造
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;		// 时间
	string interval;	// 时段
	string stu_ID;		// 学生学号
	string stu_name;	// 学生姓名
	string room_ID;		// 机房编号
	string status;		// 预约状态

	this->m_size = 0;	// 预约记录个数

	while (ifs >> date && ifs >> interval && ifs >> stu_ID &&
		ifs >> stu_name && ifs >> room_ID && ifs >> status) {
		
		string key;
		string value;
		map<string, string> m;

		// 截取时间
		int pos = date.find(":");
		if (pos != -1) {
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// 截取时段
		pos = interval.find(":");
		if (pos != -1) {
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// 截取学号
		pos = stu_ID.find(":");
		if (pos != -1) {
			key = stu_ID.substr(0, pos);
			value = stu_ID.substr(pos + 1, stu_ID.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// 截取学生姓名
		pos = stu_name.find(":");
		if (pos != -1) {
			key = stu_name.substr(0, pos);
			value = stu_name.substr(pos + 1, stu_name.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// 截取机房号
		pos = room_ID.find(":");
		if (pos != -1) {
			key = room_ID.substr(0, pos);
			value = room_ID.substr(pos + 1, room_ID.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		// 截取预约状态
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

// 更新预约记录
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