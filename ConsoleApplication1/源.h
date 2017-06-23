#pragma once
#include "stdafx.h"

#include"folder.h"
#include"hanshu.h"
#include"标头.h"
#include<iterator>
#include<string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


class  ThreadData {
	int len[22];
	vector<vector<int>> &TMdata;
	//vector<vector<int>> TMdata;
	int blocksize;

	string filenames;
	hanshu *hone;
	hanshu *htwo;
	struct block{
		
		short isYiwei;//2
		char command[50];//50
		short commandnum;//2
		short z[32];//64
		short znum;//2
		bool isUse[7];//7
		short resultType;//2
		short gongshinum;//2
		
		//short dd[7][7];//查询属性 98	

	}Block;

	struct Block2 {
		block b;
		int num;
	}B;


	struct blockList {
		block b;
		block* next;
	}List,ListBegin;
	vector<string> commandstr;
	short type[22][50];
	short isYiwei;
	string command;
	vector<int> z;//属性集
	vector<vector<int>>*sss;//
	bool isUse[7];
	short resultType ;
	short gongshinum ;
	short dd[7][7];//查询属性	

	int blocklen;
	map<int, int> CombinationMap;
	vector<vector<vector<int>>> CombinationBitmap1;
	vector<vector<vector<int>>> CombinationBitmap2;

