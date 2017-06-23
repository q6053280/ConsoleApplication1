// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//
#pragma   once  
#include "stdafx.h"



#include<Windows.h>
#include"hanshu.h"
#include"源.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
//extern string all(string tar);
//extern vector<vector<int>> TMdata;
//extern hanshu two(string str);

vector<vector<int>> TMdata;
//ThreadData thread1(TMdata,0);
//ThreadData thread2(TMdata,1);
ThreadData thread3(TMdata,2);
//ThreadData thread4(TMdata,3);
//ThreadData thread5(TMdata, 4);
//ThreadData thread6(TMdata, 5);
//ThreadData thread7(TMdata, 6);
//ThreadData thread8(TMdata, 7);
vector<string> filedata;
vector<string> result;

std::vector<std::string> split(std::string str, std::string pattern) {
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作  
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
bool kaishi(string str,string line) {
	CoInitialize(NULL); //初始化COM环境   
	//ThreadData thread1;
	//vector<string> filedata;
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象   
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象       
	//ofstream out(line+"\\0.txt");
	
	try
	{
		//步骤2：创建数据源连接  
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		string sdm = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + str;
		pMyConnect->Open(sdm.c_str(), "", "", adModeUnknown);
	}
	catch (_com_error &e)
	{
		cout << "Initiate failed!" << endl;
		//cout << e.Description() << endl;
		//cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
		return 0;
	}
	cout << "Connect succeed!" << endl;

	//步骤3：对数据源中的数据库/表进行操作  
	try
	{
		//pRst = pMyConnect->Execute("select * from fmanage", NULL, adCmdText);//执行SQL： select * from gendat  
		pRst->Open("SELECT * FROM fmanage", _variant_t((IDispatch *)pMyConnect, true),
			adOpenStatic, adLockOptimistic, adCmdText);
		if (!pRst->BOF)
		{
			pRst->MoveFirst();
			//pRst->MoveLast();
		}
		else
		{
			cout << "Data is empty!" << endl;
			return 0;
		}
		vector<_bstr_t> column_name;

		/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i< pRst->Fields->GetCount(); i++)
		{
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		}
		//cout << endl;

		/*对表进行遍历访问,显示表中每一行的内容*/
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			int i = 0;
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					//
					if (i == 3) {
						cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
						string s = (_bstr_t)pRst->GetCollect(*iter);
						filedata.push_back(s);
						//pRst->PutCollect("结果", (thread1.all(s)).c_str());
						//out<<all(s);
					}
						

					//all()

				}
				else
				{
					//cout << "NULL" << endl;
				}
				i++;
			}
			pRst->MoveNext();
			//cout << endl;
		}
		
	}
	catch (_com_error &e)
	{

		//cout << e.Description() << endl;
		//cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
		system("pause");
		return 0;
	}

	//步骤4：关闭数据源  
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集                 
		pMyConnect->Close();//关闭数据库                 
		pRst.Release();//释放记录集对象指针                 
		pMyConnect.Release();//释放连接对象指针  
	}
	catch (_com_error &e)
	{
		//cout << e.Description() << endl;
		//cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
		return 0;
	}
	CoUninitialize(); //释放COM环境  
}

bool loadData(string str) {
	CoInitialize(NULL); //初始化COM环境             
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象   
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象                 
	try
	{
		//步骤2：创建数据源连接  
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		string sdm = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + str;
		pMyConnect->Open(sdm.c_str(), "", "", adModeUnknown);
	}
	catch (_com_error &e)
	{
		cout << "Initiate failed!" << endl;
		//cout << e.Description() << endl;
		//cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
		return 0;
	}
	cout << "Connect succeed!" << endl;

	//步骤3：对数据源中的数据库/表进行操作  
	try
	{
		pRst = pMyConnect->Execute("select * from Six", NULL, adCmdText);//执行SQL： select * from gendat            
		if (!pRst->BOF)
		{
			pRst->MoveFirst();
			//pRst->MoveLast();
		}
		else
		{
			cout << "Data is empty!" << endl;
			return 0;
		}
		//vector<_bstr_t> column_name;

		/*存储表的所有列名，显示表的列名*/
		//for (int i = 0; i< pRst->Fields->GetCount(); i++)
		//{
		//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
		//	column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		//}
		//cout << endl;

		/*对表进行遍历访问,显示表中每一行的内容*/
		while (!pRst->adoEOF)
		{
			//cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
			vector<int> v(11, 0);
			v[0] = pRst->GetCollect("P1");
			v[1] = pRst->GetCollect("P2");
			v[2] = pRst->GetCollect("P3");
			v[3] = pRst->GetCollect("P4");
			v[4] = pRst->GetCollect("P5");
			v[5] = pRst->GetCollect("P6");
			v[6] = pRst->GetCollect("TM");

			string s = (_bstr_t)pRst->GetCollect("RQ");
			//cout << s << endl;
			vector<string> date = split(s, "/");
			v[7] = atoi(date[0].c_str());
			v[8] = atoi(date[1].c_str());
			v[9] = atoi(date[2].c_str());
			v[10] = pRst->GetCollect("QS");
			if (v[8] * 100 + v[9] < 204)
				v[7] -= 1;

			TMdata.push_back(v);

			pRst->MoveNext();
			//pRst->MovePrevious();
			//cout << endl;


		}
		reverse(TMdata.begin(), TMdata.end());
	}
	catch (_com_error &e)
	{
		//cout << e.Description() << endl;
		//			cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());

		return 0;
	}

	//步骤4：关闭数据源  
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集                 
		pMyConnect->Close();//关闭数据库                 
		pRst.Release();//释放记录集对象指针                 
		pMyConnect.Release();//释放连接对象指针  
	}
	catch (_com_error &e)
	{
		//cout << e.Description() << endl;
		//cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
		return 0;
	}
	CoUninitialize(); //释放COM环境  




}
char* GetCurrentDirectory_R(int _len, char* _buf)
{
	static char s_path[256] = { 0 };
	static char flag = 0;
	if (!flag)
	{
		::GetCurrentDirectory(sizeof(s_path), s_path);
		flag = 1;
	}

	return "";
}


