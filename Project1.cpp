#include <iostream> 
#include <vector> 
#include <string> 
#include <set>
#include <algorithm>
#include <fstream> 

using namespace std;
/*用来存储目标文件名*/
string file_nameOutput, file_nameId, file_nameNum;

/*提取文本文件中的信息。*/
string GetText();

/*用于存放无符号整数，便于生成常数表*/
set<int>Num;
vector<int>NUM;

/*用于存放用户标识符，便于生成标识符表*/
set<string>Id;
vector<string>ID;

/*获得一个单词符号,从位置i开始查找。
  //并且有一个引用参数j，用来返回这个单词最后一个字符在str的位置。*/
string GetWord(string str, int i, int& j);

/*这个函数用来除去字符串中连续的空格和换行
  //第一个参数为目标字符串，第二个参数为开始位置
  //返回值为连续的空格和换行后的第一个有效字符在字符串的位置*/
int DeleteNull(string str, int i);

/*判断i当前所指的字符是否为一个分界符，是的话返回真，反之假*/
bool IsBoundary(string str, int i);

/*判断i当前所指的字符是否为一个运算符，是的话返回真，反之假*/
bool IsOperation(string str, int i);

/*此函数将一个pair数组输出到output.txt文件中*/
void OutFile(vector<pair<int, string> > v);

/*此函数将用户标识符输出到idlist.txt文件中*/
void OutFileId(vector<string> s);

/*此函数将无符号整数输出到uintlist.txt文件中*/
void OutFileNum(vector<int> s);

/*此函数接受一个字符串数组，对它进行词法分析，返回一个pair型数组*/
vector<pair<int, string> > analyst(vector<string> vec);

/*此函数判断传递的参数是否为关键字，是的话，返回真，反之返回假*/
bool IsKey(string str);

/*
结果的分类如下：
关键字：1
标识符：2
无符号整数：3
算术运算符：4
分隔符：5
非法字符：6
关系运算符7：7
*/
int main()
{
	string com1 = " ";
	string com2 = "\n";
	string fileline = GetText();
	int begin = 0, end = 0;
	vector<string> array;//将单词以及各种符号存入
	do
	{
		begin = DeleteNull(fileline, begin);
		string nowString;
		nowString = GetWord(fileline, begin, end);
		if (end == -1)
			break;
		if (nowString.compare(com1) && nowString.compare(com2))
			array.push_back(nowString);
		begin = end + 1;
	} while (true);
	vector<pair<int, string> > mid_result;
	mid_result = analyst(array);//进行处理，并将二元式结果保存下来
	OutFile(mid_result);//输出分析结果到output.txt
	OutFileId(ID);//输出用户标识符结果到idlist.txt
	OutFileNum(NUM);//输出常数表结果到uintlist.txt
	for (int i = 0; i < mid_result.size(); i++)//将结果打印到控制台中
		if (mid_result[i].first == 6)
		{
			cout << "ERROR" << endl;
		}
		else
			cout << "(" << mid_result[i].first << " , " << mid_result[i].second << ")" << endl;
	cout << "**********************************************************************\n";
	cout << "***程序已完成词法分析，分析结果已经存储在F盘" << file_nameOutput << ',' << file_nameId << ',' << file_nameNum << "文件中！！！ * **\n";
	cout << "**********************************************************************\n";
	system("pause");
	return 0;
}