	map<int, Block2> blockmap;



public:
	int Tnum;
	FILE *fp;
	FILE*streamf;
	bool read1(string str) {
		



		for (int i = 0; i < 7; i++)
			isUse[i] = true;

		command = getcommand(str.c_str());

		resultType = GetPrivateProfileInt("TComboBox", "ComboBox4", -1, str.c_str());
		//cout << resultType << endl;


		resultType = getResultType(resultType);
		int che74 = GetPrivateProfileInt("TCheckBox", "CheckBox74", -1, str.c_str());
		if (che74)
			for (int i = 0; i < 7; i++)
				isUse[i] = true;
		isYiwei = GetPrivateProfileInt("TCheckBox", "CheckBox89", -1, str.c_str());
		gongshinum = GetPrivateProfileInt("TComboBox", "ComboBox5", -1, str.c_str());


		//cout << gongshinum << endl;
		if (resultType == -1 || isYiwei == -1 || che74 == -1 || gongshinum == -1) {
			cout << "错误" << endl;

			return 1;
		}

		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox";
			b.push_back('1' + i);
			dd[0][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[0][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[0] && dd[0][i])
				z.push_back(i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(10 + i);
			dd[1][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[1][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[1] && dd[1][i])
				z.push_back(7 + i);

		}

		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(19 + i);
			dd[2][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[2][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[2] && dd[2][i])
				z.push_back(14 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(28 + i);
			dd[3][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[3][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[3] && dd[3][i])
				z.push_back(21 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(35 + i);
			dd[4][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[4][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[4] && dd[4][i])
				z.push_back(28 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(42 + i);
			dd[5][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[5][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[5] && dd[5][i])
				z.push_back(35 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(49 + i);
			dd[6][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[6][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[6] && dd[6][i])
				z.push_back(42 + i);
			
		}
		return 0;
	}
	bool load(FILE *fp,string str) {
	

		for (int i = 0; i < 7; i++)
			isUse[i] = true;

		command = getcommand(str.c_str());

		resultType = GetPrivateProfileInt("TComboBox", "ComboBox4", -1, str.c_str());
		//cout << resultType << endl;


		resultType = getResultType(resultType);
		int che74 = GetPrivateProfileInt("TCheckBox", "CheckBox74", -1, str.c_str());
		if (che74)
			for (int i = 0; i < 7; i++)
				isUse[i] = true;
		isYiwei = GetPrivateProfileInt("TCheckBox", "CheckBox89", -1, str.c_str());
		gongshinum = GetPrivateProfileInt("TComboBox", "ComboBox5", -1, str.c_str());


		//cout << gongshinum << endl;
		if (resultType == -1 || isYiwei == -1 || che74 == -1 || gongshinum == -1) {
			cout << "错误" << endl;

			return 1;
		}

		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox";
			b.push_back('1' + i);
			dd[0][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[0][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[0] && dd[0][i])
				z.push_back(i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(10 + i);
			dd[1][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[1][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[1] && dd[1][i])
				z.push_back(7 + i);

		}

		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(19 + i);
			dd[2][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[2][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[2] && dd[2][i])
				z.push_back(14 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(28 + i);
			dd[3][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[3][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[3] && dd[3][i])
				z.push_back(21 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(35 + i);
			dd[4][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[4][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[4] && dd[4][i])
				z.push_back(28 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(42 + i);
			dd[5][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[5][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[5] && dd[5][i])
				z.push_back(35 + i);

		}
		for (int i = 0; i < 7; i++)
		{

			string b = "CheckBox" + Int_to_String(49 + i);
			dd[6][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
			if (dd[6][i] == -1)
			{
				cout << "错误" << endl;

				return 1;
			}
			if (isUse[6] && dd[6][i])
				z.push_back(42 + i);

		}
		

		//cout << sizeof(Block);
		
	

		return 0;
	}
	void loading() {
		
		
		for (int i = 1; i < 50; i++)
		{
			type[0][i] = i % 49;
			if (!type[0][i])
				type[0][i] = 49;
		}

		for (int i = 1; i < 50; i++)
		{
			type[1][i] = (i / 10 + i % 10) % 10;
		}

		for (int i = 1; i < 50; i++)
		{
			type[2][i] = i % 10;
		}

		for (int i = 1; i < 50; i++)
		{
			type[3][i] = i % 12;
			if (!type[3][i])
				type[3][i] = 12;
		}
		for (int i = 1; i < 50; i++)
		{
			type[4][i] = (22 - i % 12) % 12;
			if (!type[4][i])
				type[4][i] = 12;
		}

		for (int i = 1; i < 50; i++)
		{
			type[5][i] = i / 7 + 1;
			if (i % 7 == 0)
				type[5][i] -= 1;
		}

		for (int i = 1; i < 50; i++)
		{
			type[6][i] = i / 10;
		}

		for (int i = 1; i < 50; i++)
		{
			type[7][i] = i % 7;
		}

		{
			int a1[] = { 01,07,13,19,23,29,35,45 };
			int a2[] = { 02,8,12,18,24,30,34,40,46 };
			int a3[] = { 03,9,15,25,31,37,41,47 };
			int a4[] = { 04,10,14,20,26,36,42,48 };
			int a5[] = { 05,11,17,21,27,33,39,43,49 };
			int a6[] = { 06,16,22,28,32,38,44 };
			for (int i = 0; i < 8; i++)
				type[8][a1[i]] = 1;
			for (int i = 0; i < 9; i++)
				type[8][a2[i]] = 0;
			for (int i = 0; i < 8; i++)
				type[8][a3[i]] = 3;
			for (int i = 0; i < 8; i++)
				type[8][a4[i]] = 2;
			for (int i = 0; i < 9; i++)
				type[8][a5[i]] = 5;
			for (int i = 0; i < 7; i++)
				type[8][a6[i]] = 4;
		}

		{
			int a1[] = { 03,04,17,18,25,26,33,34,47,48, };
			int a2[] = { 07,8,15,16,29,30,37,38,45,46, };
			int a3[] = { 05,06,13,14,21,22,35,36,43,44, };
			int a4[] = { 01,02,9,10,23,24,31,32,39,40, };
			int a5[] = { 11,12,19,20,27,28,41,42,49, };

			for (int i = 0; i < 10; i++)
				type[9][a1[i]] = 0;
			for (int i = 0; i < 10; i++)
				type[9][a2[i]] = 1;
			for (int i = 0; i < 10; i++)
				type[9][a3[i]] = 2;
			for (int i = 0; i < 10; i++)
				type[9][a4[i]] = 3;
			for (int i = 0; i < 9; i++)
				type[9][a5[i]] = 4;


		}
		{
			int a1[] = { 01,07,13,19,23,29,35,45 };
			int a2[] = { 02,8,12,18,24,30,34,40,46 };
			int a3[] = { 03,9,15,25,31,37,41,47 };
			int a4[] = { 04,10,14,20,26,36,42,48 };
			int a5[] = { 05,11,17,21,27,33,39,43,49 };
			int a6[] = { 06,16,22,28,32,38,44 };
			for (int i = 0; i < 8; i++)
				type[10][a1[i]] = 1 / 2;
			for (int i = 0; i < 9; i++)
				type[10][a2[i]] = 0 / 2;
			for (int i = 0; i < 8; i++)
				type[10][a3[i]] = 3 / 2;
			for (int i = 0; i < 8; i++)
				type[10][a4[i]] = 2 / 2;
			for (int i = 0; i < 9; i++)
				type[10][a5[i]] = 5 / 2;
			for (int i = 0; i < 7; i++)
				type[10][a6[i]] = 4 / 2;
		}
		for (int i = 1; i < 50; i++)
		{
			type[11][i] = i % 2;
		}
		for (int i = 1; i < 50; i++)
		{
			type[12][i] = i / 25;
		}
		for (int i = 1; i < 50; i++)
		{
			type[13][i] = (i / 10 + i % 10) % 2;
		}
		for (int i = 1; i < 50; i++)
		{
			type[14][i] = (i / 10 + i % 10) / 5;
		}
		for (int i = 1; i < 50; i++)
		{
			type[15][i] = (i % 10) / 5;
		}
		for (int i = 1; i < 50; i++)
		{
			type[16][i] = (i / 25) * 2 + (i % 2);
		}
		for (int i = 1; i < 50; i++)
		{
			type[17][i] = i % 3;
		}
		for (int i = 1; i < 50; i++)
		{
			type[18][i] = i % 4;
		}
		for (int i = 1; i < 50; i++)
		{
			type[19][i] = i % 6;
		}
		for (int i = 1; i < 50; i++)
		{
			type[20][i] = (i / 10) + i % 10;
		}
		for (int i = 1; i < 50; i++)
		{
			type[21][i] = (i / 10) * 2 + i % 2;
		}
		len[0] = 49;
		len[1] = 10;
		len[2] = 10;
		len[3] = 12;
		len[4] = 12;
		len[5] = 7;
		len[6] = 5;
		len[7] = 7;
		len[8] = 6;
		len[9] = 5;
		len[10] = 3;
		len[11] = 2;
		len[12] = 2;
		len[13] = 2;
		len[14] = 2;
		len[15] = 2;
		len[16] = 4;
		len[17] = 3;
		len[18] = 4;
		len[19] = 6;
		len[20] = 13;
		len[21] = 10;
	}
	void write(FILE *fp,string str) {
		
		Block.isYiwei = isYiwei;
		Block.commandnum = command.size();
		for (int i = 0; i < Block.commandnum; i++) {
			Block.command[i] = command[i];
		}

		Block.znum = z.size();
		for (int i = 0; i < Block.znum; i++)
		{
			Block.z[i] = z[i];
		}

		for (int i = 0; i < 7; i++)
		{
			Block.isUse[i] = isUse[i];
		}
		Block.resultType = resultType;
		Block.gongshinum = gongshinum;

		//for (int i = 0; i < 7; i++)
		//	for (int j = 0; j < 7; j++)
		//		Block.dd[i][j] = dd[i][j];


		//string fdata = str.substr(0, str.find_last_of("\\")) + ".dat";
		//(fp = fopen(fdata.c_str(), "a+"));

		//fseek(fp, 0, SEEK_END);
		do { fseek(fp, blocksize, SEEK_SET); }
		while(fwrite(&Block, sizeof(Block), 1, fp)!=1);
		fflush(fp);
		//cout << sizeof(Block) << endl;
		//fseek(fp, 0, SEEK_END);
		//fclose(fp);
	}
	void write2() {

		Block.isYiwei = isYiwei;
		Block.commandnum = command.size();
		for (int i = 0; i < Block.commandnum; i++) {
			Block.command[i] = command[i];
		}

		Block.znum = z.size();
		for (int i = 0; i < Block.znum; i++)
		{
			Block.z[i] = z[i];
		}

		for (int i = 0; i < 7; i++)
		{
			Block.isUse[i] = isUse[i];
		}
		Block.resultType = resultType;
		Block.gongshinum = gongshinum;
		
		

		//for (int i = 0; i < 7; i++)
		//	for (int j = 0; j < 7; j++)
		//		Block.dd[i][j] = dd[i][j];


		//string fdata = str.substr(0, str.find_last_of("\\")) + ".dat";
		//(fp = fopen(fdata.c_str(), "a+"));

		//fseek(fp, 0, SEEK_END);

		
		B.b = Block;
		B.num = --blocklen;
		
		do { 
			fseek(streamf, 0, SEEK_END); 
		} 
		while (fwrite(&B, sizeof(Block2), 1, streamf) != 1);
		fflush(streamf);

		//fclose(streamf);


		//cout << sizeof(Block) << endl;
		//fseek(fp, 0, SEEK_END);
		//fclose(fp);
	}

	void read2(FILE *fp ,string str) {
		//cout << blocksize;
		
		do { fseek(fp, blocksize, SEEK_SET); 
		//cout << fread(&Block, sizeof(Block), 1, fp);
		} 
		while (fread(&Block, sizeof(Block), 1, fp)!=1);
	
		


		isYiwei = Block.isYiwei;
		command = "";
	
		int commandnum = Block.commandnum;
		for (int i = 0; i < Block.commandnum; i++) {
			command.push_back(Block.command[i]);
		}

		//Block.znum = z.size();
		z.resize(Block.znum,0);
		for (int i = 0; i < Block.znum; i++)
		{
			z[i] =Block.z[i];
		}

		for (int i = 0; i < 7; i++)
		{
			isUse[i] = Block.isUse[i];
		}
		resultType =Block. resultType;
		gongshinum =Block. gongshinum;

		//for (int i = 0; i < 7; i++)
		//	for (int j = 0; j < 7; j++)
		//		dd[i][j] =Block.dd[i][j];


		//string fdata = str.substr(0, str.find_last_of("\\")) + ".txt";
		//(fp = fopen(fdata.c_str(), "a+"));

		//fseek(fp, 0, SEEK_END);

		//fwrite(&Block, sizeof(Block), 1, fp);
		//cout << sizeof(Block) << endl;
		//fseek(fp, 0, SEEK_END);
		//fclose(fp);
	}

	void read3() {

		static int s = 0;
		Block = blockmap[s++].b;

		isYiwei = Block.isYiwei;
		command = "";

		int commandnum = Block.commandnum;
		for (int i = 0; i < Block.commandnum; i++) {
			command.push_back(Block.command[i]);
		}

		//Block.znum = z.size();
		z.resize(Block.znum, 0);
		for (int i = 0; i < Block.znum; i++)
		{
			z[i] = Block.z[i];
		}

		for (int i = 0; i < 7; i++)
		{
			isUse[i] = Block.isUse[i];
		}
		resultType = Block.resultType;
		gongshinum = Block.gongshinum;

		//for (int i = 0; i < 7; i++)
		//	for (int j = 0; j < 7; j++)
		//		dd[i][j] =Block.dd[i][j];


		//string fdata = str.substr(0, str.find_last_of("\\")) + ".txt";
		//(fp = fopen(fdata.c_str(), "a+"));

		//fseek(fp, 0, SEEK_END);

		//fwrite(&Block, sizeof(Block), 1, fp);
		//cout << sizeof(Block) << endl;
		//fseek(fp, 0, SEEK_END);
		//fclose(fp);
	}
	

	void Combination1(vector<int> set, int N, int m)
	{
		int C = (1 << m) - 1;
		int temp = ((1 << N) - (1 << (N - m)));
		vector<vector<int>> re;

		int str = N * 100 + m;
		//cout << str << endl;
		if (CombinationMap.find(str) == CombinationMap.end()) 
		{
			
			vector<vector<int>> ssss;
			 while (C <= temp )
			{
				int i = 0;
				int k;
				vector<int> result;
				vector<int> rtemp;
			while ((k = 1 << i) <= C)
			{
				//循环测试每个bit是否为1     
				if ((C&k) != 0)
				{
					result.push_back(set[i]);
					rtemp.push_back(i);
				}
				i++;
			}
			ssss.push_back(result);
			re.push_back(rtemp);
			C = (C + (C&(-C))) | ((C ^ (C + (C&(-C)))) / (C&(-C))) >> 2;
		}
			 CombinationMap.insert(pair<int,int>(str, CombinationBitmap1.size()));
			 //CombinationMap[str] = CombinationMap.size()+1;
			 CombinationBitmap1.push_back(re);
			 CombinationBitmap2.push_back(ssss);
			 sss = &CombinationBitmap2.back();
		}
	
		
		else
		{
			//mytimer.Start();
			
			
			sss = &CombinationBitmap2[CombinationMap.find(str)->second];
			
			vector<vector<int>>*temp = &CombinationBitmap1[CombinationMap.find(str)->second];

			//mytimer.Stop();
			//mytimer.Start();
			// for (int i = 0; i < sss.size(); i++)
			//	 for (int j = 0; j < sss[i].size(); j++)
			//		 sss[i][j] = set[sss[i][j]];
			 for (vector<vector<int>>::iterator it = sss->begin(),its=temp->begin(); it != sss->end(); ++it,++its) {
				 for (vector<int>::iterator iter = it->begin(),iters = its->begin(); iter != it->end(); ++iter,++iters)
				 {
					 *iter = set[*iters];
				 }

			}
			//mytimer.Stop();

		}
		//cout << s.size() << endl;
	}
	void Combination2(int set[], int N, int m)
	{
		int * p;
		//p = set - 1;
		int C = (1 << m) - 1;
		int temp = ((1 << N) - (1 << (N - m)));
		__asm
		{
			mov eax, m;
			mov ebx, N;
			mov esi, p;
		};
	
		return ;
	}
	int getResultType(int x) {
		switch (x) {
		case 0:
			return 0;
		case 1:
			isUse[2] = false;
			return 1;
		case 2:
			isUse[3] = false;
			return 3;
		case 3:
			isUse[3] = false;
			return 4;
		case 4:
			isUse[2] = false;
			return 2;
		case 5:
			return 5;
		case 6:
			return 7;
		case 7:
			isUse[3] = false;
			return 8;
		case 8:
			isUse[2] = false;
			return 6;
		case 9:
			isUse[2] = false;
			return 9;
		case 10:
			isUse[3] = false;
			return 10;
		case 11:
			isUse[3] = false;
			isUse[2] = false;
			return 11;
		case 12:
			isUse[3] = false;
			isUse[2] = false;
			return 12;
		case 13:
			isUse[3] = false;
			isUse[2] = false;
			return 13;
		case 14:
			isUse[3] = false;
			isUse[2] = false;
			return 14;
		case 15:
			isUse[3] = false;
			isUse[2] = false;
			return 15;
		case 16:
			isUse[3] = false;
			isUse[2] = false;
			return 16;
		case 17:
			isUse[3] = false;
			return 17;
		case 18:
			isUse[3] = false;
			return 18;
		case 19:
			isUse[3] = false;
			return 19;
		case 20:
			isUse[1] = false;
			isUse[3] = false;
			return 20;
		case 21:
			isUse[2] = false;
			return 21;
		default:
			return -1;
		}


	}
	string getcommand(string str) {
		int p[12];
		string com = "";
		p[0] = GetPrivateProfileInt("TSpinEdit", "SpinEdit7", -1, str.c_str());
		p[1] = GetPrivateProfileInt("TSpinEdit", "SpinEdit8", -1, str.c_str());
		p[2] = GetPrivateProfileInt("TSpinEdit", "SpinEdit9", -1, str.c_str());
		p[3] = GetPrivateProfileInt("TSpinEdit", "SpinEdit10", -1, str.c_str());
		p[4] = GetPrivateProfileInt("TSpinEdit", "SpinEdit25", -1, str.c_str());
		p[5] = GetPrivateProfileInt("TSpinEdit", "SpinEdit26", -1, str.c_str());
		p[6] = GetPrivateProfileInt("TSpinEdit", "SpinEdit27", -1, str.c_str());
		p[7] = GetPrivateProfileInt("TSpinEdit", "SpinEdit28", -1, str.c_str());
		p[8] = GetPrivateProfileInt("TSpinEdit", "SpinEdit29", -1, str.c_str());
		p[9] = GetPrivateProfileInt("TSpinEdit", "SpinEdit30", -1, str.c_str());
		p[10] = GetPrivateProfileInt("TSpinEdit", "SpinEdit31", -1, str.c_str());
		p[11] = GetPrivateProfileInt("TSpinEdit", "SpinEdit32", -1, str.c_str());
		int ComboBox21 = GetPrivateProfileInt("TComboBox", "ComboBox21", -1, str.c_str());
		int ComboBox3 = GetPrivateProfileInt("TComboBox", "ComboBox3", -1, str.c_str());
		switch (ComboBox3) {
		case 0:
			ComboBox3 = 1; break;
		case 1:
			ComboBox3 = 2; break;
		case 2:
			ComboBox3 = 3; break;
		case 3:
			ComboBox3 = 4; break;
		case 7:
			ComboBox3 = 5; break;
		case 8:
			ComboBox3 = 6; break;
		case 9:
			ComboBox3 = 7; break;
		case 10:
			ComboBox3 = 8; break;
		case 11:
			ComboBox3 = 9; break;
		case 12:
			ComboBox3 = 10; break;
		case 13:
			ComboBox3 = 11; break;
		case 14:
			ComboBox3 = 12; break;

		}
		for (int i = 0; i < ComboBox3; i++)
		{
			for (int j = 0; j<p[i]; j++)
				com += ('0' + (i + 1 + ComboBox21) % 2);
		}
		reverse(com.begin(), com.end());
		return com;
	}
	string Int_to_String(int n)
	{
		ostringstream stream;
		stream << n;  //n为int类型
		return stream.str();
	}
	void getResult(vector<int>& vecInt, vector<int> t) {
		vector<int> result;
		for (int i = 0; i < vecInt.size(); ++i) {
			if (vecInt[i] == 1) {
				result.push_back(t[i]);
			}
		}
		sss->push_back(result);

	}
	hanshu getSecond(hanshu a, hanshu b){
		int count = 0;
		int te = b.tema;
		vector<int> jilu;
		int tenum = b.getnum(b.tema);

		for (int i = 1; i < 50; i++) {
			if (b.getnum(i) <= tenum)
			{
				if (jilu.empty() || find(jilu.begin(), jilu.end(), type[resultType][i]) == jilu.end())
				{
					count++;
					jilu.push_back(type[resultType][i]);
					if (type[resultType][i] > type[resultType][te] && b.getnum(i) == tenum) {
						count--;
					}
				}
			}
		}

		//cout << count << endl;
		vector<int> aa;
		multimap<int, int> Map, finalmap;
		for (int i = 1; i < 50; i++) {
			if (Map.find(type[resultType][i]) == Map.end())
				Map.insert(make_pair(type[resultType][i], a.getnum(i)));

			//cout << resultType;
		}
		
		for (multimap<int, int>::iterator it = Map.begin(); it != Map.end(); ++it)
		{
			finalmap.insert(make_pair(it->second, it->first));

		}
		int d = count;
		for (multimap<int, int>::iterator it = finalmap.begin(); it != finalmap.end(); ++it)
		{
			d--;
			if (d == 0)
			{
				int r = it->second;
				vector<int> res(50, 0);
				for (int i = 1; i < 50; i++)

					if (type[resultType][i] == r)
						res[i]++;
				//cout << hanshu(res).jieguo(0);
				return hanshu(res);

				break;
			}

		}

		//return a;
	}
	hanshu getSecond4(hanshu a, hanshu b) {
		int count = 0;
		int te = b.tema;
		vector<int> jilu;
		int tenum = b.getnum(b.tema);

		for (int i = 1; i < 50; i++) {
			if (b.getnum(i) <= tenum)
			{
				int t = (type[resultType][i] + TMdata[0][7] % 12)%12;
				if (t == 0)
					t = 12;
				int tm = (type[resultType][te] + TMdata[0][7] % 12) % 12;
				if (tm == 0)
					tm = 12;
				if (jilu.empty() || find(jilu.begin(), jilu.end(), t) == jilu.end())
				{
					count++;
					jilu.push_back(t);
					if (t > tm && b.getnum(i) == tenum) {
						count--;
					}
				}
			}
		}

		//cout << count << endl;
		vector<int> aa;
		multimap<int, int> Map, finalmap;
		for (int i = 1; i < 50; i++) {
			int t = (type[resultType][i] + TMdata[0][7] % 12) % 12;
			if (t == 0)
				t = 12;
			if (Map.find(t) == Map.end()) {
				
				Map.insert(make_pair(t, a.getnum(i)));
			}
				

			//cout << resultType;
		}

		for (multimap<int, int>::iterator it = Map.begin(); it != Map.end(); ++it)
		{
			finalmap.insert(make_pair(it->second, it->first));

		}
		int d = count;
		for (multimap<int, int>::iterator it = finalmap.begin(); it != finalmap.end(); ++it)
		{
			d--;
			if (d == 0)
			{
				int r = it->second;
				vector<int> res(50, 0);
				for (int i = 1; i < 50; i++)
				{
					int t = (type[resultType][i] + TMdata[0][7] % 12) % 12;
					if (t == 0)
						t = 12;
					if (t == r)
						res[i]++;
				}

					
				//cout << hanshu(res).jieguo(0);
				return hanshu(res);

				break;
			}

		}

		//return a;
	}
	hanshu sortone(int first) {
		int count = 0, mod = 1;
		//int tempcount=0;
		vector<int> r(50, 0);
		for (vector<vector<int>>::iterator it = sss->begin(); it != sss->end(); ++it)
		{

			mod = 1;
			int m = 0;
			if (isYiwei)
			{
				mod = len[resultType];
				m = 1;
			}


			for (; m < mod; m++) {
				//string str = "";
				int flag = 1;
				for (int i = 1 + first; i < command.length() + 1 + first; i++)
				{
					//tempcount++;
					int result = 0;
					
					for (int j = 0; j < gongshinum + 1; j++)
					{
						int n = (*it)[j];
						int num = TMdata[i][n % 7];
						int shu = type[n / 7][num];
						if (n/7 == 4) {
							shu = (shu + TMdata[i][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}
							 
						result += shu;
					}

					result += m;
					if (resultType != 4) {

						if (type[resultType][TMdata[i - 1][6]] % len[resultType] == result % len[resultType])
						{
						
							if (command[i - 1 - first] != '1')

							{
								flag = 0;
								break;
							}
								
						}
						else
						{
							if (command[i - 1 - first] != '0')
							{
								flag = 0;
								break;
							}

						}

					}
					else {

						if ((type[resultType][TMdata[i - 1][6]]+ TMdata[i-1][7] % 12 )% len[resultType] == result % len[resultType])
						{

							if (command[i - 1 - first] != '1')

							{
								flag = 0;
								break;
							}
						}
						else
						{
							if (command[i - 1 - first] != '0')
							{
								flag = 0;
								break;
							}
						}
					}
					



				}

				//cout << str << endl;
				if (flag) {
					count++;
					int result = 0;
					
					for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
					{
						
						int n = *iter;
						int num = TMdata[0 + first][n % 7];
						int shu = type[n / 7][num];
						if (n/7 == 4) {
							shu = (shu + TMdata[0 + first][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
						//cout << n << "(" << type[n / 7][num] << ") ";
					}
					//cout << (result) % len[resultType] << endl;
					result += m;
					if(resultType!=4)
						for (int i = 1; i < 50; i++)
						{
							if (type[resultType][i] % len[resultType] == (result) % len[resultType])
								r[i] += 1;
						}
					else
						for (int i = 1; i < 50; i++)
						{
							if ((type[resultType][i] + TMdata[first][7] % 12) % len[resultType] == (result) % len[resultType])
								r[i] += 1;
						}

				}
			}

		}
		
		if (mod > 1)
			mod -= 1;
		//cout << sss.size()*mod << " " << count << endl;
		//cout << tempcount << endl;
		//cout << hanshu(r).jieguo(0);
		return hanshu(r);
	}
	hanshu sortthree(int first) {
		int count = 0, mod = 1;
		//int tempcount=0;
		vector<int> r(50, 0);
		
		for (vector<vector<int>>::iterator it = sss->begin(); it != sss->end(); ++it)
		{

			mod = 1;
			int m = 0;
			if (isYiwei)
			{
				mod = len[resultType];
				m = 1;
			}


			for (; m < mod; m++) {
				//string str = "";

				
				int str_flag = 0;

				for (int i = 1 + first; i < command.length() + 1 + first; i++)
				{
					//tempcount++;
					int result = 0;
					

					for (int j = 0; j < gongshinum + 1; j++)
					{
						int n = (*it)[j];
						int num = TMdata[i][n % 7];
						int shu = type[n / 7][num];
						if (n / 7 == 4) {
							shu = (shu + TMdata[i][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
					}

					result += m;
					if (resultType != 4) {

						if (type[resultType][TMdata[i - 1][6]] % len[resultType] == result % len[resultType])
						{

							if (command[i - 1 - first] == '1')

								;
							else
								break;
						}
						else
						{
							if (command[i - 1 - first] == '0')
								;
							else
								break;
						}

					}
					else {

						if ((type[resultType][TMdata[i - 1][6]] + TMdata[i - 1][7] % 12) % len[resultType] == result % len[resultType])
						{

							if (command[i - 1 - first] == '1')

								;
							else
								break;
						}
						else
						{
							if (command[i - 1 - first] == '0')
								;
							else
								break;
						}
					}
					str_flag++;




				}

				//cout << str << endl;
				if (str_flag == command.size()) {
					count++;
					int result = 0;

					for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
					{

						int n = *iter;
						int num = TMdata[0 + first][n % 7];
						int shu = type[n / 7][num];
						if (n / 7 == 4) {
							shu = (shu + TMdata[0 + first][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
						//cout << n << "(" << type[n / 7][num] << ") ";
					}
					//cout << (result) % len[resultType] << endl;
					result += m;
					if (resultType != 4)
						for (int i = 1; i < 50; i++)
						{
							if (type[resultType][i] % len[resultType] == (result) % len[resultType])
								r[i] += 1;
						}
					else
						for (int i = 1; i < 50; i++)
						{
							if ((type[resultType][i] + TMdata[first][7] % 12) % len[resultType] == (result) % len[resultType])
								r[i] += 1;
						}

				}
			}

		}

		if (mod > 1)
			mod -= 1;
		//cout << sss.size()*mod << " " << count << endl;
		//cout << tempcount << endl;
		//cout << hanshu(r).jieguo(0);

		for (int i = 1; i < 50; i++)
			if(count != 0)
			r[i] = round((r[i] * 10000.0 / count));
			


		return hanshu(r);
	}

	double round(double r)
	{
		return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
	}


    void sorttwo(int first) {
		int count = 0, mod = 1;
		vector<int> r1(50, 0);
		vector<int> r2(50, 0);
		for (vector<vector<int>>::iterator it = sss->begin(); it != sss->end(); ++it)
		{

			mod = 1;
			int m = 0;
			if (isYiwei)
			{
				mod = len[resultType];
				m = 1;
			}


			for (; m < mod; m++) {
				string str1 = "";
				//string str2 = "";
				int flag1 = 0;
				int flag2 = 0;
				for (int i = 1; i < command.length() + 2; i++)
				{

					int result = 0;

					for (int j = 0; j < gongshinum + 1; j++)
					{
						int n = (*it)[j];
						int num = TMdata[i][n % 7];
						int shu = type[n / 7][num];
						if (n / 7 == 4) {
							shu = (shu + TMdata[i][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
					}

					result += m;
					if (resultType != 4) {

						if (type[resultType][TMdata[i - 1][6]] % len[resultType] == result % len[resultType])
						{
							str1 += '1';
							if (command[i - 1 - first] != '1')
							{
								flag1 = 1;
							}
							if (i - 2 - first > -1) {
								if (command[i - 2 - first] != '1')
								{
									flag2 = 1;
								}
							} 
							
						}
						else
						{
							str1 += '0';
							if (command[i - 1 - first] != '0')
							{
								flag1 = 1;
							}
							if (i - 2 - first > -1) {
								if (command[i - 2 - first] != '0')
								
								{
									flag2 = 1;
								}
							}

						}

					}
					else {

						if ((type[resultType][TMdata[i - 1][6]] + TMdata[i - 1][7] % 12) % len[resultType] == result % len[resultType])
						{

							str1 += '1';
							if (command[i - 1 - first] != '1'){
								flag1 = 1;
							}
							if (i - 2 - first > -1) {
								if (command[i - 2 - first] != '1')
								{
									flag2 = 1;
								}
							}
								
						}
						else
						{
							str1 += '0';
							if (command[i - 1 - first] != '0')
		
							{
								flag1 = 1;
							}
							if (i - 2 - first > -1) {
								if (command[i - 2 - first] != '0')
								
								{
									flag2 = 1;
								}
							}
						}
					}
					if (flag1&&flag2)
						break;
				}
					
				if (str1.substr(0,command.length()) == command) {
					count++;
					int result = 0;

					for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
					{

						int n = *iter;
						int num = TMdata[0 + first][n % 7];
						int shu = type[n / 7][num];
						if (n / 7 == 4) {
							shu = (shu + TMdata[0 + first][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
						//cout << n << "(" << type[n / 7][num] << ") ";
					}
					//cout << (result) % len[resultType] << endl;
					result += m;
					if (resultType != 4)
						for (int i = 1; i < 50; i++)
						{
							if (type[resultType][i] % len[resultType] == (result) % len[resultType])
								r1[i] += 1;
						}
					else
						for (int i = 1; i < 50; i++)
						{
							if ((type[resultType][i] + TMdata[0][7] % 12) % len[resultType] == (result) % len[resultType])
								r1[i] += 1;
						}

				}
				if (str1.substr(1, command.length()) == command) {
					count++;
					int result = 0;

					for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
					{

						int n = *iter;
						int num = TMdata[0 + first][n % 7];
						int shu = type[n / 7][num];
						if (n / 7 == 4) {
							shu = (shu + TMdata[1 + first][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
						//cout << n << "(" << type[n / 7][num] << ") ";
					}
					//cout << (result) % len[resultType] << endl;
					result += m;
					if (resultType != 4)
						for (int i = 1; i < 50; i++)
						{
							if (type[resultType][i] % len[resultType] == (result) % len[resultType])
								r2[i] += 1;
						}
					else
						for (int i = 1; i < 50; i++)
						{
							if ((type[resultType][i] + TMdata[1][7] % 12) % len[resultType] == (result) % len[resultType])
								r2[i] += 1;
						}

				}

				//cout << str << endl;
				
				//commandstr.push_back(str);
			}

			
		}

		if (mod > 1)
			mod -= 1;
		//delete hone;
		//delete htwo;
		hone->main = (r1);
		htwo->main = (r2);
		//cout << s.size()*mod << " " << count << endl;
		//cout << hanshu(r).jieguo(0);
		//return hanshu(r1);
	}
	hanshu sort3(int first) {
		int count = 0, mod = 1;
		vector<int> r(50, 0);
		for (vector<vector<int>>::iterator it = sss->begin(); it != sss->end(); ++it)
		{

			mod = 1;
			int m = 0;
			if (isYiwei)
			{
				mod = len[resultType];
				m = 1;
			}


			for (; m < mod; m++) {
				string str = "";

				for (int i = 1 + first; i < command.length() + 1 + first; i++)
				{

					int result = 0;

					for (int j = 0; j < gongshinum + 1; j++)
					{
						int n = (*it)[j];
						int num = TMdata[i][n % 7];
						int shu = type[n / 7][num];
						if (n / 7 == 4) {
							shu = (shu + TMdata[i][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
					}

					result += m;
					if (resultType != 4) {

						if (type[resultType][TMdata[i - 1][6]] % len[resultType] == result % len[resultType])
						{

							if (command[i - 1 - first] == '1')

								str += '1';
							else
								break;
						}
						else
						{
							if (command[i - 1 - first] == '0')
								str += '0';
							else
								break;
						}

					}
					else {

						if ((type[resultType][TMdata[i - 1][6]] + TMdata[i - 1][7] % 12) % len[resultType] == result % len[resultType])
						{

							if (command[i - 1 - first] == '1')

								str += '1';
							else
								break;
						}
						else
						{
							if (command[i - 1 - first] == '0')
								str += '0';
							else
								break;
						}
					}




				}

				//cout << str << endl;
				if (str == command) {
					count++;
					int result = 0;

					for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
					{

						int n = *iter;
						int num = TMdata[0 + first][n % 7];
						int shu = type[n / 7][num];
						if (n / 7 == 4) {
							shu = (shu + TMdata[0 + first][7] % 12) % 12;
							if (shu == 0)
								shu = 12;
						}

						result += shu;
						//cout << n << "(" << type[n / 7][num] << ") ";
					}
					//cout << (result) % len[resultType] << endl;
					result += m;
					if (resultType != 4)
						for (int i = 1; i < 50; i++)
						{
							if (type[resultType][i] % len[resultType] == (result) % len[resultType])
								r[i] += 1;
						}
					else
						for (int i = 1; i < 50; i++)
						{
							if ((type[resultType][i] + TMdata[first][7] % 12) % len[resultType] == (result) % len[resultType])
								r[i] += 1;
						}

				}
			}

		}

		if (mod > 1)
			mod -= 1;
		//cout << sss.size()*mod << " " << count << endl;

		//cout << hanshu(r).jieguo(0);
		return hanshu(r);
	}

	hanshu two(string  str) {
	

		//while (load(str));
		
		//while (load(fp, str));
		
		//read2(fp, str);
		extern Mytimer mytimer;
		
		//mytimer.Start();
		read3();
		//mytimer.Stop();
		//write2();

		//mytimer.Start();
		vector<int> r(50, 0);

		//z.clear();
		//sss.clear();
		//return hanshu(r);

	
		
		
		Combination1(z, z.size(), gongshinum + 1);
		
		//mytimer.Stop();
		
		//mytimer.Start();


		hanshu a = (sortthree(0));
		//cout << a.jieguo(0);
		return a;
		hanshu b =(sortthree(1));
		



	
		//sortthree(a, b);
		
		//mytimer.Stop();
		

		//b.tema = TMdata[0][6];
		z.clear();
	
		

		
		if (resultType != 4) {

			//mytimer.Start();
			hanshu temp = getSecond(a, b);
			//mytimer.Stop();

			return temp;
		}
			
		else
		{
			//mytimer.Start();
			hanshu temp = getSecond4(a, b);
			//mytimer.Stop();

			return temp;

		}
			
		
		
		//cout << s.max_size();


		
		//return result;

	}
	string all(string tar) {
		clock_t start, finish;
		double totaltime;
		start = clock();
		blocksize = 0;
		static int si = 0;

		//构造类对象
		CStatDir statdir;

		//设置要遍历的目录
		if (!statdir.SetInitDir(tar.c_str()))
		{
			puts("目录不存在。");
			return "目录不存在。";
		}

		//开始遍历

		vector<string>file_vec = statdir.BeginBrowseFilenames("*.*");
		//for (vector<string>::const_iterator it = file_vec.begin(); it < file_vec.end(); ++it)
		//std::cout << *it << std::endl;

		//printf("文件总数: %d  ", file_vec.size());
		//cout << sizeof(Block);

		
		vector<int> re;
		re.resize(50, 0);
		hanshu finalresult(re);
		//for (int i = 0; i < 9; i++)
		//finalresult = finalresult + one(place[i]);
	

		string fdata = (file_vec[0]).substr(0, (file_vec[0]).find_last_of("\\")) + ".dat";
		//cout << fdata << endl;; 

		//finish = clock();
		//totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
		//cout << "此程序的运1行时间为" << totaltime << "秒！" << endl;
		
		//fp = fopen(fdata.c_str(), "wb+");
		//fp = fopen(fdata.c_str(), "rb+");

		blocklen = file_vec.size();
		for (vector<string>::const_iterator it = file_vec.begin(); it < file_vec.end(); ++it)
		{
			//cout << *it << endl;
			
			//while (load(fp, *it));
			//write(fp, *it);
			//z.clear();
			//sss.clear();
			
			start = clock();


			finalresult = finalresult + two(*it);

			//finish = clock();
			//totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
			//cout << "此程序的运1行时间为" << totaltime << "秒！" << endl;


			blocksize += sizeof(Block);
		}
		si++;
;
		//finish = clock();
		//totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
		//cout << "此程序的运1行时间为" << totaltime << "秒！" << endl;
		//fclose(fp);
		return finalresult.jieguo(0);

		int year = TMdata[0][7];
		if (TMdata[0][8] * 100 + TMdata[0][9] < 204)
		{
			year += 1;
		}
		int zeronum = 0;
		if (TMdata[0][10] < 100 && TMdata[0][10]>9)
			zeronum = 1;
		if (TMdata[0][10] < 10)
			zeronum = 2;


		string head = Int_to_String(year) + "年" + string(zeronum, '0') + Int_to_String(TMdata[0][10]) + "期, 批量计算结果统计如下:\r\n";
		string tmstr = Int_to_String(year) + "年" + string(zeronum, '0') + Int_to_String(TMdata[0][10]) + "期: ";
		for (int i = 0; i < 6; i++)
		{
			if (TMdata[0][i] < 10)
				tmstr.append("0");
			tmstr.append(Int_to_String(TMdata[0][i]) + "-");
		}
		tmstr.append("T" + Int_to_String(TMdata[0][6]) + "  \r\n");
		
		//return head + tmstr + finalresult.jieguo(0);
		return finalresult.jieguo(0);

		//system("pause");
	}

	string  all2(ofstream* out) {
		clock_t start, finish;
		double totaltime;
		start = clock();
		blocksize = 0;
		static int si = 0;
		vector<string> result;
		

		vector<int> re;
		re.resize(50, 0);
		hanshu finalresult(re);
		//for (int i = 0; i < 9; i++)
		//finalresult = finalresult + one(place[i]);

		int i = 0,j=0;
		for (map<int,Block2>::const_iterator it = blockmap.begin(); it != blockmap.end(); ++it)
		{
			finalresult = finalresult + two("");
			//blocksize += sizeof(Block);
			i++;
			if (it->second.num == 0)
			{
				j++;
				result.push_back(finalresult.jieguo(0));
				//(*out) << finalresult.jieguo(0);
				finalresult=hanshu(re);
				printf("%.2lf%%   %d\r", i * 100.0 /blockmap.size(),j);
				//cout << sizeof(B);
				//cout << ++i << " ";
				//printf("%d ",++i);
				
			}

		}
		;
		cout << "\n保存结果中。。。。。。" << endl;

		copy(result.begin(), result.end(), ostream_iterator<string>(*out, ""));


		//finish = clock();
		//totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
		//cout << "此程序的运1行时间为" << totaltime << "秒！" << endl;
		//fclose(fp);
		return finalresult.jieguo(0);

	
	}
	
	int test() {
		int h = 0;
		for (int i = 0; i < 8000 *250; i++)
		{
			h += i;

		}
		return h;

	}

	void filepre(string str) {
		filenames = str ;


		//streamf = fopen(filenames.c_str(), "wb+");
		//return;

		streamf = fopen(str.c_str(), "rb+");

		fseek(streamf, 0, SEEK_END);
		int len = ftell(streamf);

		fseek(streamf, 0, SEEK_SET);


		int size = 0;
		


		while (1) {
			
			
			do { fseek(streamf, size*sizeof(Block2), SEEK_SET); }
			while(fread(&B, sizeof(Block2), 1, streamf) != 1);

			blockmap.insert(make_pair(size++,B));

		

			if (ftell(streamf)==len)
				break;
		
		}
		fclose(streamf);

		
		
		


	}

	ThreadData(vector<vector<int>> &TM,int num):TMdata(TM),Tnum(num){
		TMdata = TM;
		loading();
		hone = new hanshu();
		htwo = new hanshu();
	}
		
};



