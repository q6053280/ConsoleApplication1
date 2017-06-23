#include "stdafx.h"
#include"hanshu.h"
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<strstream>
#include<sstream>
using namespace std;
vector<hanshu> max_comp;
void hanshu::clear()
{
	max_comp.clear();
}
void hanshu::open(const char* path)
{
	ifstream in(path);
	int a = 0, b, c = -1;
	int num = 0;
	string str, str1, str2;
	vector<int> comp(50, 0);
	while (getline(in, str))
	{
		if (str.find("¡¼") != -1)
		{
			a = atoi(str.substr(2, 2).c_str());
			if (a <= c)
			{
				max_comp.push_back(hanshu(comp));
				comp.clear();
				comp.resize(50, 0);
				cout << num++ << endl;
			}
			while (str.find(',') != -1)
				str = str.substr(0, str.find(',')) + " " + str.substr(str.find(",") + 1);
			while (str.find("¡î") != -1)
				str = str.substr(0, str.find("¡î")) + " " + str.substr(str.find("¡î") + 2);
			stringstream sin(str);
			sin >> str1;
			while (sin >> b)
			{
				comp[b] = a;
			}

			c = a;
		}

	}
	max_comp.push_back(hanshu(comp));
}
void hanshu::openother(const char* path)
{
	ifstream in(path);
	int a = 0, b, c = 10000000;
	int num = 0;
	string str, str1, str2;
	vector<int> comp(50, 0);
	while (getline(in, str))
	{
		if (str.find("¡¼") != -1)
		{
			a = atoi(str.substr(2, str.find("´Î") - 1).c_str());
			while (str.find(',') != -1)
				str = str.substr(0, str.find(',')) + " " + str.substr(str.find(",") + 1);
			while (str.find("¡î") != -1)
				str = str.substr(0, str.find("¡î")) + " " + str.substr(str.find("¡î") + 2);
			stringstream sin(str);
			sin >> str1;
			while (sin >> b)
			{
				comp[b] = a;
			}
			max_comp.push_back(hanshu(comp));
			comp.clear();
			cout << num++ << endl;

			comp.resize(50, 0);
		}

	}
	max_comp.push_back(hanshu(comp));
}
hanshu hanshu::cishutongji(int num)
{
	hanshu a;
	for (int i = 0; i<max_comp.size(); i++)
	{
		for (int j = 1; j<50; j++)
		{
			if (max_comp[i].main[j] == num)
				a.main[j]++;
		}

	}
	return a;
}
vector<hanshu> hanshu::cishutongji(vector<int> num, int fen)
{
	vector<hanshu> b;
	hanshu a;

	for (int i = 0; i<max_comp.size(); i++)
	{
		for (int j = 1; j<50; j++)
		{
			if (find(num.begin(), num.end(), max_comp[i].main[j]) != num.end())
				a.main[j]++;
		}
		if ((i%fen) == (fen - 1))
		{
			b.push_back(a);
			a.resize();
		}

	}
	cout << b.size();
	cout << max_comp.size();
	return b;
}
string hanshu::jieguo(int te)
{
	string jieguo = "";
	multimap<int, int> Mycomp;
	for (int i = 1; i<50; i++)
	{
		Mycomp.insert(multimap<int, int>::value_type(main[i], i));
	}
	int flag = -1;
	for (multimap<int, int>::iterator it = Mycomp.begin(); it != Mycomp.end(); ++it)
	{
		if (main[it->second] == flag) {
			if (it->second == te)
				jieguo += "¡î";
			jieguo += tostring(it->second) + ",";
		}
		else
		{
			jieguo += "\n¡¼" + tostring(main[it->second]) + "´Î¡½: ";
			if (it->second == te)
				jieguo += "¡î";
			jieguo += tostring(it->second) + ",";
			flag = main[it->second];
		}
	}
	jieguo += "\n";
	return jieguo;
}
vector<string> hanshu::jieguo(vector<hanshu>a)
{
	vector<string> b;
	for (int i = 0; i<a.size(); i++)
	{
		b.push_back(a[i].jieguo(0));
	}
	return b;
}
string hanshu::tostring(int a)
{
	string m;
	stringstream ss;
	ss << a;
	ss >> m;
	if(a<100)
		return string(2 - m.size(), '0') + m;
	else
		return  m;

}
void hanshu::display() {
	for (int i = 0; i<max_comp.size(); i++)
		cout << max_comp[i].jieguo(0) << endl;
}