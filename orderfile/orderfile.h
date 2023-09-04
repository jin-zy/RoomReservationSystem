#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "../files/files.h"

using namespace std;

/*ԤԼ״̬
* 1	 - �����
* 2	 - ԤԼ�ɹ�
* -1 - ԤԼʧ�ܣ����δͨ��
* 0  - ԤԼȡ��
*/

class OrderFile {
public:
	OrderFile();			// �޲ι���
	void update_order();	// ����ԤԼ��¼

public:
	// ԤԼ��¼����
	// key - ��¼��������value - ��¼�ļ�ֵ����Ϣ
	map<int, map<string, string>> m_order_data;
	int m_size;	// ԤԼ��¼����
};