#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "../files/files.h"

using namespace std;

/*预约状态
* 1	 - 审核中
* 2	 - 预约成功
* -1 - 预约失败，审核未通过
* 0  - 预约取消
*/

class OrderFile {
public:
	OrderFile();			// 无参构造
	void update_order();	// 更新预约记录

public:
	// 预约记录容器
	// key - 记录的条数，value - 记录的键值对信息
	map<int, map<string, string>> m_order_data;
	int m_size;	// 预约记录条数
};