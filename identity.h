#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "rooms.h"
#include "orderfile/orderfile.h"

using namespace std;

// ��ݳ������
class Identity {
public:
	// �����˵�
	virtual void oper_menu() = 0;
public:
	string m_name;		// �û���
	string m_password;	// ����

};