HANDLE g_hMutex = NULL;     //互斥量
int num = 0;
							//线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	ThreadData* pThreadData = (ThreadData*)lpParameter;

	while(num<filedata.size())
	{
		//请求获得一个互斥量锁
	
		//std::cout << pThreadData->strThreadName << " --- " << i << std::endl;
		
		//Sleep(100);
		//释放互斥量锁
		//ReleaseMutex(g_hMutex);
		WaitForSingleObject(g_hMutex, INFINITE);
		
		int a = num++;

		ReleaseMutex(g_hMutex);
		result[a] = pThreadData->all(filedata[a]);
		cout << a << " " << pThreadData->Tnum << " ;";
	}
	return 0L;
}
int main(int argc, char* argv[])
{
	clock_t start, finish;
	start = clock();
	double totaltime;
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 在此处为应用程序的行为编写代码。
			//cout << (all("C:\\001\\方案组\\005\\001\\001"));
			char workfile[1000];
			int i = 1000;
			
			GetModuleFileName(NULL,workfile,1000);   //得到当前工作路径 
			(_tcsrchr(workfile, _T('\\')))[1] = 0;
			string line;
			line.assign(workfile);
			string data, need;
			data = "C:\\001\\034\\Nmain.mdb";
			need = "C:\\001\\034\\FaData\\fa.mdb";
			
			data = line + "\\Nmain.mdb";
			need = line + "\\FaData\\fa.mdb";
			
			cout << data << endl;
			cout << need << endl;
			
			loadData(data);
			//cout<<two("C:\\00\\00\\方案组\\001.txt").jieguo(0);
			//kaishi(need,line);


			thread3.filepre(line + "\\data.dat");
			ofstream out(line + "\\1位结果.txt");
			
			int resultnum = filedata.size();
			result.resize(resultnum, "");
			//HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc, &thread1, 0, NULL);
			
			//HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc, &thread2, 0, NULL);
			//HANDLE hThread3 = CreateThread(NULL, 0, ThreadProc, &thread4, 0, NULL);
			//HANDLE hThread4 = CreateThread(NULL, 0, ThreadProc, &thread5, 0, NULL);
			//HANDLE hThread5 = CreateThread(NULL, 0, ThreadProc, &thread6, 0, NULL);
			//HANDLE hThread6 = CreateThread(NULL, 0, ThreadProc, &thread7, 0, NULL);
			//HANDLE hThread7 = CreateThread(NULL, 0, ThreadProc, &thread8, 0, NULL);
			thread3.all2(&out);

			//while (num < filedata.size()) 
			{
				//WaitForSingleObject(g_hMutex, INFINITE);

				int a = num++;
				//ReleaseMutex(g_hMutex);
				//result[a]=thread3.all(filedata[a]);
				//out << thread3.all(filedata[a]);
				//thread3.all2(&out);
				//cout << a <<" ; ";
				
			}
			//system("pause");
			
			//WaitForSingleObject(hThread1, INFINITE);
			//WaitForSingleObject(hThread2, INFINITE);
			//WaitForSingleObject(hThread3, INFINITE);
			//WaitForSingleObject(hThread4, INFINITE);
			//WaitForSingleObject(hThread5, INFINITE);
			//WaitForSingleObject(hThread6, INFINITE);
			//WaitForSingleObject(hThread7, INFINITE);
		
			
			
			//for (int i = 0; i < result.size(); i++) {
				//if (result[i].empty())
			//		cout << "empty "<< i << endl;
			//	out << result[i]<<endl;
			//}
			out.flush();
			out.close();
			finish = clock();
			
			
			totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
			cout << "\n此程序的运行时间为" << totaltime << "秒！" << endl;
			//system("pause");
			//int *aaa = new int[10000];
			system("pause");
			

        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}
