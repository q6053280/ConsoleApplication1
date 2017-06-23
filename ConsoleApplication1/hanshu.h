#pragma   once  
#include "stdafx.h"
#include"folder.h"
#include<vector>
using namespace std;
class hanshu
{
	//vector<int> main;
	
public:
	int tema;
	vector<int> main;
	int getnum(int i) { return main[i]; }
	hanshu()
	{
		
		main.resize(50, 0);
		tema = 0;
	}
	hanshu(vector<int>a)
	{
		for (int i = 0; i<a.size(); i++)
			main.push_back(a[i]);
		tema = 0;
		main.resize(50, 0);
	}
	hanshu(const hanshu&a)
	{
		for (int i = 0; i<50; i++)
			main.push_back(a.main[i]);
		tema = a.tema;
		main.resize(50, 0);
	}
	hanshu operator +(const hanshu& a)
	{
		vector<int> t(50, 0);
		for (int i = 1; i < a.main.size(); i++)
			t[i] = this->main[i] + a.main[i];
		return hanshu(t);
	}
	hanshu&operator =(const hanshu &a)
	{
		for (int i = 0; i<a.main.size(); i++)
			this->main[i] = a.main[i];
		tema = a.tema;
		return *this;
	}
	static void open(const char*);
	static void clear();
	static void openother(const char*);
	hanshu cishutongji(int);
	vector<hanshu> cishutongji(vector<int>, int);
	string tostring(int);
public:
	string jieguo(int);
	static vector<string> jieguo(vector<hanshu>);
	void resize() { main.clear(); main.resize(50, 0); tema = 0; }
	void display();
};

