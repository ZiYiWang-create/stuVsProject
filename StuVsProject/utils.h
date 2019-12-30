#pragma once
/*
* utils.h  工具类 
*/
#include <qdebug.h>
#include <QString>

#include <iostream>
using namespace std;
#include<string>


class Utils {
public:

	// 10个字符长度，全为数字
	static bool checkId(QString id) {
		string a = id.toStdString();
		int b = 1;
		if (a.size() != 10)
		{
			b = 0;
		}
		else {
			int i;
			for (i = 0; i < a.size(); i++)
			{
				int tmp = (int)a[i];
				if (tmp < 48 || tmp>57) {
					b = 0;
					break;
				}
			}
		}
		if (b == 0) {
			return false;
		}
		else {
			return true;
		}
	}


};