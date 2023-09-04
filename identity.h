#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "rooms.h"
#include "orderfile/orderfile.h"

using namespace std;

// 身份抽象基类
class Identity {
public:
	// 操作菜单
	virtual void oper_menu() = 0;
public:
	string m_name;		// 用户名
	string m_password;	// 密码

};