/*提取文本文件中的信息*/
string GetText()
{
	string file_name1;
	cout << "请输入源文件名（包括路径和后缀名）：";
	cin >> file_name1;
	ifstream infile(file_name1.c_str(), ios::in);
	if (!infile)
	{
		cerr << "无法打开文件!" << file_name1.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	char f[1000];
	infile.getline(f, 1000, EOF);
	infile.close();
	return f;
}

/*获得一个单词符号,从位置i开始查找。
//并且有一个引用参数j，用来返回这个单词最后一个字符在原字符串的位置。*/
string GetWord(string str, int i, int& j)
{
	string no_use("() {} , ;  + = * / - < > \" \' \\ [] &");
	j = str.find_first_of(no_use, i);
	if (j == -1)
		return "";
	if (i != j)
		j--;
	return str.substr(i, j - i + 1);
}

/*这个函数用来除去字符串中连续的空格和换行
//第一个参数为目标字符串，第二个参数为开始位置
//返回值为连续的空格和换行后的第一个有效字符在字符串的位置*/
int DeleteNull(string str, int i)
{
	for (;; i++)
		if (str[i] != ' '&&str[i] != '\n')
			return i;
}

/*判断i当前所指的字符是否为一个分界符，是的话返回真，反之假*/
bool IsBoundary(string str, int i)
{
	int t;
	char arr[11] = { ',',';','{','}','(',')','\"','\'','[',']','\\' };
	for (t = 0; t < 11; t++)
		if (str[i] == arr[t])
			return true;
	return false;
}

/*判断i当前所指的字符是否为一个字母，是的话返回真，反之假*/
bool Isalpha(string str, int i)
{
	int t;
	if (str[i] <= 'z'&&str[i] >= 'a' || str[i] <= 'Z'&&str[i] >= 'A')
		return true;
	return false;
}

/*判断i当前所指的字符是否为一个计算运算符，是的话返回真，反之假*/
bool IsCOperation(string str, int i)
{
	int t;
	char arr[7] = { '+','-','*','/','%','=','&' };
	for (t = 0; t < 7; t++)
		if (str[i] == arr[t])
			return true;
	return false;
}

/*判断i当前所指的字符是否为一个关系运算符，是的话返回真，反之假*/
bool IsOperation(string str, int i)
{
	int t;
	char arr[3] = { '<','>' };
	for (t = 0; t < 3; t++)
		if (str[i] == arr[t])
			return true;
	return false;
}

/*此函数判断传递的参数是否为关键字，是的话，返回真，反之返回假*/
bool IsKey(string str)
{
	string
		reslist[25] = { "#include","scanf","printf","stdio.h","void","main","%d","%f","char","double","int","long","double","float","for","while","do","break","continue",
		"switch","short","case","return","if","else" };
	vector<string> ppp(reslist, reslist + 25);
	int u;
	for (u = 0; u < ppp.size(); u++)
		if (!str.compare(ppp[u]))
			return true;
	return false;
}

/*此函数将一个个字符串数组输出到一个文件中*/
void OutFile(vector<pair<int, string> > v)
{
	file_nameOutput = "F:/output.txt";
	ofstream outfile(file_nameOutput.c_str(), ios::out);
	if (!outfile)
	{
		cerr << "无法打开文件!" << file_nameOutput.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	int i;
	for (i = 0; i < v.size(); i++)
		if (v[i].first == 6)
		{
			outfile << "ERROR" << endl;
		}
		else
			outfile << "(" << v[i].first << " , " << v[i].second << ")" << endl;
	outfile << "/*finished*/";
	outfile.close();
	return;
}
/*此函数将用户标识符输出到idlist.txt文件中*/
void OutFileId(vector<string> s)
{
	file_nameId = "F:/idlist.txt";
	ofstream outfile(file_nameId.c_str(), ios::out);
	if (!outfile)
	{
		cerr << "无法打开文件!" << file_nameId.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	for (auto it = s.begin(); it != s.end(); it++)
	{
		outfile << *it << endl;
	}
	outfile << "/*finished*/";
	outfile.close();
	return;
}

/*此函数将无符号整数输出到uintlist.txt文件中*/
void OutFileNum(vector<int> s)
{
	file_nameNum = "F:/uintlist.txt";
	ofstream outfile(file_nameNum.c_str(), ios::out);
	if (!outfile)
	{
		cerr << "无法打开文件!" << file_nameNum.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	for (auto it = s.begin(); it != s.end(); it++)
	{
		outfile << *it << endl;
	}
	outfile << "/*finished*/";
	outfile.close();
	return;
}

/*此函数接受一个字符串数组，对它进行词法分析，返回一个pair型数组*/
vector<pair<int, string> > analyst(vector<string> vec)
{
	vector<pair<int, string> > temp;
	int i;
	for (i = 0; i < vec.size(); i++)
	{
		if (vec[i].size() == 1)
		{
			if ((vec[i] == ">" || vec[i] == "<" || vec[i] == "!" || vec[i] == "=") && vec[i + 1] == "=")
			{
				string jk = vec[i];
				jk.append(vec[++i], 0, 1);
				pair<int, string> pp(7, jk);
				temp.push_back(pp);
				continue;
			}
			if ((vec[i] == "+"&&vec[i + 1] == "+") || (vec[i] == "-"&&vec[i + 1] == "-"))
			{
				string jk = vec[i];
				jk.append(vec[++i], 0, 1);
				pair<int, string> pp(4, jk);
				temp.push_back(pp);
				continue;
			}
			if (IsBoundary(vec[i], 0))
			{
				pair<int, string> pp(5, vec[i]);
				temp.push_back(pp);
			}
			else if (IsCOperation(vec[i], 0))
			{
				pair<int, string> pp(4, vec[i]);
				temp.push_back(pp);
			}
			else if (IsOperation(vec[i], 0))
			{
				pair<int, string> pp(7, vec[i]);
				temp.push_back(pp);
			}
			else if (vec[i][0] <= '9'&&vec[i][0] >= '0')
			{
				pair<int, string> pp(3, vec[i]);
				int cnt = Num.size();
				Num.insert(atoi(vec[i].c_str()));//将1位数的整数（由string类型转换为int类型）存入Num中
				if (cnt != Num.size())
				{
					NUM.push_back(atoi(vec[i].c_str()));
				}
				temp.push_back(pp);
			}
			else if (Isalpha(vec[i], 0))
			{
				pair<int, string> pp(2, vec[i]);
				int cnt = Id.size();
				Id.insert(vec[i]);
				if (cnt != Id.size())
				{
					ID.push_back(vec[i]);
				}
				temp.push_back(pp);
			}
			else//报错
			{
				pair<int, string> pp(6, vec[i]);
				temp.push_back(pp);
			}
		}
		else if (vec[i][0] <= '9'&&vec[i][0] >= '0')
		{
			pair<int, string> pp(3, vec[i]);
			int cnt = Num.size();
			Num.insert(atoi(vec[i].c_str()));//将大于1位数的整数（由string类型转换为int类型）存入Num中
			if (cnt != Num.size())
			{
				NUM.push_back(atoi(vec[i].c_str()));
			}
			temp.push_back(pp);
		}
		else if (IsKey(vec[i]))
		{
			pair<int, string> pp(1, vec[i]);
			temp.push_back(pp);
		}
		else if (Isalpha(vec[i], 0))
		{
			pair<int, string> pp(2, vec[i]);
			int cnt = Id.size();
			Id.insert(vec[i]);
			if (cnt != Id.size())
			{
				ID.push_back(vec[i]);
			}
			temp.push_back(pp);
		}
		else//报错
		{
			pair<int, string> pp(6, vec[i]);
			temp.push_back(pp);
		}
	}
	return temp;
}